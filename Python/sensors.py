import cv2

class Camera:

    STATIC_CAM = 0
    ARM_CAM = 1

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
    def detect_start_signal():
        # TODO: returns true if the green LED is on
        pass