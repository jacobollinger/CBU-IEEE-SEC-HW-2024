import cv2
from math import exp, sqrt
import numpy as np
import torch


from modules.hardware.actuators import Wheels, Arm
from modules.hardware.sensors import Camera, Phototransistor, Ultrasonic
from modules.hardware.serial import SerialInterface
from modules.timer import Timer
from custom_object_detection_ieee.src.model import create_model
from custom_object_detection_ieee.src.config import NUM_CLASSES, DEVICE, CLASSES

from time import sleep

DEBUG_VIDEO_STREAM = True
DEBUG_IMSHOW = False

SMALL_PACKAGE_WIDTH_THRESHOLD = 20 # 75
SMALL_PACKAGE_DISTANCE_THRESHOLD = 15

fixedCamera = Camera()
model = create_model(num_classes=NUM_CLASSES, size=640)
timer = Timer()
serial = SerialInterface("/dev/ttyACM1", 4800)
# serial = SerialInterface()



if DEBUG_IMSHOW:
    from custom_object_detection_ieee.src.config import COLORS

if DEBUG_VIDEO_STREAM:
    import pickle
    import socket
    import struct

    from custom_object_detection_ieee.src.config import COLORS

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("0.0.0.0", 8485))
    server_socket.listen()

    print("Waiting for client to connect")
    client_socket, addr = server_socket.accept()


model.load_state_dict(
    torch.load("./data/out/ieee/e337l/best_model.pth", map_location=DEVICE)[
        "model_state_dict"
    ]
)
model.to(DEVICE).eval()

serial.start()

def main():

    # Wait for signal from the Arduino to pick up the small packages
    print("Waiting for start signal")
    # while not detect_start_signal():
    #     pass

    # Collect the small package
    # for i in range(3):
    while (True):
        collect_a_small_packages()

    # Handover control to the Arduino to do everything else
    serial.write_line("done")


def detect_start_signal():
    """Detects the start signal

    Returns:
        bool: whether or not the start signal was detected
    """
    if serial.is_data_available() and serial.read_line() == "START":
        return True

    return False


