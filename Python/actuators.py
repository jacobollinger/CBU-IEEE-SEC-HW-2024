from math import degrees
import threading
import time
import Jetson.GPIO as GPIO

class Wheels:
    # Define constants or configuration settings
    GPIO.setmode(GPIO.BOARD)
    MOTOR_PIN1 = 2 # right motor, change as needed
    MOTOR_PIN2 = 3 # left motor, change as needed
    GPIO.setup(MOTOR_PIN1, GPIO.OUT)
    GPIO.setup(MOTOR_PIN2, GPIO.OUT)
    MOTOR1_LOCK = threading.Lock()
    MOTOR2_LOCK = threading.Lock()
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
    GPIO.setmode(GPIO.BOARD)
    SERVO_PIN = 4 # change as needed
    GPIO.setup(SERVO_PIN, GPIO.OUT)
    SERVO_LOCK = threading.Lock()

    # Degree calculation function for the arm
    def degree(self, distance):
        return ((distance / self.WHEEL_CIRCUMFERENCE) * 360.0)

    # Arm movement functions

    # Function that allows robot to move arm up
    def move_arm_up(self, distance):
        # For this function the arm will move up
        degree_for_motor = self.degree(distance)
        # Create thread for the motor
        thread = threading.Thread(target=self.move_motor, args=(self.SERVO_PIN, degree_for_motor,))
        # Start thread
        thread.start()
        # Wait for thread to finish
        thread.join()

    # Function that allows robot to move arm down
    def move_arm_down(self, distance):
        # For this function the arm will move down
        degree_for_motor = self.degree(distance)
        # Create thread for the motor
        thread = threading.Thread(target=self.move_motor, args=(self.SERVO_PIN, degree_for_motor,))
        # Start thread
        thread.start()
        # Wait for thread to finish
        thread.join()

    # Function that allows robot to move arm left
    def move_arm_left(self, distance):
        # For this function the arm will move left
        degree_for_motor = self.degree(distance)
        # Create thread for the motor
        thread = threading.Thread(target=self.move_motor, args=(self.SERVO_PIN, degree_for_motor,))
        # Start thread
        thread.start()
        # Wait for thread to finish
        thread.join()

    # Function that allows robot to move arm right
    def move_arm_right(self, distance):
        # For this function the arm will move right
        degree_for_motor = self.degree(distance)
        # Create thread for the motor
        thread = threading.Thread(target=self.move_motor, args=(self.SERVO_PIN, degree_for_motor,))
        # Start thread
        thread.start()
        # Wait for thread to finish
        thread.join()

    # Function that allows robot to move arm forward
    def move_arm_forward(self, distance):
        # For this
