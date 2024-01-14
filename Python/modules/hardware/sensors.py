import cv2
from gpio import GPIO
import time

class Camera:

    def __init__(self, camera_id):
        """Creates a camera object

        Args:
            camera_id (int): id of the camera to use
        """
        self.camera_id = camera_id
        self.cap = cv2.VideoCapture(camera_id)

    def get_image(self):
        """returns a single image from the camera

        Args:
            camera_id (int): id of the camera to use

        Returns:
            numpy.uint8: image from the camera
        """
        _, frame = self.cap.read()
        return frame

# TODO: Move this to a class that makes more sense
class Phototransistor:
    PIN = 0 # TODO: change this to the correct pin
    
    def detect_start_signal():
        # TODO: returns true if the green LED is on
        pass
    
class Ultrasonic:
    # Pins: [trigger, echo]
    FRONT = [0, 0] # TODO: change this to the correct pin
    BACK = [0, 0] # TODO: change this to the correct pin
    LEFT = [0, 0] # TODO: change this to the correct pin
    RIGHT = [0, 0] # TODO: change this to the correct pin
    
    def get_distance(pins):
            GPIO.output(pins[0], True)

            time.sleep(0.00001)
            GPIO.output(pins[0], False)
        
            start = time.time()
            end = time.time()

            while GPIO.input(pins[1]) == 0:
                start = time.time()

            while GPIO.input(pins[1]) == 1:
                end = time.time()

            time_elapsed = end - start
            
            # speed of sound: 34300 cm/s
            distance = (time_elapsed * 34300) / 2
        
            return distance
