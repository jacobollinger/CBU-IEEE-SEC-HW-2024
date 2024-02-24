#include "RobotArmControl.h"
#include "Servo.h"
#include "Math.h"

RobotArmControl::RobotArmControl(){

	
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
	
	
	
}
void RobotArmControl::initialize()
	
	
{	// Define Pins
	gripperServo.attach(8,440, 1408);
    wristServo.attach(9,440, 1968);
    shoulderServo.attach(10, 945, 2400);
	baseServo.attach(11, 440, 2238);
	
	// set Analog Pins
    int ARM_WRIST_FEEDBACK_PIN = analogRead(A0);    // Analog pin for calibration
    int ARM_GRIPPER_FEEDBACK_PIN = analogRead(A1);  // Analog pin for calibration
	int ARM_SHOULDER_FEEDBACK_PIN = analogRead(A2); // Analog pin for calibration

    //updatePosition(initializedAngles, "");
}
// Servo.h write degrees is arbitary to the 360; warning: writeMicroseconds to DMA-MG90-A 270 = continuous motor = irreversible
// Takes kinematics angles and matches it respective to these servos 
int RobotArmControl::angleToMicroseconds360(double angle){
	double microAngle = 500.0+(((2500.0-500)/360) * (angle) ; 
	return (int) microAngle; 
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
	baseServo.writeMicroseconds(b); 
	//Serial.println(b);
	shoulderServo.write(a1);
	Serial.println(a1);
	wristServo.write(a2); // Warning: .writeMicroseconds converts the motor into continuous
	Serial.println(a2);
	gripperServo.write(g); 
	Serial.println(g);
}

int RobotArmControl::calcVectorAngle( double x_coordinate, double y_coordinate){
	int degrees = (int) ( atan2(y_coordinate, x_coordinate) * (180/pi));
	degrees = ( degrees + 360 ) % 360; 
	return degrees;
}

void RobotArmControl::solveIK(double x_coordinate, double y_coordinate, double z_coordinate)
{
	double gripAngle = 88; // for testing purposes only 
	double zOffset = z_coordinate - L0;
	

	
	// xy plane as the surface
	int baseAngle = calcVectorAngle(x_coordinate, y_coordinate);
	Serial.println(baseAngle);
	baseAngle = angleToMicroseconds360(baseAngle);
	Serial.println(baseAngle);
	
	// "Creating triangle"
	double distanceToEndEffector = sqrt(sq(x_coordinate) + sq(y_coordinate)); // polar coordinates: "r"
	double R = sqrt(sq(zOffset) + sq(distanceToEndEffector)); // "r" with height 
	
	if ( z_coordinate > L0 ){
	// Prelimnary Angles
	double phi = calcVectorAngle(distanceToEndEffector, zOffset); // Angle between height and distancetoEndEffector
	double theta = acos((sq(L1) + (sq(R)) - sq(L2))/(2*R*L1)) * (180/pi); // law of cosine to find angle between length to End Effector and ARM link 1
	double beta =  acos((sq(L2) + (sq(L1)) - sq(R))/(2*L1*L2)); 
	
	// Angles for servo motors 
	double shoulderAngle = phi + theta; //angle for first part of the arm 
	//double wristAngle = (pi - beta)* (180/pi); //angle for second part of the arm
	double wristAngle = beta * 180/pi;
	
	moveToAngle(baseAngle,shoulderAngle,wristAngle,gripAngle); 
	
	}
	// condition where different triangle is considered
	/*else if { //when wrist is flexed out
	
	double phi = atan(zOffset / distanceToEndEffector) * (180/pi); // Angle between height and distancetoEndEffector
	double theta = acos((sq(L1) + (sq(R)) - sq(L2))/(2*R*L1)) * (180/pi); // law of cosine to find angle between length to End Effector and ARM link 1
	double beta =  acos((sq(L2) + (sq(L1)) - sq(R))/(2*L1*L2)); 
	
	// Angles for servo motors 
	double shoulderAngle = phi + theta; //angle for first part of the arm 

	double wristAngle = (pi/2 - beta)* (180/pi); //angle for second part of the arm

		
		
	}*/
	else {
	// Prelimnary Angles
	double phi = atan(zOffset / distanceToEndEffector) * (180/pi); // Angle between height and distancetoEndEffector
	double theta = acos((sq(L1) + (sq(R)) - sq(L2))/(2*R*L1)) * (180/pi); // law of cosine to find angle between length to End Effector and ARM link 1
	double beta =  acos((sq(L2) + (sq(L1)) - sq(R))/(2*L1*L2)); 
	
	// Angles for servo motors 
	double shoulderAngle = theta - phi; //angle for first part of the arm 
	double wristAngle = beta * 180/pi;
		moveToAngle(baseAngle,shoulderAngle,wristAngle,gripAngle); 
	} 
	
	
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
