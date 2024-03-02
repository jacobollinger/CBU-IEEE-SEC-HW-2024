#include "RobotArmControl.h"
#include "Servo.h"
#include "Math.h"
#include "ServoEasing.hpp"

ServoEasing wristServo; // DMA-MG90-A 270
ServoEasing shoulderServo; // FS5106B-FB 180 W/FEEDBACK
ServoEasing baseServo; //FT6325M-360 

RobotArmControl::RobotArmControl(){
	// Intialize servos
	Servo gripperServo; // DMA-MG90-A 270
	// Servo wristServo; // DMA-MG90-A 270
    // Servo shoulderServo; // FS5106B-FB 180 W/FEEDBACK
	//Servo baseServo; //FT6325M-360 
	
}
void RobotArmControl::initialize(){	
	// Store intial position before attach
	//updatePosition("initial");
	gripperServo.attach(8);
    wristServo.attach(9,11);
    shoulderServo.attach(10, 170);
	baseServo.attach(11, 888);
	

	// define easing type
	//gripperServo.setEasingType(EASE_SINE_IN_OUT);
	wristServo.setEasingType(EASE_SINE_IN_OUT);
	shoulderServo.setEasingType(EASE_SINE_IN_OUT);
	baseServo.setEasingType(EASE_SINE_IN_OUT);
		
	// define constraint angles  
	gripperServo.attach(9, 440, 1408);
    wristServo.attach(10, 440, 2400);
    shoulderServo.attach(11, 440, 2400);
	baseServo.attach(12, 440, 2238);
	
	// set Analog Pins
    int ARM_WRIST_FEEDBACK_PIN = analogRead(A0);    // Analog pin for calibration
    int ARM_GRIPPER_FEEDBACK_PIN = analogRead(A1);  // Analog pin for calibration
	int ARM_SHOULDER_FEEDBACK_PIN = analogRead(A2); // Analog pin for calibration
}

int RobotArmControl::calcVectorAngle( double x_coordinate, double y_coordinate){
	int degrees = (int) ( atan2(y_coordinate, x_coordinate) * (180/pi));
	degrees = ( degrees + 360 ) % 360; 
	return degrees;
}

int RobotArmControl::angleToMicroseconds360(double angle){
// Servo.h write degrees is arbitary to the 360; warning: writeMicroseconds to DMA-MG90-A 270 = continuous motor = irreversible
// Takes kinematics angles and matches it respective to these servos 

	double microAngle = 500.0+(((2500.0-500)/360) * (angle)) ; 
	return (int) microAngle; 
}

void RobotArmControl::moveToAngle( int baseAngle, float shoulderAngle, float wristAngle, double gripperAngle){
	// Conditions to consider: 
		// if coming down move base, shoulder, wrist 
		// if moving up: wrist, shoulder, base

	//wristServo.write(wristAngle); // Warning: .writeMicroseconds converts the motor into continuous
	wristServo.easeTo(wristAngle, 60);
	Serial.println(wristAngle);
	delay(1000);

	//shoulderServo.write(shoulderAngle);
	shoulderServo.easeTo(shoulderAngle, 60);
	Serial.println(shoulderAngle);
	delay(1000);
	
	gripperServo.write(gripperAngle); 
	//gripperServo.easeTo(gripperAngle)
	Serial.println(gripperAngle);
	delay(1000);
	
	//baseServo.writeMicroseconds(baseAngle);
	baseServo.easeTo(baseAngle, 60); 
	Serial.println(baseAngle);
	delay(1000);	
}


void RobotArmControl::calibrate(){	int shoulderFeedback = analogRead(ARM_SHOULDER_FEEDBACK_PIN);
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


void RobotArmControl::solveIK(double x_coordinate, double y_coordinate, double z_coordinate){
	
	double zOffset = z_coordinate - L0;
	double gripAngle = 88;
	
	// xy plane as the surface
	int baseAngle = calcVectorAngle(x_coordinate, y_coordinate) - 20; // -20 to adjsut for servo offset
	baseAngle = angleToMicroseconds360(baseAngle);
	
	// "Creating triangle"
	double distanceToEndEffector = sqrt(sq(x_coordinate) + sq(y_coordinate)); // polar coordinates: "r"
	double R = sqrt(sq(zOffset) + sq(distanceToEndEffector)); // "r" with height 
	
	float theta = acos((sq(L1) + (sq(R)) - sq(L2))/(2*R*L1)) * (180/pi); // law of cosine to find angle between length to End Effector and ARM link 1
	float beta =  acos((sq(L2) + (sq(L1)) - sq(R))/(2*L1*L2)); 
	
	if ( z_coordinate > L0 ){
		// Prelimnary Angles
		float phi = (float) calcVectorAngle(distanceToEndEffector, zOffset); // Angle between height and distancetoEndEffector
		
		float shoulderAngle = phi + theta + 90; 
		float wristAngle = beta * 180/pi - 65; // 65 to adjust for servo offset and be in line with the grippers
		moveToAngle(baseAngle,shoulderAngle,wristAngle,gripAngle); 
	} else {
		// Prelimnary Angles
		float phi = (float) atan(zOffset / distanceToEndEffector) * (180/pi); // Angle between height and distancetoEndEffector
		
		// Angles for servo motors 
		float shoulderAngle = theta - phi; //angle for first arm link 
		float wristAngle = beta * 180/pi;
		moveToAngle(baseAngle,shoulderAngle,wristAngle,gripAngle); 
	}
}

void RobotArmControl::updatePosition(String objective){	
	objective.trim();
    //calibrate();
	if (objective == "smallPackage"){
            gripperServo.write(gripSmallPackage);
			Serial.println("n");
			//Serial.println(gripSmallPackage);
			delay(500);
			moveToAngle(dropOffAnglesSmallPkg[0], dropOffAnglesSmallPkg[1], dropOffAnglesSmallPkg[2], dropOffAnglesSmallPkg[3]);
            delay(500);
			updatePosition("release");
        }
    else if (objective == "largePackage"){
            gripperServo.write(gripLargePackage);
			delay(500); 
			moveToAngle(dropOffAnglesLargePkg[0], dropOffAnglesLargePkg[1], dropOffAnglesLargePkg[2], dropOffAnglesLargePkg[3]);
            updatePosition("release");
        }
        else if (objective == "initial"){
		moveToAngle(initializedAngles[0], initializedAngles[1], initializedAngles[2], initializedAngles[3]);
		delay(500);
        }
	/*else if (objective == "booster"){
            gripperServo.write(gripBooster);
			delay(500);
            updatePosition(dropBridgeAngles, "release");
        }*/
    else if (objective == "release"){
            gripperServo.write(gripRelease);
			Serial.println(gripRelease);
			delay(500);
        } 
	else{
		;
	}
}

