import torch

from Python.modules.hardware.actuators import Wheels, Arm
from Python.modules.hardware.sensors import Camera, Phototransistor, Ultrasonic
from Python.modules import Timer
from Python.custom_object_detection_ieee.src.model import create_model
from Python.custom_object_detection_ieee.src.config import NUM_CLASSES, DEVICE, CLASSES

armCamera = Camera(0)
fixedCamera = Camera(1)
model = create_model(num_classes=NUM_CLASSES, size=640)
timer = Timer()


def main():
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
        file.write(str(timer.get_time()))


def detect_start_signal():
    """detects the start signal

    Returns:
        bool: whether or not the start signal was detected
    """
    return Phototransistor.detect_start_signal()


def scan_for_objects():
    """scans for objects in the environment

    Returns:
        dict: dictionary of objects detected and their positions from the fixed camera
        dict: dictionary of objects detected and their positions from the arm camera
    """
    images = fixedCamera.get_image(), armCamera.get_image()
    with torch.no_grad():
        outputs = model(images.to(DEVICE))
    if len(outputs[0]["boxes"]) == 0:
        fixed_ret = {}
    else:
        # TODO: implement
        pass
    if len(outputs[1]["boxes"]) == 0:
        arm_ret = {}
    else:
        # TODO: implement
        pass

    return fixed_ret, arm_ret


if __name__ == "__main__":
    main()
