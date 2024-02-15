#include <RobotArmControl.h>
#include <Servo.h>
Servo testServo;

void setup()

{   RobotArmControl test;
    Serial.begin(115200); // Initialize serial communication
   // test.initialize(); // Initialize the robot arm
   
    // Attach the servo to pin x
    testServo.attach(10);
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
    int x = input.substring(0, spaceIndex).toInt();
    Serial.println(x); 
    
    // Get the substring after the space as y
    int y = input.substring(spaceIndex + 1).toInt();
    Serial.println(y); 
// Read Anloag output at this location   
// get the substring after the space as z 
//    int z = input.substring(spaceIndex2 + 1).toInt(); 
    
    
    // Set the servo position to y degrees
    testServo.write(y);

//    if( z != 0); {
//    int output = analogRead(z); 
//    Serial.println(output); 
//    }
  }
}
