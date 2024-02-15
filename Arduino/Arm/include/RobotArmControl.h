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
    void updatePosition(const JointAngles &angles, const String &objective);
    JointAngles solveIK(float x, float y, float z);
    void calibrate();    



private:
	
    Servo baseServo; // this servo cannot be accurately moved by the servo library 
    Servo shoulderServo;
	Servo wristServo;
	Servo gripperServo;
    JointAngles dropOffAnglesLargePkg;
	JointAngles dropOffAnglesSmallPkg;
	JointAngles dropOffAnglesBoosters;
    JointAngles dropBridgeAngles;
    JointAngles initializedAngles;
    JointAngles currentAngles;
	
	const float j1; 
	const float j2; 
	const int gripString;
	const int gripLargePackage;
	const int gripSmallPackage;
	const int gripBooster;
	const int gripRelease;
	
	// Analog inputs
    int ARM_GRIPPER_FEEDBACK_PIN;
	int ARM_WRIST_FEEDBACK_PIN; 
	int ARM_SHOULDER_FEEDBACK_PIN;

};

#endif // ROBOT_ARM_CONTROL_H
