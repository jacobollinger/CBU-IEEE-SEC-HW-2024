#include "../include/RobotArmControl.hpp"

#include <ServoEasing.hpp>

#include "../include/Logger.hpp"

#define EASE_SPEED 80
#define SHOULDER_MID_POSITION 80 
#define WRIST_MID_POSITION 60
#define BASE_X_AXIS_LOCATION 330
#define BASE_NEGATIVE_X_AXIS_LOCATION 1388
#define BASE_Y_AXIS_LOCATION 888
#define BRIDGE_CONTACT_POINT 70
#define SWEEP_EASE_SPEED 250

ServoEasing wristServo;
ServoEasing shoulderServo;
ServoEasing baseServo;
RobotArmControl::RobotArmControl(){
    // Intialize servos
    // RobotArmControl::initialize();
	Servo gripperServo;
}

void RobotArmControl::initialize(){

	// Following is not included in the MAIN
	
	gripperServo.attach(ARM_GRIPPER_PIN);
	wristServo.attach(ARM_WRIST_PIN, initializedAngles.wrist);
	shoulderServo.attach(ARM_SHOULDER_PIN, initializedAngles.shoulder);
	baseServo.attach(ARM_BASE_PIN,initializedAngles.base);
    delay(500);

    // Define Pins
    gripperServo.attach(ARM_GRIPPER_PIN);
    wristServo.attach(ARM_WRIST_PIN, ARM_WRIST_MIN, ARM_WRIST_MAX);
    shoulderServo.attach(ARM_SHOULDER_PIN, ARM_SHOULDER_MIN, ARM_SHOULDER_MAX);
    baseServo.attach(ARM_BASE_PIN, ARM_BASE_MIN, ARM_BASE_MAX);

    // Set easing types
    wristServo.setEasingType(EASE_SINE_IN);
    shoulderServo.setEasingType(EASE_SINE_IN);
    baseServo.setEasingType(EASE_SINE_IN);
}

// Servo.h write degrees is arbitary to the 360; warning: writeMicroseconds to DMA-MG90-A 270 = continuous motor = irreversible
// Takes kinematics angles and matches it respective to these servos
int RobotArmControl::angleToMicroseconds360(double angle){
    double microAngle = 500.0 + (((2500.0 - 500) / 360) * (angle));
    return (int)microAngle;
}

