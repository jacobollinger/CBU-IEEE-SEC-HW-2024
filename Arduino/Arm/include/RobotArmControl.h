#ifndef ROBOT_ARM_CONTROL_H
#define ROBOT_ARM_CONTROL_H

#include <Arduino.h>
#include <Servo.h>
#include <math.h>

#include "Defines.hpp"
// #include "FunctionMap.hpp"

class RobotArmControl
{
public:
    struct Angles
    {
        int base;
        float shoulder;
        float wrist;
        float gripper;
    };

    RobotArmControl();
    void initialize();
    int angleToMicroseconds360(double angle);
    int calcVectorAngle(double x, double y); // Calculate angle of vector
    void moveToAngle(Angles angles);
    void moveToAngleLessEase(int x, float y, float z, float g);
    void moveToAngleLessEase(Angles angles);
    void moveToAngle(int x, float y, float z, float g);
    // void updatePosition(double x, double y, double z, double g);
    void updatePosition(String objective);
    void solveIK(double x, double y, double z);
    void sweep();
    void calibrate();

    // static int getFunctionCount();
    // static FunctionMap::Function *getFunctions();

private:
    Servo gripperServo; // DMA-MG90-A 270

    // Predefined Angles *Determine these
    const double gripLargePackage = 38;
    const double gripSmallPackage = 35;
    const double gripBooster = 18;
    const double gripRelease = 60;
    const double gripSweep = 5; 

    // Store specific angles in arrays
    // double dropBridgeAngles[4] = {90, 90, 90, 90};			  // set angles for droppping off bridge *update
    // double initializedAngles[4] = {888, 170, 30, 75};		  // set angles for statup *update
    // double currentAngles[4] = {90, 90, 90, 90};				  //
    // double dropOffAnglesLargePkg[4] = {1583, 167.22, 14, 46}; // set angles for dropping off large packages *update
    // double dropOffAnglesSmallPkg[4] = {2194, 131, 11.76, 35}; // set angles for dropping off small packages * updateSerial.print("dropOffAnglesSmallPkg.base: ");
    // double dropOffAnglesBoosters[4] = {90, 90, 90, 18};		  // set angles for dropping off boosters *update) {}

    Angles dropBridgeAngles = {1888, 152, 34, 0};
    Angles dropSmallContainer = {2094, 138, 7, gripSmallPackage};
    Angles dropLargeContainer = {1888, 150 , 7, gripLargePackage};
    Angles initializedAngles = {888, 170, 25, gripRelease};
    Angles uprightAngles = {888, 180, 85, gripRelease};
    Angles dropOffAnglesLargePkg = {1583, 175, 5, 46};
    Angles dropOffAnglesSmallPkg = {2222, 147, 35, 35};
    Angles pickupSweep = {2177, 145, 5, gripRelease};
    Angles disposeSweepAngles = {2222, 115.2, 87.6, gripSweep};

    const float L0 = 12.5;   // length from ground to first joint
    const float L1 = 18.25625; // length from 2nd joint to 3rd joint (shoulder to wrist)
    const float L2 = 12.7;     // length from 3rd joint to gripper tip
    const float pi = 3.141592653589793;
};

#endif // ROBOT_ARM_CONTROL_H
