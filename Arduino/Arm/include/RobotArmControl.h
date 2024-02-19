#ifndef ROBOT_ARM_CONTROL_H
#define ROBOT_ARM_CONTROL_H

#include <Arduino.h>
#include <Servo.h>

struct JointAngles
{
    float base;
    float shoulder;
    float wrist;
    float gripper;

    JointAngles(float initBase = 90.0, float initShoulder = 90.0, float initWrist = 90.0, float initGripper = 90.0)
        : base(initBase), shoulder(initShoulder), wrist(initWrist), gripper(initGripper) {}
};

class RobotArmControl
{
public:
    RobotArmControl();
    void initialize();
    void moveToAngle(double x, double y, double z, double g);
    void updatePosition(double x, double y, double z, double g);
    void solveIK(float x, float y, float z);
    void calibrate();    



private:
	
Servo baseServo;
Servo shoulderServo;
Servo wristServo;
Servo gripperServo;

JointAngles dropOffAnglesLargePkg;
JointAngles dropOffAnglesSmallPkg;
JointAngles dropOffAnglesBoosters;
JointAngles dropBridgeAngles;
JointAngles initializedAngles;
JointAngles currentAngles;
	
const float L0 = 19.2875; // length from ground to second joint (elbow)
const float L1 = 12.85875; // length from 2nd joint to 3rd joint (elbow to wrist)
const float L2 = 10.16; // length from 3rd joint to gripper tip
const float pi = 3.141592653589793;
	
	//const int gripString;
	//const int gripLargePackage;
	//const int gripSmallPackage;
	//const int gripBooster;
	//const int gripRelease;
	//const float pi; 
	//int g;
	
// Analog inputs
int ARM_GRIPPER_FEEDBACK_PIN;
int ARM_WRIST_FEEDBACK_PIN; 
int ARM_SHOULDER_FEEDBACK_PIN;

};

#endif // ROBOT_ARM_CONTROL_H
