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
    static constexpr int wristPin = 8;
    static constexpr int basePin = 9;
    static constexpr int shoulderPin = 10;
    static constexpr int elbowPin = 11;
    static constexpr int gripperPin = 12;
    static constexpr int analogPinWrist = A0;
    static constexpr int analogPinBase = A1;
    static constexpr int analogPinShoulder = A2;
    static constexpr int analogPinElbow = A3;
    static constexpr int analogPinGripper = A4;
    static constexpr float j1 = 5.0;
    static constexpr float j2 = 5.0;
    static constexpr int gripString = 13;
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
