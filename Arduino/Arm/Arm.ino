#include <RobotArmControl.h>

#include <Servo.h>
RobotArmControl Arm;

void setup(){

    Serial.begin(9600); // Initialize serial communication
    Arm.initialize(); // Initialize the robot arm
    //Arm.updatePosition("initial");
    collectLargePackages();
   

}

void loop()
{   
//     // Check for new SPI data and update robot arm position accordingly
//     // if (SPIReceiver::messageEndFlag)
//     // {
//     //     float x = SPIReceiver::getNextFloat(); // Implement this method to read floats from SPI
//     //     float y = SPIReceiver::getNextFloat();
//     //     float z = SPIReceiver::getNextFloat();
//     //     string objective = SPIReceiver::getNextString();
//     //     // Solve inverse kinematics to get joint angles
//     //     JointAngles angles = robotArm.solveIK(x, y, z);
//     //     robotArm.updatePosition(angles, objective);
//     //     SPIReceiver::clearBuffer(); // Clear the SPI buffer after processing
//     // }

//     while (!Serial.available()) {}
// String input = Serial.readString();

// // Find the first space separating x and y
// int spaceIndex1 = input.indexOf(' ');

// if (spaceIndex1 != -1) {
//     // Extract x as a substring from the start of the string to the first space
//     String xStr = input.substring(0, spaceIndex1);
//     double x = xStr.toDouble();
//     Serial.println(x); // Print x with 2 decimal places

//     // Find the second space separating y and z
//     int spaceIndex2 = input.indexOf(' ', spaceIndex1 + 1);

//     if (spaceIndex2 != -1) {
//         // Extract y as a substring between the first and second space
//         String yStr = input.substring(spaceIndex1 + 1, spaceIndex2);
//         double y = yStr.toDouble();
//         Serial.println(y); // Print y with 2 decimal places

//         // Find the third space separating z and objective
//         int spaceIndex3 = input.indexOf(' ', spaceIndex2 + 1);

//         if (spaceIndex3 != -1) {
//             // Extract z as a substring between the second and third space
//             String zStr = input.substring(spaceIndex2 + 1, spaceIndex3);
//             double z = zStr.toDouble();
//             Serial.println(z); // Print z with 2 decimal places

//             // Extract objective as a substring from the third space to the end of the string
//             String obj = input.substring(spaceIndex3 + 1);
//             Serial.println(obj);
            
// // Set the servo position to y degrees
//      Arm.solveIK(x,y,z);
//      Arm.updatePosition(obj);
//      delay(500); 
     }
    }
}
   }

void collectLargepackages(){
    // Collect Center package 
    Arm.solveIK(-3.81, 13. 1.27);
    Arm.updatePosition("largePackage");

    // Collect Right1 package 
    Arm.solveIK(2.54, 14, 2.54);
    Arm.updatePosition("largePackage");
    
    // Collect Left1 package 
    Arm.solveIK(-10, 12 ,0);
    Arm.updatePosition("largePackage");
    
    // Collect Right2 package 
    Arm.solveIK(10, 17, 0);
    Arm.updatePosition("largePackage");
    
    // Collect Left2 package 
    Arm.solveIK(-18, 13, -3);
    Arm.updatePosition("largePackage");
}
