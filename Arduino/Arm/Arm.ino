#include <RobotArmControl.h>
#include <Servo.h>
Servo testServo;
RobotArmControl Arm;

void setup(){

    Serial.begin(115200); // Initialize serial communication
    //Arm.initialize(); // Initialize the robot arm
   

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

   /* // input format: "x y z"
    String input = Serial.readString();
    float x = input.substring(0, input.indexOf(' ')).toFloat();
    input = input.substring(input.indexOf(' ') + 1);
    float y = input.substring(0, input.indexOf(' ')).toFloat();
    input = input.substring(input.indexOf(' ') + 1);
    float z = input.toFloat();*/

    // input format: "x y z"
 
    String input = Serial.readString();
    int spaceIndex = input.indexOf(' ');
    int spaceIndex2 = input.lastIndexOf(' '); 
    
    if (spaceIndex != -1 && spaceIndex2 != -1) {
    // Get the substring before the space as x
    double x = input.substring(0, spaceIndex).toDouble();
    Serial.println(x); 
    
    // Get the substring after the space as y
    double y = input.substring(spaceIndex + 1).toDouble();
    Serial.println(y); 
// Read Anloag output at this location   
// get the substring after the space as z 
  double z = input.substring(spaceIndex2 + 1).toDouble(); 
  Serial.println(z); 
  
// Set the servo position to y degrees
     Arm.solveIK(x,y,z);

   }
}
