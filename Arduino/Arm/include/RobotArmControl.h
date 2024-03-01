#ifndef ROBOT_ARM_CONTROL_H
#define ROBOT_ARM_CONTROL_H

#include <Arduino.h>
#include <Servo.h>
#include <Math.h>

class RobotArmControl{
public:
    RobotArmControl();
	void initialize();
	int angleToMicroseconds360(double angle);
	int calcVectorAngle(double x, double y); // Calculate angle of vector
	void moveToAngle(double x, double y, double z, double g);
	//void updatePosition(double x, double y, double z, double g);
	void updatePosition(String objective);
	void solveIK(double x, double y, double z);
	void calibrate();    
private:
	
   	Servo baseServo;
    	Servo shoulderServo;
	Servo wristServo;
	Servo gripperServo;
	
// Predefined Angles *Determine these
	double gripLargePackage = 46;
	double gripSmallPackage = 35; 
	double gripBooster = 18; 
	double gripRelease = 88; 
	
	// Store specific angles in arrays
        double dropBridgeAngles[4] = {90, 90, 90, 90};      // set angles for droppping off bridge *update
        double initializedAngles[4] = {888, 177.56, 0, 88};     // set angles for statup *update
	double currentAngles[4] = {90, 90, 90, 90}; // 
	double dropOffAnglesLargePkg[4] = {1666, 140, 11.76, 46}; // set angles for dropping off large packages *update
        double dropOffAnglesSmallPkg[4] = {2194, 131, 11.76, 35}; // set angles for dropping off small packages * updateSerial.print("dropOffAnglesSmallPkg.base: ");
	double dropOffAnglesBoosters[4] = {90, 90, 90, 18}; // set angles for dropping off boosters *update) {}
	
	const float L0 = 10.125; // length from ground to second joint (shoulder)
        const float L1 = 18.25625; // length from 2nd joint to 3rd joint (shoulder to wrist)
	const float L2 = 12.7; // length from 3rd joint to gripper tip
	const float pi = 3.141592653589793;
	
	//int g;
	
	// Analog inputs
        int ARM_GRIPPER_FEEDBACK_PIN;
	int ARM_WRIST_FEEDBACK_PIN; 
	int ARM_SHOULDER_FEEDBACK_PIN;

};

#endif // ROBOT_ARM_CONTROL_H
