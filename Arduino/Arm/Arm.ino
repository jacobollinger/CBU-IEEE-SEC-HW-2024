#include "./include/RobotArmControl.h"

void setup()
{
    Serial.begin(115200); // Initialize serial communication
    RobotArmControl::initialize(); // Initialize the robot arm
}

void loop()
{
    // Check for new SPI data and update robot arm position accordingly
    // if (SPIReceiver::messageEndFlag)
    // {
    //     float x = SPIReceiver::getNextFloat(); // Implement this method to read floats from SPI
    //     float y = SPIReceiver::getNextFloat();
    //     float z = SPIReceiver::getNextFloat();
    //     string objective = SPIReceiver::getNextString();
    //     // Solve inverse kinematics to get joint angles
    //     JointAngles angles = robotArm.solveIK(x, y, z);
    //     robotArm.updatePosition(angles, objective);
    //     SPIReceiver::clearBuffer(); // Clear the SPI buffer after processing
    // }

    while (!Serial.available()) {}

    // input format: "x y z"
    String input = Serial.readString();
    float x = input.substring(0, input.indexOf(' ')).toFloat();
    input = input.substring(input.indexOf(' ') + 1);
    float y = input.substring(0, input.indexOf(' ')).toFloat();
    input = input.substring(input.indexOf(' ') + 1);
    float z = input.toFloat();
}
