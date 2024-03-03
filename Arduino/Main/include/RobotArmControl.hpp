#ifndef ROBOT_ARM_CONTROL_H
#define ROBOT_ARM_CONTROL_H

#include <Arduino.h>
#include <Servo.h>
#include <math.h>

#include "Defines.hpp"
#include "FunctionMap.hpp"

class RobotArmControl
{
public:
    struct Angles
    {
        double base;
        double shoulder;
        double wrist;
        double gripper;
    };

    RobotArmControl();
    void initialize();
    int angleToMicroseconds360(double angle);
    int calcVectorAngle(double x, double y); // Calculate angle of vector
    void moveToAngle(Angles angles);
    void moveToAngle(double x, double y, double z, double g);
    // void updatePosition(double x, double y, double z, double g);
    void updatePosition(String objective);
    void solveIK(double x, double y, double z);
    void calibrate();

    static int getFunctionCount();
    static FunctionMap::Function *getFunctions();

private:
    Servo wristServo;    // DMA-MG90-A 270
    Servo gripperServo;  // DMA-MG90-A 270
    Servo shoulderServo; // FS5106B-FB 180 W/FEEDBACK
    Servo baseServo;     // FT6325M-360

    // Predefined Angles *Determine these
    const double gripLargePackage = 46;
    const double gripSmallPackage = 35;
    const double gripBooster = 18;
    const double gripRelease = 88;

    // Store specific angles in arrays
    // double dropBridgeAngles[4] = {90, 90, 90, 90};			  // set angles for droppping off bridge *update
    // double initializedAngles[4] = {888, 177.56, 0, 88};		  // set angles for statup *update
    // double currentAngles[4] = {90, 90, 90, 90};				  //
    // double dropOffAnglesLargePkg[4] = {1666, 140, 11.76, 46}; // set angles for dropping off large packages *update
    // double dropOffAnglesSmallPkg[4] = {2194, 131, 11.76, 35}; // set angles for dropping off small packages * updateSerial.print("dropOffAnglesSmallPkg.base: ");
    // double dropOffAnglesBoosters[4] = {90, 90, 90, 18};		  // set angles for dropping off boosters *update) {}
    Angles dropBridgeAngles = {90, 90, 90, 90};
    Angles initializedAngles = {888, 177.56, 0, 88};
    Angles currentAngles = {90, 90, 90, 90};
    Angles dropOffAnglesLargePkg = {1666, 140, 11.76, 46};
    Angles dropOffAnglesSmallPkg = {2194, 131, 11.76, 35};
    Angles dropOffAnglesBoosters = {90, 90, 90, 18};

    const float L0 = 10.125;   // length from ground to second joint (shoulder)
    const float L1 = 18.25625; // length from 2nd joint to 3rd joint (shoulder to wrist)
    const float L2 = 12.7;     // length from 3rd joint to gripper tip
    const float pi = 3.141592653589793;
};

#endif // ROBOT_ARM_CONTROL_H
