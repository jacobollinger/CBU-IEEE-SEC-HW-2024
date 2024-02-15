#include "RobotArmControl.h"

RobotArmControl::RobotArmControl(){

	// Predefined constants 
	const float j1 = 13.34;
    const float j2 = 10.80;
	
	// **No idea** 
    const int gripString = 13;
    const int gripLargePackage = 14;
    const int gripSmallPackage = 15;
    const int gripBooster = 16;
    const int gripRelease = 16;
	
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
	//servo baseServo; //FT6325M-360 
	// Define Pins
	
	wristServo.attach(8);
    gripperServo.attach(9);
    shoulderServo.attach(10);
	//baseServo.attach(11); servo cannot be accurately controlled by servo library
	
	// set Analog Pins
    int ARM_WRIST_FEEDBACK_PIN = analogRead(A0);    // Analog pin for calibration
    int ARM_GRIPPER_FEEDBACK_PIN = analogRead(A1);  // Analog pin for calibration
	int ARM_SHOULDER_FEEDBACK_PIN = analogRead(A2); // Analog pin for calibration {}
}
void RobotArmControl::initialize()
{	

    updatePosition(initializedAngles, "");
}

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
        }*/
        currentAngles = angles;

}

JointAngles RobotArmControl::solveIK(float x, float y, float z)
{
	/*JointAngles angles; // needs tuning for gripper coordinates
    wristAngle = -acos((sq(x) + sq(y) - sq(j1) - sq(j2)) / (2 * j1 * j2));
    shoulderAngle = atan(y / x) + atan((j2 * sin(elbow)) / (j1 + j2 * cos(elbowAngle)));
    return angles;*/
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
