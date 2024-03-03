#ifndef ROBOT_ARM_CONTROL_H
#define ROBOT_ARM_CONTROL_H

#include <Arduino.h>
#include <Servo.h>
#include <Math.h>
//#include <ServoEasing.h> //could not use the ServoEasing in this header possibly due to it being an hpp



class RobotArmControl{
public:
    RobotArmControl();
    void initialize();
	int calcVectorAngle(double x, double y); // Calculate angle of vector
	int angleToMicroseconds360(double angle);
	void moveToAngle(int baseAngle, float shoulderAngle, float wristAngle, double gripperAngle);
	void calibrate();
    //void updatePosition(double x, double y, double z, double g);
	void solveIK(double x_coordinate, double y_coordinate, double z_coordinate);
	void updatePosition(String objective);
        
private:
	
    // Servo baseServo;
	// Servo shoulderServo;
	// Servo wristServo;
	Servo gripperServo;

//could not use the ServoEasing in this header possibly due to it being an hpp
    // ServoEasing shoulderServo;
	// ServoEasing wristServo;
	
// Predefined Angles *Determine these
	double gripLargePackage = 46;
	double gripSmallPackage = 35; 
	double gripBooster = 18; 
	double gripRelease = 88; 
	
	// Store specific angles in arrays
    double dropBridgeAngles[4] = {90, 90, 90, 90};      // set angles for droppping off bridge *update
    double initializedAngles[4] = {888, 170, 11.76, 88};     // set angles for statup *update
	double currentAngles[4] = {90, 90, 90, 90}; // 
	double dropOffAnglesLargePkg[4] = {1666, 140, 11.76, 46}; // set angles for dropping off large packages *update
    double dropOffAnglesSmallPkg[4] = {2194, 131, 11.76, 36}; // set angles for dropping off small packages * updateSerial.print("dropOffAnglesSmallPkg.base: ");
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
