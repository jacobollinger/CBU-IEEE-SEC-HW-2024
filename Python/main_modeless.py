from .actuators import Wheels, Arm, Containers, Bridge
from .sensors import Camera, Ultrasonic, Phototransistor, LineSensor
from .timer import Timer

def main():
    timer = Timer()
    
    while not Phototransistor.detect_start_signal():
        # Waiting for start signal
        pass

    timer.start()
    
    for i in range(5): # Number of large packages
        Wheels.turn_right(90)
        # TODO: Use arm to grab the right most package
        Wheels.turn_left(90)
        Wheels.move_forward(10) # TODO: Move forward x cm
        
    # TODO: Collect small packages
    
    while Ultrasonic.get_distance(Ultrasonic.FRONT)) > 10:
        Wheels.move_forward(10)
        
    Wheels.turn_right(90)
    
    while Ultrasonic.get_distance(Ultrasonic.FRONT) > 10:
        Wheels.move_forward(10)
    Wheels.move_forward(10)
    
    Wheels.turn_left(90)
    Containers.dump()
    
    Wheels.move_backwards(10)
    Wheels.turn_left(90)
    
    while Ultrasonic.get_distance(Ultrasonic.FRONT) > 10:
        Wheels.move_forward(10)
    Wheels.move_forward(10)
    
    Wheels.turn_right(90)
    
    # TODO: Collect fuel tanks
    
    Wheels.turn_left(180)
    
    # while the white line is not detected
    while not LineSensor.detect_line():
        Wheels.move_forward(1)
        
    Wheels.turn_left(180)
    Bridge.deploy()
    
    Wheels.turn_left(180)
    
    Wheels.move_forward(50) # get off ramp
    
    while Ultrasonic.get_distance(Ultrasonic.FRONT) > 10:
        Wheels.move_forward(10)
    Wheels.move_forward(10)
    
    Wheels.turn_left(90)
    for i in range(3) # number of thrusters
        # TODO: Place fuel tank on right most thruster
        Wheels.turn_left(90)
        Wheels.move_forward(10) # TODO: move forward x cm
        Wheels.turn_right(90)

    Wheels.turn_left(180)

    while True:
        Wheels.move_forward(100)
        Wheels.move_backwards(25)
        

if __name__ == "__main__":
    main()
