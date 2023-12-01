try:
    import Jetson.GPIO as GPIO
except ImportError:
    try:
        import RPi.GPIO as GPIO
    except ImportError:
        class GPIO:
            BOARD = None
            OUT = None
            PWM = None

            @staticmethod
            def setmode(*args):
                # This method is intentionally left empty.
                pass

            @staticmethod
            def setup(*args):
                # This method is intentionally left empty.
                pass

            @staticmethod
            def PWM(*args):
                # This method is intentionally left empty.
                pass

GPIO.setmode(GPIO.BCM) # Use BCM GPIO numbers