void RobotArmControl::updatePosition(String objective){
    objective.trim();
    // calibrate();
    if (objective == "smallPackage"){
        delay(200);
		gripperServo.write(gripSmallPackage);
        //delay(500);
        moveToAngle(dropOffAnglesSmallPkg.base, uprightAngles.shoulder, dropOffAnglesSmallPkg.wrist, dropOffAnglesSmallPkg.gripper);
        moveToAngle(dropOffAnglesSmallPkg.base, dropOffAnglesSmallPkg.shoulder, dropOffAnglesSmallPkg.wrist, dropOffAnglesSmallPkg.gripper);
        delay(200);
        updatePosition("release");
        shoulderServo.easeTo(uprightAngles.shoulder, EASE_SPEED);
		///delay(500);
		//updatePosition("initial");
    }
    else if (objective == "largePackage"){  
		gripperServo.write(gripLargePackage);
		delay(500);
		shoulderServo.easeTo(SHOULDER_MID_POSITION, EASE_SPEED);
        //delay(500);
		//wristServo.easeTo(WRIST_MID_POSITION, EASE_SPEED);
        //delay(500);
        moveToAngle(dropOffAnglesLargePkg.base, dropOffAnglesLargePkg.shoulder, dropOffAnglesLargePkg.wrist, dropOffAnglesLargePkg.gripper);
        updatePosition("release");
		//delay(500);
        // wristServo.easeTo(initializedAngles.wrist);
		//updatePosition("initial");>>>>> cc3622ee42282b8d04944cf6670ff6a414f08ebc
    }
    else if (objective == "initial") {	
		moveToAngle(initializedAngles.base, initializedAngles.shoulder, initializedAngles.wrist, initializedAngles.gripper);
        //delay(500);
    }
    else if (objective == "negativeInitial") {
        moveToAngle(negativeInitializedAngles.base, negativeInitializedAngles.shoulder, negativeInitializedAngles.wrist, negativeInitializedAngles.gripper);
        //delay(500);
    }
    else if (objective == "centerGravityForward"){
        moveToAngle(centerGravityForward);
    }
    else if (objective == "dropSmall"){
        delay(500);
        moveToAngle(dropSmallContainer.base, uprightAngles.shoulder, uprightAngles.wrist, dropSmallContainer.gripper);
        moveToAngle(dropSmallContainer.base, dropSmallContainer.shoulder, dropSmallContainer.wrist, dropSmallContainer.gripper);        //gripperServo.write(dropSmallContainer.gripper, EASE_SPEED);
        baseServo.easeTo(2200,EASE_SPEED);
        }
    else if(objective == "dropLarge"){
        moveToAngle(dropLargeContainer.base, uprightAngles.shoulder, uprightAngles.wrist, dropLargeContainer.gripper);
        moveToAngle(dropLargeContainer);
        //wristServo.easeTo(dropLargeContainer.wrist, EASE_SPEED);
        baseServo.easeTo(BASE_NEGATIVE_X_AXIS_LOCATION, EASE_SPEED); 
    }
    else if(objective == "dropBridge"){
        moveToAngle(dropBridgeAngles);
        wristServo.easeTo(BRIDGE_CONTACT_POINT, EASE_SPEED);
    }
    else if (objective == "release"){  
		gripperServo.write(gripRelease);
        Serial.println(gripRelease);
        //delay(500);
	}
    else if( objective == "sweep"){
        moveToAngle(pickupSweep.base, uprightAngles.shoulder, uprightAngles.wrist,gripRelease);
        moveToAngle(pickupSweep); //determine position to pickup "sweep" metal
        delay(200);
        gripperServo.write(0);
        delay(100);
        
        // //Move to Upright Position to avoid collisions
        shoulderServo.easeTo(uprightAngles.shoulder, EASE_SPEED);
        wristServo.easeTo(uprightAngles.wrist, EASE_SPEED);
        delay(200);

        // // // Move to First Sweep location; 
        baseServo.easeTo(1250, EASE_SPEED);
        wristServo.easeTo(25, EASE_SPEED);
        shoulderServo.easeTo(90, EASE_SPEED);
        delay(200);
        wristServo.easeTo(55, EASE_SPEED);
        

        // First Sweep 
        sweep();
    }
    else{
        Logger::log("Invalid objective: " + objective);
    }
}

void RobotArmControl::moveToAngle(int baseAngle, float shoulderAngle, float wristAngle, float gripperAngle){
    moveToAngle(Angles{baseAngle, shoulderAngle, wristAngle, gripperAngle});
}

void RobotArmControl::moveToAngle(Angles angles){
	if(90 > angles.shoulder)    { // Moving down move base, wrist, shoulder 
		baseServo.easeTo(angles.base, EASE_SPEED);
		// baseServo.writeMicroseconds(angleToMicroseconds360(angles.base));
		//delay(500);
		shoulderServo.easeTo(angles.shoulder, EASE_SPEED);
		//delay(500);
		wristServo.easeTo(angles.wrist, EASE_SPEED); // Warning: .writeMicroseconds converts the motor into continuous
		//delay(500);
		gripperServo.write(angles.gripper);
		//delay(500);
	 }
	 else if (90 < angles.shoulder){ // moving up: wrist, shoulder, base
		wristServo.easeTo(angles.wrist, EASE_SPEED); // Warning: .writeMicroseconds converts the motor into continuous
		//delay(500);
		shoulderServo.easeTo(angles.shoulder, EASE_SPEED);
		//delay(500);
		gripperServo.write(angles.gripper);
		//delay(500);
		baseServo.easeTo(angles.base, EASE_SPEED);
		// baseServo.writeMicroseconds(angleToMicroseconds360(angles.base));
		//delay(500);
	}
	else{
		;
	}
}

int RobotArmControl::calcVectorAngle(double x_coordinate, double y_coordinate){
	int degrees = (int)(atan2(y_coordinate, x_coordinate) * (180 / pi));
    degrees = (degrees + 360) % 360;
    return degrees;
}

