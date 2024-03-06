#include <Arduino.h>
#include <NewPing.h>

#include "./include/WheelControls.hpp"
#include "./include/WheelEncoder.hpp"

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

    
    wheelControls.moveForwardEncoders(32.0, 400);
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
    wheelControls.rotateCounterClockwise(80, 100);
    delay(1000);

    wheelControls.moveUltrasonicsForward(4, 150);
    delay(1000);

    wheelControls.rotateClockwise(45, 100);
    delay(1000);

    wheelControls.rotateCounterClockwise(90, 100);
    delay(1000);

    wheelControls.rotateClockwise(45, 100);
    delay(1000);

    Serial.println("UltraBackward...");
    wheelControls.moveUltrasonicsBackward(8, 150);
    delay(1000);

    wheelControls.rotateCounterClockwise(90, 100);
    delay(1000);

    wheelControls.lineFollowConstant(10.0, 100, 75, 75);
    delay(1000);

    wheelControls.moveUltrasonicsForward(6, 150);
    delay(1000);

    wheelControls.rotateCounterClockwise(90, 100);
    delay(1000);

    wheelControls.moveForwardEncoders(30.0,400);
    delay(100); 


    wheelControls.rotateClockwise(180, 100);
    delay(100);

    wheelControls.lineFollowConstant(4.0, 50, 50, 50);
    delay(100);

    wheelControls.moveBackwardUntilSensor(100,100);
    delay(10000);
    

    // dropbridge()

    // wheelControls.moveForwardEncoders(3.0, 20);
    // delay(10);

    // wheelControls.moveBackwardEncoders(20.0, 25);
    // delay(100);

    // wheelControls.rotateClockwise(180, 100);
    // delay(100);

    // wheelControls.moveUltrasonics(1, 100);
    // delay(100);

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
