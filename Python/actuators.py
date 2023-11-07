import threading
import time
import Jetson.GPIO as GPIO

class Wheels:
    # Define constants or configuration settings
    # Set the pin numbering scheme to the numbering shown on the robot itself
    GPIO.setmode(GPIO.BOARD)
    # The pins for the motors will be defined here
    MOTOR_PIN1 = 2 # right motor, change as needed
    MOTOR_PIN2 = 3 # left motor, change as needed
    # Set the pins as outputs
    GPIO.setup(MOTOR_PIN1, GPIO.OUT)
    GPIO.setup(MOTOR_PIN2, GPIO.OUT)
    # Create locks for the motors
    MOTOR1_LOCK = threading.Lock()
    MOTOR2_LOCK = threading.Lock()
    # Define constants for the wheels
    WHEEL_CIRCUMFERENCE = .08 * 3.14159265359 # 80mm is the radius of the wheel
    CHASIS_CIRCUMFERENCE = 5 * 3.14159265359 # 5 is the distance between the wheels, change later

    # Degree calculation function for the wheels
    def degree(self, distance):
        return ((distance / self.WHEEL_CIRCUMFERENCE) * 360.0)

    # Wheel turn function
    def move_motor(self, motor_pin, degrees):
        try:
            # Define PWM settings for the motor
            pwm_frequency = 50  # Hz
            pwm = GPIO.PWM(motor_pin, pwm_frequency)
            # Calculate duty cycle for the specified degree
            duty_cycle = (degrees / 180.0) * 10.0 + 2.5  # Mapping degrees to duty cycle (adjust as needed)
            # Start PWM with the calculated duty cycle
            pwm.start(duty_cycle)
            # Allow time for the motor to reach the desired position, will be changed later
            time.sleep(1)
            # Stop PWM
            pwm.stop()
        finally:
            pass


    # Movement functions

    # Function that allows robot to move forward
    def move_forward(self, distance):
        # For this function both motors will move forward
        degree_for_motor1 = self.degree(distance)
        degree_for_motor2 = degree_for_motor1
        # Create threads for each motor
        thread1 = threading.Thread(target=self.move_motor, args=(self.MOTOR_PIN1, degree_for_motor1,))
        thread2 = threading.Thread(target=self.move_motor, args=(self.MOTOR_PIN2, degree_for_motor2,))
        # Start threads
        thread1.start()
        thread2.start()
        # Wait for threads to finish
        thread1.join()
        thread2.join()

    # Function that allows robot to move backwards
    def move_backwards(self, distance):
        # For this function both motors will move backwards
        degree_for_motor1 = self.degree(distance)
        degree_for_motor2 = degree_for_motor1
        # Create threads for each motor
        thread1 = threading.Thread(target=self.move_motor, args=(self.MOTOR_PIN1, degree_for_motor1,))
        thread2 = threading.Thread(target=self.move_motor, args=(self.MOTOR_PIN2, degree_for_motor2,))
        # Start threads
        thread1.start()
        thread2.start()
        # Wait for threads to finish
        thread1.join()
        thread2.join()

    # Function that allows robot to turn left
    def turn_left(self, angle):
        # Calculate the distance that the wheels need to move based on the angle
        distance = (self.CHASIS_CIRCUMFERENCE/360)*angle
        # For this function the right motor will move forward and the left motor will move backwards
        degree_for_motor1 = self.degree(distance)
        degree_for_motor2 = -1 * (degree_for_motor1)
        # Create threads for each motor
        thread1 = threading.Thread(target=self.move_motor, args=(self.MOTOR_PIN1, degree_for_motor1,))
        thread2 = threading.Thread(target=self.move_motor, args=(self.MOTOR_PIN2, degree_for_motor2,))
        # Start threads
        thread1.start()
        thread2.start()
        # Wait for threads to finish
        thread1.join()
        thread2.join()

    def turn_right(self, angle):
        # Calculate the distance that the wheels need to move based on the angle
        distance = (self.CHASIS_CIRCUMFERENCE / 360) * angle
        # For this function the left motor will move forward and the right motor will move backwards
        degree_for_motor2 = self.degree(distance)
        degree_for_motor1 = -1 * (degree_for_motor1)
        # Create threads for each motor
        thread1 = threading.Thread(target=self.move_motor, args=(self.MOTOR_PIN1, degree_for_motor1,))
        thread2 = threading.Thread(target=self.move_motor, args=(self.MOTOR_PIN2, degree_for_motor2,))
        # Start threads
        thread1.start()
        thread2.start()
        # Wait for threads to finish
        thread1.join()
        thread2.join()

class Arm:
    # Define constants or configuration settings
    # Set the pin numbering scheme to the numbering shown on the robot itself
    GPIO.setmode(GPIO.BOARD)
    # The pins for the servos will be defined here
    SERVO_PIN1 = 4 # 360 degree base (YAW), change as needed
    SERVO_PIN2 = 5 # Sholder joint servo (PITCH), change as needed
    SERVO_PIN3 = 6 # Elbow joint servo (PITCH), change as needed
    SERVO_PIN4 = 7 # 360 degree wrist servo (ROLL), change as needed
    SERVO_PIN5 = 8 # Wrist joint servo (PITCH), change as needed
    SERVO_PIN6 = 9 # Grabber servo, change as needed
    # Set the pins as outputs
    GPIO.setup(SERVO_PIN1, GPIO.OUT)
    GPIO.setup(SERVO_PIN2, GPIO.OUT)
    GPIO.setup(SERVO_PIN3, GPIO.OUT)
    GPIO.setup(SERVO_PIN4, GPIO.OUT)
    GPIO.setup(SERVO_PIN5, GPIO.OUT)
    GPIO.setup(SERVO_PIN6, GPIO.OUT)
    # Create locks for the servos
    SERVO1_LOCK = threading.Lock()
    SERVO2_LOCK = threading.Lock()
    SERVO3_LOCK = threading.Lock()
    SERVO4_LOCK = threading.Lock()
    SERVO5_LOCK = threading.Lock()
    SERVO6_LOCK = threading.Lock()
    # Define constants for the arm
    # Set Later

    # Degree calculation function for the arm
    def degree(self, distance):
        return ((distance / self.WHEEL_CIRCUMFERENCE) * 360.0)

    # Arm movement functions
    
    def rotate_base(degrees):
    # Code to rotate base servo to the specified degrees

    def move_shoulder(angle):
    # Code to move shoulder servo to the specified angle

    def bend_elbow(angle):
    # Code to move elbow servo to the specified angle

    def rotate_wrist(degrees):
    # Code to rotate wrist servo

    def flex_wrist(angle):
    # Code to move wrist flex servo

    def actuate_gripper(open_close):
    # Code to open or close the gripper servo