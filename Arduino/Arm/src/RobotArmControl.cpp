#include "RobotArmControl.h"
#include "Servo.h"
#include "Math.h"

RobotArmControl::RobotArmControl(){
	// Intialize servos
	Servo wristServo; // DMA-MG90-A 270
    Servo gripperServo; // DMA-MG90-A 270
    Servo shoulderServo; // FS5106B-FB 180 W/FEEDBACK
	Servo baseServo; //FT6325M-360 
}
void RobotArmControl::initialize(){	// Define Pins
	updatePosition("initial");
	gripperServo.attach(8,440, 1408);
    wristServo.attach(9,440, 2400);
    shoulderServo.attach(10, 440, 2400);
	baseServo.attach(11, 440, 2238);
	
	// set Analog Pins
    int ARM_WRIST_FEEDBACK_PIN = analogRead(A0);    // Analog pin for calibration
    int ARM_GRIPPER_FEEDBACK_PIN = analogRead(A1);  // Analog pin for calibration
	int ARM_SHOULDER_FEEDBACK_PIN = analogRead(A2); // Analog pin for calibration
}
// Servo.h write degrees is arbitary to the 360; warning: writeMicroseconds to DMA-MG90-A 270 = continuous motor = irreversible
// Takes kinematics angles and matches it respective to these servos 
int RobotArmControl::angleToMicroseconds360(double angle){
	double microAngle = 500.0+(((2500.0-500)/360) * (angle)) ; 
	return (int) microAngle; 
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
}

void RobotArmControl::moveToAngle( double b, double a1, double a2, double g){
	// if coming down move base, shoulder, wrist 
	// if moving up: wrist, shoulder, base
	shoulderServo.write(a1);
	Serial.println(a1);
	delay(1000);
	wristServo.write(a2); // Warning: .writeMicroseconds converts the motor into continuous
	Serial.println(a2);
	delay(1000);
	gripperServo.write(g); 
	Serial.println(g);
	delay(1000);
	baseServo.writeMicroseconds(b); 
	Serial.println(b);
	delay(1000);
	
}

int RobotArmControl::calcVectorAngle( double x_coordinate, double y_coordinate){
	int degrees = (int) ( atan2(y_coordinate, x_coordinate) * (180/pi));
	degrees = ( degrees + 360 ) % 360; 
	return degrees;
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
	
	double theta = acos((sq(L1) + (sq(R)) - sq(L2))/(2*R*L1)) * (180/pi); // law of cosine to find angle between length to End Effector and ARM link 1
	double beta =  acos((sq(L2) + (sq(L1)) - sq(R))/(2*L1*L2)); 
	
	if ( z_coordinate > L0 ){
		// Prelimnary Angles
		double phi = calcVectorAngle(distanceToEndEffector, zOffset); // Angle between height and distancetoEndEffector
		
		double shoulderAngle = phi + theta + 90; 
		double wristAngle = beta * 180/pi - 65; // 65 to adjust for servo offset and be in line with the grippers
		moveToAngle(baseAngle,shoulderAngle,wristAngle,gripAngle); 
	} else {
		// Prelimnary Angles
		double phi = atan(zOffset / distanceToEndEffector) * (180/pi); // Angle between height and distancetoEndEffector
		
		// Angles for servo motors 
		double shoulderAngle = theta - phi; //angle for first part of the arm 
		double wristAngle = beta * 180/pi;
		moveToAngle(baseAngle,shoulderAngle,wristAngle,gripAngle); 
	}
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
