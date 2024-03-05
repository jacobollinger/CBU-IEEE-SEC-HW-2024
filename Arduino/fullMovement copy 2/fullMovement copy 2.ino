#include <Arduino.h>

#include "./include/WheelControls.hpp"
#include "./include/WheelEncoder.hpp"

// const int trigPinFront = 26; // Ultrasonic sensor trigger pin
// const int echoPinFront = 27; // Ultrasonic sensor echo pin
// const int trigPinFront = 26; // Ultrasonic sensor trigger pin
// const int echoPinFront = 27; // Ultrasonic sensor echo pin

// NewPing sonarFront(trigPinFront, echoPinFront, 200); // NewPing object with a maximum distance of 200 inches

// const int leftSensorPin = A5;
// const int rightSensorPin = A6;

// Define threshold values for line following
// const int thresholdLeft = 470;  // Adjust this value based on your setup
// const int thresholdRight = 470; // Adjust this value based on your setup

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
    Serial.begin(4800);
    Serial.println("Starting...");

    // wheelControls = WheelControls();

    // Attach interrupts == Once a high ENCA is read pulse counting begins
    // attachInterrupt(digitalPinToInterrupt(WHEELS_M1_ENCA), [](){ wheelControls.updateLeftEncoder(); }, RISING);
    // attachInterrupt(digitalPinToInterrupt(WHEELS_M2_ENCA), [](){ wheelControls.updateRightEncoder(); }, RISING);
}

