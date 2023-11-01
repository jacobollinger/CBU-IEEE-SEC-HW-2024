# Imports
import threading
import time
import RPi.GPIO as GPIO

# Define constants or configuration settings
GPIO.setmode(GPIO.BOARD)
servo_pin1 =  #right servo
servo_pin2 =  #left servo
GPIO.setup(servo_pin1, GPIO.OUT)
GPIO.setup(servo_pin2, GPIO.OUT)
servo1_lock = threading.Lock()
servo2_lock = threading.Lock()
wheel_circumference = # wheel_diameter * 3.14159265359
chasis_circumference = # chasis_diameter * 3.14159265359

# Degree calculation function
def degree(distance):
    return ((distance/wheel_circumference)*360.0)

# Wheel turn function
def move_servo( servo_pin, degrees):
    try:
        # Define PWM settings
        pwm_frequency = 50  # Hz
        pwm = GPIO.PWM(servo_pin, pwm_frequency)

        # Calculate duty cycle for the specified degree
        duty_cycle = (degrees / 180.0) * 10.0 + 2.5  # Mapping degrees to duty cycle (adjust as needed)

        # Start PWM with the calculated duty cycle
        pwm.start(duty_cycle)

        # Allow time for the servo to reach the desired position
        time.sleep(1)

        # Stop PWM
        pwm.stop()
    finally:
        pass

# Movement functions

def move_forward(distance):
    degree_for_servo1 = degree(distance)
    degree_for_servo2 = degree_for_servo1
    thread1 = threading.Thread(target=move_servo, args=(servo_pin1, degree_for_servo1,))
    thread2 = threading.Thread(target=move_servo, args=(servo_pin2, degree_for_servo2,))
    thread1.start()
    thread2.start()
    thread1.join()
    thread2.join()

def move_backward(distance):
    degree_for_servo1 = degree(distance)
    degree_for_servo2 = degree_for_servo1
    thread1 = threading.Thread(target=move_servo, args=(servo_pin1, degree_for_servo1,))
    thread2 = threading.Thread(target=move_servo, args=(servo_pin2, degree_for_servo2,))
    thread1.start()
    thread2.start()
    thread1.join()
    thread2.join()

def turn_left(angle):
    distance = chasis_circumference/wheel_circumference
    degree_for_servo1 = degree(distance)
    degree_for_servo2 = -1*(degree_for_servo1)
    thread1 = threading.Thread(target=move_servo, args=(servo_pin1, degree_for_servo1,))
    thread2 = threading.Thread(target=move_servo, args=(servo_pin2, degree_for_servo2,))
    thread1.start()
    thread2.start()
    thread1.join()
    thread2.join()

def turn_right(angle):
    distance = chasis_circumference/wheel_circumference
    degree_for_servo2 = degree(distance)
    degree_for_servo1 = -1*(degree_for_servo1)
    thread1 = threading.Thread(target=move_servo, args=(servo_pin1, degree_for_servo1,))
    thread2 = threading.Thread(target=move_servo, args=(servo_pin2, degree_for_servo2,))
    thread1.start()
    thread2.start()
    thread1.join()
    thread2.join()