void RobotArmControl::solveIK(double x_coordinate, double y_coordinate, double z_coordinate){  
	double zOffset = z_coordinate - L0;
    float gripAngle = gripRelease;

    // xy plane as the surface
    int baseAngle = calcVectorAngle(x_coordinate, y_coordinate) - 20; // -20 to adjsut for servo offset
    baseAngle = angleToMicroseconds360(baseAngle);
    Serial.println(baseAngle);
    // "Creating triangle"
    double distanceToEndEffector = sqrt(sq(x_coordinate) + sq(y_coordinate)); // polar coordinates: "r"
    double R = sqrt(sq(zOffset) + sq(distanceToEndEffector));                 // "r" with height

    float theta = acos((sq(L1) + (sq(R)) - sq(L2)) / (2 * R * L1)) * (180 / pi); // law of cosine to find angle between length to End Effector and ARM link 1
    float beta = acos((sq(L2) + (sq(L1)) - sq(R)) / (2 * L1 * L2));

    if (z_coordinate > L0){ 	// Prelimnary Angles
        float phi = calcVectorAngle(distanceToEndEffector, zOffset); // Angle between height and distancetoEndEffector

        float shoulderAngle = phi + theta + 90;
        Serial.println(shoulderAngle);
        float wristAngle = beta * 180 / pi - 65; // 65 to adjust for servo offset and be in line with the grippers
        Serial.println(wristAngle);
        moveToAngle(baseAngle, shoulderAngle, wristAngle, gripAngle);
    }
    else{	// Prelimnary Angles
        float phi = atan(zOffset / distanceToEndEffector) * (180 / pi); // Angle between height and distancetoEndEffector

        // Angles for servo motors
        float shoulderAngle = 70 + (phi + theta); // angle for first part of the arm
        Serial.println(shoulderAngle);
        float wristAngle = beta * 180 / pi - 20; // 35 to adjust for servo offset 
        Serial.println(wristAngle);
        moveToAngle(baseAngle, shoulderAngle, wristAngle, gripAngle);
    }
}
void RobotArmControl::sweep(){
    delay(100);
    baseServo.easeTo(BASE_X_AXIS_LOCATION + 100, SWEEP_EASE_SPEED);
    delay(100);
    baseServo.easeTo(BASE_NEGATIVE_X_AXIS_LOCATION - 100, SWEEP_EASE_SPEED);
    delay(100);
    baseServo.easeTo(BASE_X_AXIS_LOCATION + 100, SWEEP_EASE_SPEED);
    delay(100);
    baseServo.easeTo(BASE_NEGATIVE_X_AXIS_LOCATION - 100, SWEEP_EASE_SPEED);
}


// void RobotArmControl::calibrate(){	
// 	int shoulderFeedback = analogRead(ARM_SHOULDER_FEEDBACK_PIN);
//     // int elbowFeedback = analogRead(ARM_ELBOW_FEEDBACK_PIN);
//     int wristFeedback = analogRead(ARM_WRIST_FEEDBACK_PIN);
//     int gripperFeedback = analogRead(ARM_GRIPPER_FEEDBACK_PIN);
//     // Convert feedback to angles - this requires mapping sensor values to degrees

//     /* Do not understand this portion
//     // Placeholder for conversion logic: map(value, fromLow, fromHigh, toLow, toHigh)
//     shoulderServo.write(map(shoulderFeedback, 0, 1023, 0, 180));
//     // elbowServo.write(map(elbowFeedback, 0, 1023, 0, 180));
//      wristServo.write(map(wristFeedback, 0, 1023, 0, 180));
//     gripperServo.write(map(gripperFeedback, 0, 1023, 0, 180));*/
// }

// int RobotArmControl::getFunctionCount()
// {
//     return 7;
// }

// FunctionMap::Function *RobotArmControl::getFunctions()
// {
//     FunctionMap::Function *functions = new FunctionMap::Function[getFunctionCount()];
//     // functions[0].name = "initialize";
//     // functions[0].function = &RobotArmControl::initialize;
//     // functions[1].name = "moveToAngle";
//     // functions[1].function = &RobotArmControl::moveToAngle;
//     // functions[2].name = "updatePosition";
//     // functions[2].function = &RobotArmControl::updatePosition;
//     // functions[3].name = "solveIK";
//     // functions[3].function = &RobotArmControl::solveIK;
//     // functions[4].name = "calibrate";
//     // functions[4].function = &RobotArmControl::calibrate;
//     // functions[5].name = "angleToMicroseconds360";
//     // functions[5].function = &RobotArmControl::angleToMicroseconds360;
//     // functions[6].name = "calcVectorAngle";
//     // functions[6].function = &RobotArmControl::calcVectorAngle;
//     return functions;
// }
