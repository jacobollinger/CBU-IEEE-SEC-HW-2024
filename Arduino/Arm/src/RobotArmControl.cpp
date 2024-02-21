#include "RobotArmControl.h"
#include "Math.h"

RobotArmControl::RobotArmControl(){

	// Predefined constants 
	//const float L0 = 19.2875; // length from ground to second joint (elbow)
    //const float L1 = 12.85875; // length from 2nd joint to 3rd joint (elbow to wrist)
	//const float L2 = 10.16; // length from 3rd joint to gripper tip
	//const float pi = 3.141592653589793;
	
	// **No idea** 
    //const int gripString = 13;
    //const int gripLargePackage = 14;
    //const int gripSmallPackage = 15;
    //const int gripBooster = 16;
    //const int gripRelease = 16;
	//const int g = 88;
	
	// Predefined Angles
    JointAngles dropBridgeAngles = JointAngles(90, 90, 90, 90);      // set angles for droppping off bridge *update
    JointAngles initializedAngles = JointAngles(90, 90, 90, 90);     // set angles for statup *update
    JointAngles currentAngles = JointAngles(90, 90, 90, 90); 
	JointAngles dropOffAnglesLargePkg = JointAngles(90, 90, 90, 90); // set angles for dropping off large packages *update
    JointAngles dropOffAnglesSmallPkg = JointAngles(90, 90, 90, 90); // set angles for dropping off small packages * update
    JointAngles dropOffAnglesBoosters = JointAngles(90, 90, 90, 90); // set angles for dropping off boosters *update) {}
	
	// Intialize servos

	Servo wristServo; // DMA-MG90-A 270
    Servo gripperServo; // DMA-MG90-A 270
    Servo shoulderServo; // FS5106B-FB 180 W/FEEDBACK
	Servo baseServo; //FT6325M-360 
	// Define Pins
	
	gripperServo.attach(8,440, 1408);
    wristServo.attach(9,440, 1968);
    shoulderServo.attach(10, 945, 2400);
    baseServo.attach(11, 440, 2238);
	
	// set Analog Pins
    int ARM_WRIST_FEEDBACK_PIN = analogRead(A0);    // Analog pin for calibration
    int ARM_GRIPPER_FEEDBACK_PIN = analogRead(A1);  // Analog pin for calibration
    int ARM_SHOULDER_FEEDBACK_PIN = analogRead(A2); // Analog pin for calibration {}
}
void RobotArmControl::initialize()
{	

    //updatePosition(initializedAngles, "");
}
void RobotArmControl::updatePosition(double x, double y, double z, double g){
	
	return;
	
	
}
/*
void RobotArmControl::updatePosition(const JointAngles &angles, const String &objective)
{
    currentAngles = angles;
    shoulderServo.write(angles.shoulder);
    wristServo.write(angles.wrist);
	currentAngles = angles
        shoulderServo.write(angles.shoulder);
        // elbowServo.write(angles.elbow);
        wristServo.write(angles.wrist);
        calibrate();
		/*
        if (objective == "smallPackage")
        {
            gripperServo.write(gripSmallPackage);
            updatePosition(dropOffAnglesSmallPkg, "release");
        }
        else if (objective == "largePackage")
        {
            gripperServo.write(gripLargePackage);
            updatePosition(dropOffAnglesLargePkg, "release");
        }
        else if (objective == "string")
        {
            gripperServo.write(gripString);
            updatePosition(dropBridgeAngles, "release")
        }
        else if (objective == "booster")
        {
            gripperServo.write(gripBooster);
            updatePosition(dropBridgeAngles, "release");
        }
        else if (objective == "release")
        {
            gripperServo.write(gripRelease);
        } 
        currentAngles = angles;

} */

void RobotArmControl::moveToAngle( double b, double a1, double a2, double g){
	baseServo.write(b); 
	Serial.println(b);
	shoulderServo.write(a1);
	Serial.println(a1);
	wristServo.write(a2);
	Serial.println(a2);
	gripperServo.write(g); 
	Serial.println(g);

	
}

void RobotArmControl::solveIK(float x, float y, float z)
{
	double g = 88;
	double b = atan(y/x) * (180 / pi ); // base angle 
	double l = sqrt(x*x + y*y); // polar coordinates: "r"
	double h = sqrt(z*z + l*l); // "r" with height 
	
	// 
	double C = acos( - (h*h - (L1*L1 + L2*L2))/(2*L1*L2)) * (180/pi);
	
	// theta and phi
	double theta = asin( (sin(C)/ h) * L2);
	double phi = atan(z/l) * (180/pi);
	double a1 = phi + theta; //angle for first part of the arm 
	double a2 = phi - theta; //angle for second part of the arm 
	moveToAngle(b,a1,a2,g); 
}

void RobotArmControl::calibrate()
{	int shoulderFeedback = analogRead(ARM_SHOULDER_FEEDBACK_PIN);
	// int elbowFeedback = analogRead(ARM_ELBOW_FEEDBACK_PIN);
        int wristFeedback = analogRead(ARM_WRIST_FEEDBACK_PIN);
	int gripperFeedback = analogRead(ARM_GRIPPER_FEEDBACK_PIN);
	// Convert feedback to angles - this requires mapping sensor values to degrees
	
	/* Do not understand this portion 
	// Placeholder for conversion logic: map(value, fromLow, fromHigh, toLow, toHigh)
       shoulderServo.write(map(shoulderFeedback, 0, 1023, 0, 180));
	// elbowServo.write(map(elbowFeedback, 0, 1023, 0, 180));
       wristServo.write(map(wristFeedback, 0, 1023, 0, 180));
       gripperServo.write(map(gripperFeedback, 0, 1023, 0, 180));*/
	
}
