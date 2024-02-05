#include "RobotArmControl.h" // Include the header file for robot arm control
#include <SPI.h> // Include the SPI library
#include <Arduino.h> // Include the Arduino library
#include <Servo.h> // Include the Servo library

struct JointAngles {
    float base;
    float shoulder;
    //float elbow;
    float wrist;
    float gripper;

    // Constructor to initialize the angles
    JointAngles(float base =90.0, float initShoulder = 90.0, float initWrist = 90.0, float initGripper = 90.0)
        : base(initbase), shoulder(initShoulder), wrist(initWrist), gripper(initGripper) {}
}

class RobotArmControl {
public:
    //set Servos
    Servo wristServo; //DMS-MG90-A-360
    Servo baseServo; //FT6325M-360 Servo
    Servo shoulderServo; //FT6325-360 Servo
    Servo gripperServo; //DMS-MG90-A-360 Servo
    //set Pins
    const int wristPin = 8; // Pin for wrist servo
    const int basePin = 9; // Pin for base servo
    const int shoulderPin = 10; // Pin for shoulder servo
    const int gripperPin = 11; // Pin for gripper servo
    //set Analog Pins
    const int analogPinWrist = A0; //Analog pin for calibration
    const int analogPinBase = A1; //Analog pin for calibration
    const int analogPinShoulder = A2; //Analog pin for calibration
    const int analogPinGripper = A3; //Analog pin for calibration
    //set constants that will be used
    const float j1 = 13.34; // Length of the shoulder to wrist link in cm, 5.25 in
    const float j2 = 10.80; // Length to ideal grip in cm, 4.25
    float shoulderAngle; //Angle between the base and the shoulder
    const int gripString = 13; //Gripper string *update
    const int gripLargePackage = 14; //Gripper string *update
    const int gripSmallPackage = 15; //Gripper string *update
    const int gripBooster = 16; //Gripper string *update
    const int gripRelease = 16; //Gripper string *update
    dropOffAnglesLargePkg = JointAngles(90, 90, 90, 90); // set angles for dropping off large packages *update
    dropOffAnglesSmallPkg = JointAngles(90, 90, 90, 90); // set angles for dropping off small packages * update
    dropOffAnglesBoosters = JointAngles(90, 90, 90, 90); // set angles for dropping off boosters *update
    dropBridgeAngles = JointAngles(90, 90, 90, 90); // set angles for droppping off bridge *update
    initializedAngles = JointAngles(90, 90, 90, 90); //set angles for statup *update
    currentAngles = JointAngles(90, 90, 90,90); // placeholder to know where arm is set
    RobotArmControl() {}

    void initialize() {
        wristServo.attach(wristPin);
        baseServo.attach(basePin);
        shoulderServo.attach(shoulderPin);
        //elbowServo.attach(elbowPin);
        gripperServo.attach(gripperPin);
        updatePosition(initializedAngles);
    }

    // Other class methods
    void updatePosition(const JointAngles& angles, const String& objective) {
        currentAngles = angles
        shoulderServo.write(angles.shoulder);
        //elbowServo.write(angles.elbow);
        wristServo.write(angles.wrist);
        calibrate();
        if (objective == "smallPackage") {
            gripperServo.write(gripSmallPackage);
            updatePosition(dropOffAnglesSmallPkg, "release");
        } else if (objective == "largePackage") {
            gripperServo.write(gripLargePackage);
            updatePosition(dropOffAnglesLargePkg, "release");
        } else if (objective == "string") {
            gripperServo.write(gripString);
            updatePosition(dropBridgeAngles, "release")
        } else if (objective == "booster") {
            gripperServo.write(gripBooster);
            updatePosition(dropBridgeAngles, "release");
        } else if (objective == "release") {
            gripperServo.write(gripRelease);
        }
        currentAngles = angles
    }
    JointAngles solveIK(float x, float y, float z) {
        JointAngles angles; //needs tuning for gripper coordinates
        wristAngle = -acos((sq(x) + sq(y) -sq(j1) - sq(j2)) / (2 * j1 * j2));
        shoulderAngle = atan(y / x) + atan((j2 * sin(elbow)) / (j1 + j2 * cos(elbowAngle))); 
        return angles;
    }
    void calibrate() {
        int shoulderFeedback = analogRead(analogPinShoulder);
        //int elbowFeedback = analogRead(analogPinElbow);
        int wristFeedback = analogRead(analogPinWrist);
        int gripperFeedback = analogRead(analogPinGripper);
        // Convert feedback to angles - this requires mapping sensor values to degrees
        // Placeholder for conversion logic: map(value, fromLow, fromHigh, toLow, toHigh)
        shoulderServo.write(map(shoulderFeedback, 0, 1023, 0, 180));
        //elbowServo.write(map(elbowFeedback, 0, 1023, 0, 180));
        wristServo.write(map(wristFeedback, 0, 1023, 0, 180));
        gripperServo.write(map(gripperFeedback, 0, 1023, 0, 180));
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