void loop()
{
    Serial.println("Top of the loop");
    delay(50); // Small delay for stability

    // int distanceFront = sonarFront.ping_in();
    // distanceFront = sonarFront.ping_in();

    // int leftSensorValue = analogRead(leftSensorPin);
    // int rightSensorValue = analogRead(rightSensorPin);

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

    // lineFollowerFoward(32.0,75,100,100); // distance, fowardspeed, rightturn speed, leftturn speed
    /*wheelControls.moveForwardEncoders(32.0, 70);
    delay(100);

    wheelControls.rotateClockwise(192, 100); // 180 degrees
    delay(100);

    wheelControls.moveBackwardEncoders(25.0, 35);
    delay(100);

    //! Breaks here
    wheelControls.rotateCounterClockwise(90, 100);
    delay(100);

    wheelControls.moveUltrasonicsForward(3, 150);
    delay(100);

    wheelControls.rotateCounterClockwise(90, 100);
    delay(100);

    wheelControls.moveUltrasonicsForward(4, 150);
    delay(100);

    wheelControls.rotateClockwise(45, 100);
    delay(100);

    wheelControls.rotateCounterClockwise(90, 100);
    delay(100);

    wheelControls.rotateClockwise(45, 100);
    delay(100);

    wheelControls.moveUltrasonicsForward(8, 150);
    delay(100);

    wheelControls.rotateCounterClockwise(90, 100);
    delay(100);

    wheelControls.lineFollowConstant(10.0, 100, 75, 75);
    delay(100);

    wheelControls.moveUltrasonicsForward(4, 150);
    delay(100);

    wheelControls.rotateClockwise(90, 100);
    delay(100);

    wheelControls.moveUltrasonicsForward(3, 150);
    delay(100);

    wheelControls.moveUltrasonicsForward(10, 150);
    delay(100);

    wheelControls.rotateCounterClockwise(90, 100);
    delay(100);

    wheelControls.moveUltrasonicsForward(6, 150);
    delay(100);

    wheelControls.rotateCounterClockwise(90, 100);
    delay(100);

    // wheelControls.lineFollow(30.0, 150, 150, 50);
    wheelControls.lineFollowConstant(30.0, 150, 150, 50);
    delay(5000);

    wheelControls.rotateClockwise(190, 100);
    delay(100);

    wheelControls.lineFollowConstant(4.0, 50, 50, 50);
    delay(100);

    wheelControls.moveBackwardEncoders(4.0, 20);
    delay(10000);
    */

    // dropbridge()

    // wheelControls.moveForwardEncoders(3.0, 20);
    // delay(10);

    // wheelControls.moveBackwardEncoders(20.0, 25);
    // delay(100);

    // wheelControls.rotateClockwise(180, 100);
    // delay(100);

    // wheelControls.moveUltrasonics(1, 100);
    // delay(100);

    // wheelControls.rotateClockwise(90, 100);
    // delay(100);

    // wheelControls.moveUltrasonics(1, 100);
    // delay(100);

    //   sonarDistance(5,100); // distance, speed
    //   delay(100);
    //   encoder1.clrEncoder();
    //   encoder2.clrEncoder();

    //   delay (10);

    //   rotateClockwise(pos,180,100);
    //   encoder1.clrEncoder();
    //   encoder2.clrEncoder();

    //   delay (10);

    //   moveBackward(pos);
    //   encoder1.clrEncoder();
    //   encoder2.clrEncoder();

    //   delay(10);

    //   rotateCounterClockwise(pos, 90, 50);
    //   int distanceFront = sonarFront.ping_in();
    //   distanceFront = sonarFront.ping_in();
    //   encoder1.clrEncoder();
    //   encoder2.clrEncoder();

    //   delay(10);

    //    function6(distanceFront); // moves 5in from wall

    //   delay (10);

    //   encoder1.clrEncoder(); // clears encoders pos
    //   encoder2.clrEncoder(); // clears encoder pos
    //   rotateCounterClockwise(pos,90,150);
    //   distanceFront = sonarFront.ping_in();
    //   delay (10);

    //   function8(distanceFront); // move 4in from wall
    //   encoder1.clrEncoder(); // clears encoder pos
    //   encoder2.clrEncoder(); // clears encoder pos
    //   delay (10);

    //   rotateClockwise(pos,45,150); // turns 45 degrees clockwise
    //   encoder1.clrEncoder(); // clears encoder pos
    //   encoder2.clrEncoder(); // clears encoder pos
    //   delay (10);

    //   rotateCounterClockwise(pos,90,200); // turns 90 degrees counterclockwise
    //   encoder1.clrEncoder(); // clears encoder pos
    //   encoder2.clrEncoder(); // clears encoder pos
    //   delay(10);

    //   rotateClockwise(pos,45,50); // turns 45 degrees counterclockwise
    //   delay(10);

    //   function12(distanceFront);
    //   encoder1.clrEncoder(); // clears encoder pos
    //   encoder2.clrEncoder(); // clears encoder pos
    //   delay(10);

    //   rotateCounterClockwise(pos,90,150);
    //   delay(10);

    //   function13(distanceFront);
    //   encoder1.clrEncoder(); // clears encoder pos
    //   encoder2.clrEncoder(); // clears encoder pos
    //   delay(10);

    //   rotateClockwise(pos,90,100);
    //   delay(10);

    //   function14(distanceFront);
    //   encoder1.clrEncoder(); // clears encoder pos
    //   encoder2.clrEncoder(); // clears encoder pos
    //   delay(10);

    //   rotateCounterClockwise(pos, 180,100);
    //   encoder1.clrEncoder(); // clears encoder pos
    //   encoder2.clrEncoder(); // clears encoder pos
    //   delay(10);

    //   move32in(pos, target_speed1);
    //   encoder1.clrEncoder(); // clears encoder pos
    //   encoder2.clrEncoder(); // clears encoder pos
    //   delay(10);

    //   rotateClockwise(pos,185,100);
    //   encoder1.clrEncoder();
    //   encoder2.clrEncoder();
    //   delay(10);

    //   moveBackwardSlow(pos);
    //   encoder1.clrEncoder();
    //   encoder2.clrEncoder();
    //   delay (10);

    //   rotateClockwise(pos, 180, 100);
    //   delay(10);

    //   Serial.print("done");

    delay(100000);
}

