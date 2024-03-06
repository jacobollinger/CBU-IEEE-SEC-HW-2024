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

fixedCamera = Camera()
model = create_model(num_classes=NUM_CLASSES, size=640)
timer = Timer()
serial = SerialInterface("/dev/tty.usbserial-14410", 9600)


def main():
    model.load_state_dict(
        torch.load("./data/out/ieee/best_model.pth", map_location=DEVICE)[
            "model_state_dict"
        ]
    )
    model.to(DEVICE).eval()

    serial.start()

    sleep(2)

    # Wait for the start signal
    print("Waiting for start signal")
    while not detect_start_signal():
        pass

    print("GO!")
    timer.start()

    # Collect the large package
    collect_large_packages()

    # Collect the small package
    collect_small_packages()

    # Traverse ramps
    traverse_ramps()

    # Deposit packages
    go_to_deposit_location()
    deposit_packages()

    # Collect Fuel Tanks
    go_to_fuel_tank_location()
    collect_fuel_tanks()

    # Cross the crater
    cross_crater()

    # Assemble the thrusters
    display_team_promotion()
    while Ultrasonic.get_distance(FRONT) > 10:
        Wheels.move_forward(10)
    Wheels.rotate(90)
    assemble_thrusters()

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


def old_main():
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
    """Detects the start signal

    Returns:
        bool: whether or not the start signal was detected
    """
    return serial.read_line() == "START"


def scan_for_objects():
    """Scans for objects in the environment

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


def collect_large_packages():
    """Collects the large packages from the environment"""
    object_positions = scan_for_objects()
    for object, position in object_positions[0].items():
        if object == "large_package":
            # TODO: implement large package pickup
            Arm.move_to(position)
            Arm.pickup("large_package")
            Arm.move_to("large_package_container")
            Arm.release()

    Arm.move_to("home")


def collect_small_packages():
    """Collects the small packages from the environment"""
    object_positions = scan_for_objects()
    for object, position in object_positions[0].items():
        if object == "small_package":
            # TODO: implement large package pickup
            Arm.move_to(position)
            Arm.pickup("small_package")
            Arm.move_to("small_package_container")
            Arm.release()
            Arm.move_to("home")


def traverse_ramps():
    # TODO: implement orienting the robot to the ramp using IMU, line following, or ultrasonics
    # TODO: implement climbing the 1st ramp
    Wheels.rotate(180)
    # TODO: implement descending the 2nd ramp


def deposit_packages():
    # TODO: implement depositing the packages
    pass


def collect_fuel_tanks():
    """Collects the fuel tanks from the environment"""
    object_positions = scan_for_objects()
    for object, position in object_positions[0].items():
        if object == "fuel_tank":
            # TODO: implement fuel tank pickup
            Arm.move_to(position)
            Arm.pickup("fuel_tank")
            Arm.move_to("home")


def cross_crater():
    # TODO: implement orienting the robot to the crater using line following
    # TODO: implement climbing the 1st ramp
    Wheels.rotate(180)
    # TODO: implement detaching the bridge
    # TODO: push the bridge into place and cross the crater
    Wheels.rotate(180)
    # TODO: implement descending the 2nd ramp


def display_team_promotion():
    # TODO: implement team promotion display
    pass


def assemble_thrusters():
    """Assembles the thrusters"""
    object_positions = scan_for_objects()
    for object, position in object_positions[0].items():
        if object == "thruster":
            # TODO: implement thruster assembly
            Arm.move_to("fuel_tank")
            Arm.pickup("fuel_tank")
            Arm.move_to(position)
            Arm.release()

    Arm.move_to("home")


if __name__ == "__main__":
    main()
