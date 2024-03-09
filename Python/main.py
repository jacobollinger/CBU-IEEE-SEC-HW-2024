import cv2
import numpy as np
import torch


from modules.hardware.actuators import Wheels, Arm
from modules.hardware.sensors import Camera, Phototransistor, Ultrasonic
from modules.hardware.serial import SerialInterface
from modules.timer import Timer
from custom_object_detection_ieee.src.model import create_model
from custom_object_detection_ieee.src.config import NUM_CLASSES, DEVICE, CLASSES

from time import sleep

DEBUG_VIDEO_STREAM = False
DEBUG_IMSHOW = True

fixedCamera = Camera()
model = create_model(num_classes=NUM_CLASSES, size=640)
timer = Timer()
# serial = SerialInterface("/dev/ttyACM0", 9600)


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


def main():
    model.load_state_dict(
        torch.load("./data/out/ieee/e273_BEST/best_model.pth", map_location=DEVICE)[
            "model_state_dict"
        ]
    )
    model.to(DEVICE).eval()

    # serial.start()

    # Wait for signal from the Arduino to pick up the small packages
    # print("Waiting for start signal")
    # while not detect_start_signal():
    #     pass

    # Collect the small package
    collect_small_packages()

    # Handover control to the Arduino to do everything else
    # serial.write_line("done")


def detect_start_signal():
    """Detects the start signal

    Returns:
        bool: whether or not the start signal was detected
    """
    return serial.read_line() == "START"


def scan_for_objects(
    threshold=0.5,
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

            for j, box in enumerate(boxes):
                class_name = CLASSES[output["labels"][j].cpu().numpy()]
                if class_name not in object_types:
                    continue
                fixed_ret.append([class_name, box])
                if DEBUG_VIDEO_STREAM or DEBUG_IMSHOW:
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


def collect_small_packages():
    """Collects the small packages from the environment"""
    while True:
        object_positions = scan_for_objects(object_types=["small_package"])
        print(f"Object positions: {object_positions}")
        closest_small_package = max(
            (pos for obj, pos in object_positions if obj == "small_package"),
            default=None,
            key=lambda x: x[3],
        )
        print(f"Closest small package: {closest_small_package}")

        # for object, position in object_positions:
        # TODO: implement large package pickup
        # Arm.move_to(position)
        # Arm.pickup("small_package")
        # Arm.move_to("small_package_container")
        # Arm.release()
        print()

    # Arm.move_to("home")


def collect_fuel_tanks():
    """Collects the fuel tanks from the environment"""
    # object_positions = scan_for_objects()
    # for object, position in object_positions[0].items():
    #     if object == "fuel_tank":
    #         # TODO: implement fuel tank pickup
    #         Arm.move_to(position)
    #         Arm.pickup("fuel_tank")
    #         Arm.move_to("home")
    pass


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
    main()