/*

void lineFollowerBackward(float targetDistance, int speed, int right, int left)
{
    const float inchesPerRevolution = 32.0 / 7100.0;

    int pos[2];
    encoder1.clear(); // clears encoder pos
    encoder2.clear(); // clears encoder pos
    const float targetRotations = targetDistance / inchesPerRevolution;
    int leftSensorValue = analogRead(leftSensorPin);
    int rightSensorValue = analogRead(rightSensorPin);

    // Debugging information
    Serial.print("Motor 1 Position: ");
    Serial.print(pos[0]);
    Serial.print("\t");
    Serial.print("Motor 2 Position: ");
    Serial.println(pos[1]);
    speed < 400 ? speed += 25 : speed = 400;
    while (pos[1] > -targetRotations)
    {

        // Read encoder positions
        pos[0] = encoder1.getPosition();
        pos[1] = -encoder2.getPosition();

        int leftSensorValue = analogRead(leftSensorPin);
        int rightSensorValue = analogRead(rightSensorPin);

        // Debugging information
        Serial.print("Left Sensor: ");
        Serial.print(leftSensorValue);
        Serial.print("\t");
        Serial.print("  Right Sensor: ");
        Serial.println(rightSensorValue);
        speed < 400 ? speed += 15 : speed = 400;

        if (leftSensorValue < thresholdLeft && rightSensorValue < thresholdRight)
        {
            // Both sensors on the line - move forward
            md.setM1Speed(-speed);
            md.setM2Speed(-speed);
        }
        else if (leftSensorValue < thresholdLeft)
        {
            // Left sensor on the line - turn right
            md.setM1Speed(-right);
            md.setM2Speed(right);
        }
        else if (rightSensorValue < thresholdRight)
        {
            // Right sensor on the line - turn left
            md.setM1Speed(left);
            md.setM2Speed(-left);
        }
        else
        {
            // Both sensors off the line - stop
            md.setM1Speed(0);
            md.setM2Speed(0);
        }
    }

    // Stop the motors if the target rotations are reached
    md.setM1Speed(0);
    md.setM2Speed(0);
    Serial.println("Target rotations reached. Stopping.");
}
*/

// void centerBot() {
//   const int targetDistance = 5; // Target distance in inches

//   // Read distances from ultrasonic sensors
//   float distanceFront = sonarFront.ping_in();
//   float distanceRight = sonarRight.ping_in();

//   // Check if both sensors have a value of 5 inches
//   if (distanceFront == targetDistance && distanceRight == targetDistance) {
//     float distanceFront = sonarFront.ping_in();
//     float distanceRight = sonarRight.ping_in();
//     md.setM1Speed(0);
//     md.setM2Speed(0); // Stop the bot
//   } else {
//     // Check if the right sensor has a value greater than 5 inches
//     if (distanceRight > targetDistance) {
//       float distanceFront = sonarFront.ping_in();
//       float distanceRight = sonarRight.ping_in();
//       // Adjust motor speeds to decrease the right sensor value to 5 inches
//       Serial.print("Right Distance: ");
//       Serial.print(distanceRight);
//       Serial.println(" inches");
//       md.setM1Speed(0);
//       md.setM2Speed(100);
//     } else if (distanceRight < targetDistance) {
//       float distanceFront = sonarFront.ping_in();
//       float distanceRight = sonarRight.ping_in();
//       // Move left if the right sensor has a value less than 5 inches
//       Serial.print("Right Distance2: ");
//       Serial.print(distanceRight);
//       Serial.println(" inches");
//       md.setM1Speed(100);
//       md.setM2Speed(0);
//       } else if (distanceFront > targetDistance) {
//         float distanceFront = sonarFront.ping_in();
//        float distanceRight = sonarRight.ping_in();
//       // Move forward if the front sensor has a value greater than 5 inches
//       md.setM1Speed(100);
//       md.setM2Speed(100); // Example: Move both motors forward
//     }else{
//       md.setM1Speed(0);
//       md.setM2Speed(0);
//     }
//   }
// }

// void readEncoder1()
// {
//     encoder1.update();
// }

// void readEncoder2()
// {
//     encoder2.update();
// }
