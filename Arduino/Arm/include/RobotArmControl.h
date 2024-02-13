#ifndef ROBOT_ARM_CONTROL_H
#define ROBOT_ARM_CONTROL_H

#pragma region Arm Pins
#define ARM_WRIST_PIN 8
#define ARM_BASE_PIN 9
#define ARM_SHOULDER_PIN 10
#define ARM_ELBOW_PIN 11
#define ARM_GRIPPER_PIN 12
#define ARM_WRIST_FEEDBACK_PIN A0
#define ARM_BASE_FEEDBACK_PIN A1
#define ARM_SHOULDER_FEEDBACK_PIN A2
#define ARM_ELBOW_FEEDBACK_PIN A3
#define ARM_GRIPPER_FEEDBACK_PIN A4
#pragma endregion

#pragma region Arm Angles

#include <Arduino.h> // Include the Arduino library
#include <Servo.h>   // Include the Servo library

// Define the JointAngles structure
struct JointAngles
{
    float base;
    float shoulder;
    float elbow;
    float wrist;
    float gripper;

    // Constructor to initialize the angles
    JointAngles(float initShoulder = 90.0, float initElbow = 90.0, float initWrist = 90.0, float initGripper = 90.0);
};

// Define the RobotArmControl class
class RobotArmControl
{
public:
    RobotArmControl();
    static void initialize();
    static void updatePosition(const JointAngles &angles, const String &objective);
    static JointAngles solveIK(float x, float y, float z);
    static void calibrate();

    static constexpr float j1 = 5.0;
    static constexpr float j2 = 5.0;
    static constexpr int gripString = 13; //? What is this for?
    static constexpr int gripLargePackage = 14;
    static constexpr int gripSmallPackage = 15;
    static constexpr int gripBooster = 16;
    static constexpr int gripRelease = 16;

private:
    Servo wristServo;
    Servo baseServo;
    Servo shoulderServo;
    Servo elbowServo;
    Servo gripperServo;
    JointAngles dropOffAngles;
    JointAngles dropBridgeAngles;
    JointAngles initializeAngles;
    // Add any additional member variables or methods needed here.
};

#endif // ROBOT_ARM_CONTROL_H
