#include <Arduino.h>
#include <NewPing.h>
#include <Servo.h>

#include "./include/WheelControls.hpp"
#include "./include/WheelEncoder.hpp"


Servo myservo1; //servo for the small container d4
Servo myservo2; //servo for the large container d5
Servo myservo3; //servo for the bridge d13

int pos1 = 90; //servo1 position for setup
int pos2 = 0; //servo1 to drop container and bridge
int pos3 = 180; //servo3 position for the bridge
int pos4 = 50;  //servo2 posiiton for setup
int pos5 = 150; //servo2 to drop container

// const int trigPinFront = 26; // Ultrasonic sensor trigger pin
// const int echoPinFront = 27; // Ultrasonic sensor echo pin
// const int trigPinFront = 26; // Ultrasonic sensor trigger pin
// const int echoPinFront = 27; // Ultrasonic sensor echo pin

// NewPing sonarFront(trigPinFront, echoPinFront, 200); // NewPing object with a maximum distance of 200 inches

//const int leftSensorPin = A5;
//const int rightSensorPin = A6;






// Define threshold values for line following
//const int thresholdLeft = 470;  // Adjust this value based on your setup
//const int thresholdRight = 470; // Adjust this value based on your setup
//const int thresholdBack = 100;
// Intialize variables
// int prev_time = 0;
// float actual_speed1 = 0;
// float actual_speed2 = 0;

// const int M1DIR=25;
// //const int IN2=24;
// const int M1PWM=8;

// const int M2DIR=23;
// //const int IN4=22;
// const int M2PWM=7;

WheelControls wheelControls;

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting...");

    wheelControls = WheelControls();

    // Attach interrupts == Once a high ENCA is read pulse counting begins
    attachInterrupt(
        digitalPinToInterrupt(WHEELS_M1_ENCA), []()
        { wheelControls.updateLeftEncoder(); },
        RISING);
    attachInterrupt(
        digitalPinToInterrupt(WHEELS_M2_ENCA), []()
        { wheelControls.updateRightEncoder(); },
        RISING);

     myservo1.attach(4);
     myservo2.attach(5);
     myservo3.attach(13);

     servoInit(myservo1, pos1); 
     delay(500);
     servoInit(myservo3, pos2); 
     delay(500);
     servoInit(myservo2, pos4);
     delay(500);
}

void loop()
{
    Serial.println("Top of the loop");
    delay(50); // Small delay for stability

    // int distanceFront = sonarFront.ping_in();
    // distanceFront = sonarFront.ping_in();

    // int leftSensorValue = analogRead(leftSensorPin);
    // int rightSensorValue = analogRead(rightSensorPin);
    // int backSensorValue = analogRead(backSensorPin);

    // float current_time = millis();
    // float dt = current_time - prev_time;

    // int target_speed1 = 255;
    // int target_speed2 = -target_speed1;
    // int pos[2];

    // ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    // {
    // pos[0] = encoder1.getPosition();
    // pos[1] = encoder2.getPosition();
    // }
    // delay(1);
 
    // delay(10000);
    wheelControls.rotateCounterClockwise(15,100);
    delay(1000); 

    wheelControls.moveForwardEncoders(2,100);
    delay(5000);


    wheelControls.rotateCounterClockwise(65,100);
    delay(1000); 

    wheelControls.moveBackwardEncoders(1,100);
    delay(100);

    wheelControls.moveForwardEncoders(38.0, 400);
    delay(1000);

    wheelControls.rotateClockwise(180, 100); // 180 degrees
    delay(1000);

    Serial.println("Moving backwards...");
    wheelControls.moveBackwardEncoders(25.0, 35);
    delay(1000);

    Serial.println("Rotating counterclockwise...");
    //! Breaks here
    wheelControls.rotateCounterClockwise(80, 100);
    delay(1000);

    Serial.println("Moving ultrasonics forward...");
    wheelControls.moveUltrasonicsForward(3, 150);
    delay(2000);

    Serial.println("Rotating clockwise...");
    wheelControls.rotateCounterClockwise(90, 100);
    delay(1000);

    wheelControls.moveUltrasonicsForward(5, 150);
    delay(1000);

    wheelControls.rotateClockwise(90, 100);
    delay(1000);

    servoUnlock(myservo2, pos5);
    delay(100);

    wheelControls.rotateCounterClockwise(135, 100);
    delay(1000);

    servoUnlock(myservo1, pos2);
    delay(500);

    wheelControls.rotateClockwise(45, 100);
    delay(1000);

    Serial.println("UltraBackward...");
    wheelControls.moveUltrasonicsBackward(8, 150);
    delay(1000);

    wheelControls.rotateCounterClockwise(90, 100);
    delay(1000);

    wheelControls.lineFollowConstant(14.0, 100, 75, 75);
    delay(1000);




    wheelControls.moveUltrasonicsForward(6, 150);
    delay(100);

    wheelControls.rotateCounterClockwise(83, 100);
    delay(100);

    wheelControls.moveBackwardEncoders(6.0,150);
    delay(1000); 


    wheelControls.moveForwardEncoders(38.0,400);
    delay(2000); 


    wheelControls.rotateClockwise(180, 100);
    delay(100);


    wheelControls.moveBackwardUntilSensors(50,50);
    delay(100);

    wheelControls.moveForwardEncoders(1.0, 100);
    delay(100);

    servoUnlock(myservo3, pos3);
    delay(5000);


    wheelControls.moveForwardEncoders(4.0, 100);
    delay(1000);

    wheelControls.rotateClockwise(180, 100);
    delay(100);

    wheelControls.moveForwardEncoders(35.0, 100);
    delay(100);

    
    wheelControls.moveUltrasonicsForward(3, 100);
    delay(100);

    wheelControls.rotateClockwise(80, 100);
    delay(100);

   wheelControls.moveForwardEncoders(5.0, 200);
    delay(100);

    Serial.print("done");

    delay(100000);
}

// void readEncoder1()
// {
//     encoder1.update();
// }

// void readEncoder2()
// {
//     encoder2.update();
// }

void servoInit(Servo servoi, int initial_pos) {
  servoi.write(initial_pos);
  delay(100);
  //servoi.detach();
}
void servoUnlock( Servo servo, int pos_move){
 
  servo.write(pos_move);
  delay(500);
  servo.detach();
  }