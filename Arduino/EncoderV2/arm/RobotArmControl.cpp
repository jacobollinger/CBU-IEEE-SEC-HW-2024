#include "RobotArmControl.h" // Include the header file for robot arm control
#include <SPI.h> // Include the SPI library
#include <Arduino.h> // Include the Arduino library
#include <Servo.h> // Include the Servo library

struct JointAngles {
    float base;
    float shoulder;
    float elbow;
    float wrist;
    float gripper;

    // Constructor to initialize the angles
    JointAngles(float initShoulder = 90.0, float initElbow = 90.0, float initWrist = 90.0, float initGripper = 90.0)
        : shoulder(initShoulder), elbow(initElbow), wrist(initWrist), gripper(initGripper) {}
}

class RobotArmControl {
public:
    Servo wristServo;
    Servo baseServo;
    Servo shoulderServo;
    Servo elbowServo;
    Servo grippedServo; 
    const int wristPin = 8;
    const int basePin = 9;
    const int shoulderPin = 10;
    const int elbowPin = 11;
    const int gripperPin = 12; 
    const float j1 = 5; // Length of the first link update
    const float j2 = 5; // Length of the second link update
    float wristAngle = 180; // Desired orientation in degrees for wrist/ Will be constant
    //Analog pins go here
    float shoulderAngle; //Angle between the base and the shoulder
    float elbowAngle; //Angle between the shoulder and the elbow
    const int gripString = 13; //Gripper string update
    const int gripLargePackage = 14; //Gripper string update
    const int gripSmallPackage = 15; //Gripper string update
    const int gripBooster = 16; //Gripper string update
    const int gripRelease = 16; //Gripper string update
    dropOffAngles = JointAngles(90, 90, 90); // Initialize angles to 90 degrees
    dropBridgeAngles = JointAngles(90, 90, 90); // Initialize angles to 90 degrees
    initializeAngles = JointAngles(90, 90, 90); // Initialize angles to 90 degrees
    RobotArmControl() {}

    void initialize() {
        wristServo.attach(wristPin);
        baseServo.attach(basePin);
        shoulderServo.attach(shoulderPin);
        elbowServo.attach(elbowPin);
        j3Servo.attach(gripperPin);
        updatePosition(initializeAngles);
        currentAngles = initializeAngles;
    }

    // Other class methods
    void updatePosition(const JointAngles& angles, const String& objective) {
        shoulderServo.write(angles.shoulder);
        elbowServo.write(angles.elbow);
        wristServo.write(angles.wrist);
        calibrate();
        if (objective == "smallPackage") {
            gripperServo.write(gripSmallPackage);
            updatePosition(dropOffAngles, "release");
        } else if (objective == "largePackage") {
            gripperServo.write(gripLargePackage);
            updatePosition(dropOffAngles, "release");
        } else if (objective == "string") {
            gripperServo.write(gripString);
            updatePosition(dropBridgeAngles, "release")
        } else if (objective == "booster") {
            gripperServo.write(gripBooster);
            updatePosition(dropBridgeAngles, "release");
        } else if (objective == "release") {
            gripperServo.write(gripRelease);
        }
    }
    JointAngles solveIK(float x, float y, float z) {
        JointAngles angles;
        elbowAngle = -acos((sq(x) + sq(y) -sq(j1) - sq(j2)) / (2 * j1 * j2));
        shoulderAngle = atan(y / x) + atan((j2 * sin(elbow)) / (j1 + j2 * cos(elbowAngle))); 
        return angles;
    }
    void calibrate() {
    // Steps to calibrate check each servo position need analog ouputs
    }
}


void setup() {
    SPI.begin(); // Initialize SPI
    robotArm.initialize(); // Initialize robot arm components
}

void loop() {
    // Check for new SPI data and update robot arm position accordingly
    if (SPIReceiver::messageEndFlag) {
        float x = SPIReceiver::getNextFloat(); // Implement this method to read floats from SPI
        float y = SPIReceiver::getNextFloat();
        float z = SPIReceiver::getNextFloat();
        string objective = SPIReceiver::getNextString();
        // Solve inverse kinematics to get joint angles
        JointAngles angles = robotArm.solveIK(x, y, z);
        robotArm.updatePosition(angles, objective);
        SPIReceiver::clearBuffer(); // Clear the SPI buffer after processing
    }
}