def scan_for_objects(
    threshold=0.25,
    object_types=["large_package", "small_package", "fuel_tank", "thruster"],
):
    """Scans for objects in the environment

    Returns:
        dict: dictionary of objects detected and their positions from the fixed camera
        dict: dictionary of objects detected and their positions from the arm camera
    """
    num_images = 1
    fixed_ret = []

    images = [fixedCamera.get_image() for _ in range(num_images)]
    images = [cv2.resize(image, (640, 640)) for image in images]
    # ? Does this need to be converted from BGR to RGB?
    images = [
        cv2.cvtColor(image, cv2.COLOR_BGR2RGB).astype(np.float32) for image in images
    ]
    images = [image / 255.0 for image in images]
    # ? Does this need to be converted from (H, W, C) to (C, H, W)?
    images = [np.transpose(image, (2, 0, 1)).astype(np.float32) for image in images]
    images = [torch.tensor(image, dtype=torch.float).to(DEVICE) for image in images]

    with torch.no_grad():
        outputs = model(images)

    outputs = [{k: v.to("cpu") for k, v in output.items()} for output in outputs]

    for i, output in enumerate(outputs):
        if len(output["boxes"]) == 0:
            outputs.remove(output)
        else:
            boxes = output["boxes"].data.numpy()
            scores = output["scores"].data.numpy()

            boxes = boxes[scores >= threshold].astype(np.int32)

            if DEBUG_VIDEO_STREAM or DEBUG_IMSHOW:
                image_np = images[i].cpu().numpy().transpose(1, 2, 0)
                image_np = cv2.cvtColor(image_np, cv2.COLOR_RGB2BGR)
                cv2.circle(image_np, (400, 400), 5, (128, 128, 128), -1)

            for j, box in enumerate(boxes):
                class_name = CLASSES[output["labels"][j].cpu().numpy()]
                if class_name not in object_types:
                    continue
                fixed_ret.append([class_name, box])
                if DEBUG_VIDEO_STREAM or DEBUG_IMSHOW:
                    # draw a line at 4.3481x-1268.9 +- THRESHOLD
                    print(f"(292, {int(4.3481 * 292 - 1268.9)}), ({int(fixedCamera.width)}, {int(400 - 4.3481 * fixedCamera.width - 1268.9)})")
                    cv2.line(image_np, (292, int(4.3481 * 292 - 1268.9)), (int(fixedCamera.width), int(4.3481 * fixedCamera.width - 1268.9)), (255,255,255), 2)
                    cv2.line(image_np, (292 - SMALL_PACKAGE_WIDTH_THRESHOLD, int(4.3481 * 292 - 1268.9)), (int(fixedCamera.width) - SMALL_PACKAGE_WIDTH_THRESHOLD, int(4.3481 * fixedCamera.width - 1268.9)), (0, 255, 0), 2)
                    cv2.line(image_np, (292 + SMALL_PACKAGE_WIDTH_THRESHOLD, int(4.3481 * 292 - 1268.9)), (int(fixedCamera.width) + SMALL_PACKAGE_WIDTH_THRESHOLD, int(4.3481 * fixedCamera.width - 1268.9)), (0, 255, 0), 2)
                    
                    # cv2.line(image_np, (400 - SMALL_PACKAGE_WIDTH_THRESHOLD, 0), (400 - SMALL_PACKAGE_WIDTH_THRESHOLD, int(fixedCamera.height)), (0, 255, 0), 2)
                    # cv2.line(image_np, (400 + SMALL_PACKAGE_WIDTH_THRESHOLD, 0), (400 + SMALL_PACKAGE_WIDTH_THRESHOLD, int(fixedCamera.height)), (0, 255, 0), 2)
                    
                    # draw a horizontal line at the THRESHOLDS
                    cv2.line(image_np, (0, 400 - SMALL_PACKAGE_DISTANCE_THRESHOLD), (int(fixedCamera.width), 400 - SMALL_PACKAGE_DISTANCE_THRESHOLD), (255, 0, 0), 2)
                    cv2.line(image_np, (0, 400 + SMALL_PACKAGE_DISTANCE_THRESHOLD), (int(fixedCamera.width), 400 + SMALL_PACKAGE_DISTANCE_THRESHOLD), (255, 0, 0), 2)


                    color = COLORS[CLASSES.index(class_name)]
                    xmin = int((box[0] / images[i].shape[1]) * images[0].shape[1])
                    ymin = int((box[1] / images[i].shape[0]) * images[0].shape[0])
                    xmax = int((box[2] / images[i].shape[1]) * images[0].shape[1])
                    ymax = int((box[3] / images[i].shape[0]) * images[0].shape[0])
                    cv2.rectangle(
                        image_np,
                        (xmin, ymin),
                        (xmax, ymax),
                        color[::-1],
                        3,
                    )
                    cv2.putText(
                        image_np,
                        f"{class_name} {scores[j]:.2f}",
                        (xmin, ymin - 5),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.8,
                        color[::-1],
                        2,
                        lineType=cv2.LINE_AA,
                    )
                    cv2.circle(image_np, ((xmin + xmax) // 2, (ymin + ymax) // 2), 5, (0, 0, 255), -1)

            if DEBUG_VIDEO_STREAM:
                image_np = cv2.resize(image_np, (1920, 1080))
                # downscale the image 8x for faster transmission
                image_np = cv2.resize(image_np, (240, 135))
                data = pickle.dumps(image_np)
                message_size = struct.pack("L", len(data))
                client_socket.sendall(message_size + data)
            if DEBUG_IMSHOW:
                cv2.imshow("Fixed Camera", cv2.resize(image_np, (1920, 1080)))
                if cv2.waitKey(1) & 0xFF == ord("q"):
                    break

    return fixed_ret

PIX_PER_DEG = 8.9333
PIX_PER_INCH = 80
def collect_a_small_packages():
    """Collects the small packages from the environment"""
    closest_small_package_center = [fixedCamera.width / 2, 0]
    degree = 16
    distance = 2
    speed = 50

    while (True):
        object_positions = scan_for_objects(object_types=["small_package"])
        closest_small_package = max(
            (pos for obj, pos in object_positions if obj == "small_package"),
            default=None,
            key=lambda x: x[3],
        )

        if closest_small_package is None:
            print("No small packages found")
            continue

        closest_small_package_center = (
            (closest_small_package[0] + closest_small_package[2]) / 2,
            (closest_small_package[1] + closest_small_package[3]) / 2,
        )
        
        degree = (closest_small_package_center[0] - (closest_small_package_center[1] + 1268.9) / 4.3481) / PIX_PER_DEG
        
        # print(f"Center: {closest_small_package_center[0]}, {closest_small_package_center[1]}: solveIK 0 {solveY(closest_small_package_center[1])} -1")

        if serial.is_waiting():
            
            if (
                closest_small_package_center[0]
                < (closest_small_package_center[1] + 1268.9) / 4.3481 - SMALL_PACKAGE_WIDTH_THRESHOLD
            ):
                degree = degree * -1
                print(f"Moving to closest small package center: {closest_small_package_center[0]}, {closest_small_package_center[1]}")
                print(f"Rotate counter clockwise {degree:.2f} degrees at speed {speed}")
                serial.write_line(f"rotateCounterClockwise {degree:.2f} {speed} ")
            elif (
                closest_small_package_center[0]
                > (closest_small_package_center[1] + 1268.9) / 4.3481 + SMALL_PACKAGE_WIDTH_THRESHOLD
            ):
                print(f"Moving to closest small package center: {closest_small_package_center[0]}, {closest_small_package_center[1]}")
                print(f"Rotate clockwise {degree} degrees at speed {speed}")
                serial.write_line(f"rotateClockwise {degree:.2f} {speed} ")
            else:
                break
                # pass

            if speed > 64:
                speed = speed / 2

    speed = 256
    while (True):
        object_positions = scan_for_objects(object_types=["small_package"])
        closest_small_package = max(
            (pos for obj, pos in object_positions if obj == "small_package"),
            default=None,
            key=lambda x: x[3],
        )

        if closest_small_package is None:
            print("No small packages found 2")
            continue

        closest_small_package_center = (
            (closest_small_package[0] + closest_small_package[2]) / 2,
            (closest_small_package[1] + closest_small_package[3]) / 2,
        )
        
        distance = abs((400 - closest_small_package_center[1]) / PIX_PER_INCH)
        
        # print(f"Center: {closest_small_package_center[0]}, {closest_small_package_center[1]}")

        if serial.is_waiting():
            print(
                f"Moving to closest small package center: {closest_small_package_center[0]}, {closest_small_package_center[1]}"
            )
            if (
                closest_small_package_center[1]
                < 400 - SMALL_PACKAGE_DISTANCE_THRESHOLD
            ):
                print(f"moveForwardEncoders {distance}")
                serial.write_line(f"moveForwardEncoders {distance} {speed} ")
            elif (
                closest_small_package_center[1]
                > 400 + SMALL_PACKAGE_DISTANCE_THRESHOLD
            ):
                print(f"moveBackwardEncoders {distance}")
                serial.write_line(f"moveBackwardEncoders {distance} {speed} ")
            else:
                break
                # pass

            if speed > 32:
                    speed = speed / 2

    while (False):
        object_positions = scan_for_objects(object_types=["small_package"])
        closest_small_package = max(
            (pos for obj, pos in object_positions if obj == "small_package"),
            default=None,
            key=lambda x: x[3],
        )

        if closest_small_package is None:
            print("No small packages found")
            continue

        closest_small_package_center = (
            (closest_small_package[0] + closest_small_package[2]) / 2,
            (closest_small_package[1] + closest_small_package[3]) / 2,
        )
        
        degree = (400 - closest_small_package_center[0]) / PIX_PER_DEG
        
        # print(f"Center: {closest_small_package_center[0]}, {closest_small_package_center[1]}: solveIK 0 {solveY(closest_small_package_center[1])} -1")

        if serial.is_waiting() or True:
            # degree = degree + 10
            
            if (
                closest_small_package_center[0]
                < 400 - SMALL_PACKAGE_WIDTH_THRESHOLD
            ):
                print(f"Moving to closest small package center: {closest_small_package_center[0]}, {closest_small_package_center[1]}")
                print(f"Rotate counter clockwise {degree:.2f} degrees at speed {speed}")
                serial.write_line(f"rotateCounterClockwise {degree:.2f} {speed} ")
            elif (
                closest_small_package_center[0]
                > 400 + SMALL_PACKAGE_WIDTH_THRESHOLD
            ):
                degree = degree * -1
                print(f"Moving to closest small package center: {closest_small_package_center[0]}, {closest_small_package_center[1]}")
                print(f"Rotate clockwise {degree} degrees at speed {speed}")
                serial.write_line(f"rotateClockwise {degree:.2f} {speed} ")
            else:
                break
                # pass

            if speed > 64:
                speed = speed / 2

    while not serial.is_waiting():
        pass
    sleep(5)
    print("Picking up the small package")
    # coords = input("Enter the coordinates of the small package: ")
    # serial.write_line(f"solveIK {coords} ")
    
    # while (True):
    #     scan_for_objects()
    #     closest_small_package_area = (closest_small_package[2] - closest_small_package[0]) * (closest_small_package[3] - closest_small_package[1])
    #     print(f"Center: {closest_small_package_center[0]}, {closest_small_package_center[1]}")
    #     print(f"Area: {closest_small_package_area}")
    #     command = input("Enter the coordinates of the small package: ")
    #     if command == "exit":
    #         break
    #     serial.write_line(f"{command} ")
    #     while not serial.is_waiting():
    #         pass


    serial.write_line(f"solveIK {solveX(closest_small_package_center[0])} {solveY(closest_small_package_center[1])} 3 ")
    while not serial.is_waiting():
        pass
    sleep(1)
    serial.write_line("pickupSmallPackage")
    while not serial.is_waiting():
        pass


def solveX(value):
    return 0.033 * value - 13.053

def solveY(value):
    return 11 / 400 * value


"""def old_main():
    model.load_state_dict(
        torch.load("./data/out/ieee/best_model.pth", map_location=DEVICE)[
            "model_state_dict"
        ]
    )
    model.to(DEVICE).eval()

    while not detect_start_signal():
        pass

    timer.start()

    # Collect the large package
    Wheels.rotate(-90)
    object_positions = scan_for_objects()
    for object, position in object_positions[0].items():
        if object == "large_package":
            # TODO: implement large package pickup
            pass

    # Collect the small package
    Wheels.rotate(-90)
    for object, position in object_positions[0].items():
        if object == "small_package":
            # TODO: implement small package pickup
            pass

    # Traverse ramps
    Wheels.rotate(180)
    # TODO: implement orienting the robot to the ramp using IMU, line following, or ultrasonics
    # TODO: implement climbing the 1st ramp
    Wheels.rotate(180)
    # TODO: implement descending the 2nd ramp

    # Deposit packages
    while Ultrasonic.get_distance(FRONT) > 10:
        Wheels.move_forward(10)
    Wheels.rotate(90)
    while Ultrasonic.get_distance(FRONT) > 10:
        Wheels.move_forward(10)
    Wheels.rotate(90)
    # TODO: implement depositing the packages

    # Collect Fuel Tanks
    Wheels.move_backwards(100)
    Wheels.rotate(-90)
    while Ultrasonic.get_distance(FRONT) > 10:
        Wheels.move_forward(10)
    Wheels.rotate(90)
    object_positions = scan_for_objects()
    for object, position in object_positions[0].items():
        if object == "fuel_tank":
            # TODO: implement fuel tank pickup
            pass

    # Cross the crater
    Wheels.rotate(180)
    # TODO: implement orienting the robot to the crater using IMU, line following, or ultrasonics
    # TODO: implement climbing the 1st ramp
    Wheels.rotate(180)
    # TODO: implement detaching the bridge
    # TODO: push the bridge into place and cross the crater
    Wheels.rotate(180)
    # TODO: implement descending the 2nd ramp

    # Assemble the thruster
    # TODO: implement team promotion display
    while Ultrasonic.get_distance(FRONT) > 10:
        Wheels.move_forward(10)
    Wheels.rotate(90)
    object_positions = scan_for_objects()
    for object, position in object_positions[0].items():
        if object == "thruster":
            # TODO: implement thruster assembly
            pass

    # Press the launch button
    while Ultrasonic.get_distance(FRONT) > 10:
        Wheels.move_forward(10)
    Wheels.move_forward()
    time.sleep(5)
    Wheels.stop()

    Timer.stop()
    print(f"Time taken: {timer.get_time()} seconds")

    # Save the time take to file named the current date and time
    with open(f"./data/out/{time.strftime('%Y-%m-%d_%H-%M-%S')}.txt", "w") as file:
        file.write(str(timer.get_time()))"""

if __name__ == "__main__":
    try:
        main()
    finally:
        if DEBUG_VIDEO_STREAM:
            client_socket.close()
