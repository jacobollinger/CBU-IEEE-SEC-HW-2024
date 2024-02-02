#ifndef ROBOT_ARM_CONTROL_H
#define ROBOT_ARM_CONTROL_H

#include <Servo.h>
#include <Arduino.h>

// Define the JointAngles structure
struct JointAngles {
    float base;
    float shoulder;
    float elbow;
    float wrist;
    float gripper;

    // Constructor to initialize the angles
    JointAngles(float initShoulder = 90.0, float initElbow = 90.0, float initWrist = 90.0, float initGripper = 90.0);
};

// Define the RobotArmControl class
class RobotArmControl {
public:
    RobotArmControl();
    void initialize();
    void updatePosition(const JointAngles& angles, const String& objective);
    JointAngles solveIK(float x, float y, float z);
    void calibrate();

private:
    Servo wristServo;
    Servo baseServo;
    Servo shoulderServo;
    Servo elbowServo;
    Servo gripperServo;
    const int wristPin = 8;
    const int basePin = 9;
    const int shoulderPin = 10;
    const int elbowPin = 11;
    const int gripperPin = 12;
    const int analogPinWrist = A0;
    const int analogPinBase = A1;
    const int analogPinShoulder = A2;
    const int analogPinElbow = A3;
    const int analogPinGripper = A4;
    const float j1 = 5;
    const float j2 = 5;
    float wristAngle = 180;
    float shoulderAngle;
    float elbowAngle;
    const int gripString = 13;
    const int gripLargePackage = 14;
    const int gripSmallPackage = 15;
    const int gripBooster = 16;
    const int gripRelease = 16;
    JointAngles dropOffAngles;
    JointAngles dropBridgeAngles;
    JointAngles initializeAngles;
    // Add any additional member variables or methods needed here.
};

#endif // ROBOT_ARM_CONTROL_H
