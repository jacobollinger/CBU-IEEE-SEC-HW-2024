import cv2
from gpio import GPIO
import time

class Camera:

    STATIC_CAM_PIN = 0 # TODO: change this to the correct pin
    ARM_CAM_PIN = 0 # TODO: change this to the correct pin

    def get_image(camera_id):
        """returns a single image from the camera

        Args:
            camera_id (int): id of the camera to use

        Returns:
            numpy.uint8: image from the camera
        """
        with cv2.VideoCapture(camera_id) as cap:
            _, frame = cap.read()
            return frame

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