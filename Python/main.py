from Python.modules.hardware.actuators import Wheels, Arm
from Python.modules.hardware.sensors import Camera, Phototransistor, Ultrasonic
from Python.modules.model.ml import GameObjectModel, GameObjectDataset

model = GameObjectModel(True)

def main():
    timer = Timer()
    
    while not Phototransistor.detect_start_signal():
        pass
    
    timer.start()
    
    prediction = model.classify_image(Camera.get_image(0))


def contains_object(object, image):
    """parent function for all object detection functions

    Args:
        object (String): name of the object to detect
        image (numpy.uint8): image to detect the object in

    Returns:
        bool: whether or not the object was detected
        int: number of times the object was detected
    """
    predictions = model.classify_image_h(image)
    return object in predictions, predictions.count(object)


def contains_large_package(image):
    """detects if a large package is in the image

    Args:
        image (numpy.uint8): image to detect the object in

    Returns:
        bool: whether or not the object was detected
        int: number of times the object was detected
    """
    return contains_object("large_package", image)


def contains_small_package(image):
    """detects if a small package is in the image
    
    Args:
        image (numpy.uint8): image to detect the object in
        
    Returns:
        bool: whether or not the object was detected
        int: number of times the object was detected
    """
    return contains_object("small_package", image)


def contains_fuel_tank(image):
    """detects if a fuel tank is in the image

    Args:
        image (numpy.uint8): image to detect the object in

    Returns:
        bool: whether or not the object was detected
        int: number of times the object was detected
    """
    return contains_object("fuel_tank", image)


def contains_thruster(image):
    """detects if a thruster is in the image

    Args:
        image (numpy.uint8): image to detect the object in

    Returns:
        bool: whether or not the object was detected
        int: number of times the object was detected
    """
    return contains_object("thruster", image)


def contains_package_delivery_zone(image):
    # TODO: implement
    pass


def contains_fuel_tank_pickup(image):
    # TODO: implement
    pass


def contains_crater_marking(image):
    # TODO: implement
    pass


def contains_fuel_tank_delivery_zone(image):
    # TODO: implement
    pass


if __name__ == "__main__":
    main()
