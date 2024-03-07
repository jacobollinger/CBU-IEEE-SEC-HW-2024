#include <Arduino.h>
#include <Encoder.h>
#include <PID.h>
#include <util/atomic.h>
#include "CytronMotorDriver.h"

// Define motor pins
//const int leftMotorPWM = 6;    // PWM pin for left motor speed control
//const int leftMotorDir = 7;    // Direction pin for left motor
//const int rightMotorPWM = 9;   // PWM pin for right motor speed control
//const int rightMotorDir = 8;   // Direction pin for right motor
CytronMD motor1(PWM_DIR, 6, 7);  // PWM 1 = Pin 6, DIR 1 = Pin 7.
CytronMD motor2(PWM_DIR, 9, 8); // PWM 2 = Pin 9, DIR 2 = Pin 8.
// Define line follower sensor pins
const int leftSensorPin = A5;
const int rightSensorPin = A6;
const int backRightSensorPin = A7;
const int backLeftSensorPin = A8;


// Define threshold values for line following
const int thresholdLeft = 470;   // Adjust this value based on your setup
const int thresholdRight = 470;  // Adjust this value based on your setup
const int backRightSensorPin = 100;
const int backLeftSensorPin = 100;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

//  // Set motor pins as outputs
//  pinMode(leftMotorPWM, OUTPUT);
//  pinMode(leftMotorDir, OUTPUT);
//  pinMode(rightMotorPWM, OUTPUT);
//  pinMode(rightMotorDir, OUTPUT);
}

void loop() {
  // Read sensor values
  int leftSensorValue = analogRead(leftSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);
  int backRightSensorValue = analogRead(backRightSensorPin);
  int backLeftSensorValue = analogRead(backLeftSensorPin);

  // Debugging information
  Serial.println("Left Sensor: ");
  Serial.println(leftSensorValue);
  Serial.println(" | Right Sensor: ");
  Serial.println(rightSensorValue);

  // Check the line following conditions
  if (leftSensorValue < thresholdLeft && rightSensorValue < thresholdRight) {
    // Both sensors on the line - move forward
    moveForward();
  } else if (leftSensorValue < thresholdLeft) {
    // Left sensor on the line - turn right
    turnRight();
  } else if (rightSensorValue < thresholdRight) {
    // Right sensor on the line - turn left
    turnLeft();
  } else {
    // Both sensors off the line - stop
    stopMotors();
  }
}

void moveForward() {
 motor1.setSpeed(150);   // Motor 1 runs forward at 50% speed.
 motor2.setSpeed(150);  // Motor 2 runs backward at 50% speed.
}

void turnLeft() {
  motor1.setSpeed(-100);   // Motor 1 runs forward at 50% speed.
 motor2.setSpeed(100);  // Motor 2 runs backward at 50% speed.
}

void turnRight() {
  motor1.setSpeed(100);   // Motor 1 runs forward at 50% speed.
 motor2.setSpeed(-100);  // Motor 2 runs backward at 50% speed.
}

void stopMotors() {
  motor1.setSpeed(0);   // Motor 1 runs forward at 50% speed.
 motor2.setSpeed(0);  // Motor 2 runs backward at 50% speed.
}
