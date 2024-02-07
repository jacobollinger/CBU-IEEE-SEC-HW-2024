#include <Arduino.h>
#include <Encoder.h>
#include <PID.h>
#include <util/atomic.h>
#include "CytronMotorDriver.h"

// These are digital inputs for motor encoders
#define ENCA_M1 2
#define ENCB_M1 13
#define ENCA_M2 3
#define ENCB_M2 12

// intiallize the two encoders and PID controllers store in array 
Encoder encoder1(ENCA_M1, ENCB_M1);
Encoder encoder2(ENCA_M2, ENCB_M2);
//Encoder enc_array [2] = {encoder1, encoder2}; 
PID PIDcontroller1;
PID PIDcontroller2;

// Intialize variables
int prev_time = 0; 
float actual_speed1 = 0;
float actual_speed2 = 0;



// Configure the motor driver.
CytronMD motor1(PWM_DIR, 5, 4);  // PWM 1 = Pin 5, DIR 1 = Pin 4.
CytronMD motor2(PWM_DIR, 9, 10); // PWM 2 = Pin 9, DIR 2 = Pin 10.

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

// Setup PID Controller parameters
PIDcontroller1.setParameters(0.1, 0.01, 0.01);  // Adjust the gains as needed
PIDcontroller2.setParameters(0.1, 0.01, 0.01);  // Adjust the gains as needed

// Attach interrupts == Once a high ENCA is read pulse counting begins
attachInterrupt(digitalPinToInterrupt(ENCA_M1), readEncoder1, RISING);
attachInterrupt(digitalPinToInterrupt(ENCA_M2), readEncoder2, RISING);


}

void loop() {
// put your main code here, to run repeatedly:
// intialize variables
float current_time = millis();
float dt = current_time - prev_time;

// Define target speed(should be part of the movement/sensor code)
// Reverse sign PWM to get them to move in same direction (make sure correct pos are read)
// may need to change signs of motor 
int target_speed1 = 255; 
int target_speed2 = - target_speed1; 

volatile long int pos[2];
ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
  pos[0] = encoder1.getPosition();
  pos[1] = encoder2.getPosition();
}  
Serial.print("Motor 1 Position: ");
Serial.println(pos[0]);

Serial.print("Motor 2 Position: ");
Serial.println(pos[1]);
  //pos[1] = encoder2.getPosition();
// Get actual speed (need to fix)
//actual_speed1 = encoder1.speedInRPM(pos[0]);
//actual_speed2 = encoder2.speedInRPM(pos[1]);


// moves 32in increasing by 64 til 256 
int i = 64;

while (pos[0] < 6500 && pos[1] < 6500){
  
     
    motor1.setSpeed(i);   // Motor 1 runs forward at 50% speed.
    motor2.setSpeed(-i);  // Motor 2 runs backward at 50% speed.
    i < 256 ? i += 16: i = 256;
    
    delay(10);
    pos[0] = -encoder1.getPosition();
    pos[1] = encoder2.getPosition();
    
  
    Serial.print("Motor 1 Position: ");
    Serial.println(pos[0]);

    Serial.print("Motor 2 Position: ");
    Serial.println(pos[1]);

   
}

motor1.setSpeed(0);     // Motor 1 stops.
motor2.setSpeed(0);     // Motor 2 stops.
delay(3000);
//pos[0] = 0;
Serial.print("Motor 1 Position: ");
Serial.println(pos[0]);


 //turns the bot 180 deg
while (pos[0] < 4100 && pos[1] > 8900){
  
    int i = 128;
    motor1.setSpeed(i);   
    motor2.setSpeed(i);  
    delay(10);
    pos[0] = -encoder1.getPosition();
    pos[1] = encoder2.getPosition();
    Serial.print("Motor 1 Position: ");
    Serial.println(pos[0]);

    Serial.print("Motor 2 Position: ");
    Serial.println(pos[1]);
}
  motor1.setSpeed(0);     // Motor 1 stops.
  motor2.setSpeed(0);     // Motor 2 stops.
  delay(3000);

  //goes in reverse for 52in increasing by 8 til -256
  int j = -32;
  while (pos[1] > -3100 && pos[0] < 1700){
 
    motor1.setSpeed(j-6.5);   
    motor2.setSpeed(-j);  
    j > -256 ? j += -2: j = -256;
    delay(50);
   
    pos[0] = -encoder1.getPosition();
    pos[1] = encoder2.getPosition();
    Serial.print("Motor 1 Position: ");
    Serial.println(pos[0]);

    Serial.print("Motor 2 Position: ");
    Serial.println(pos[1]);
}
  motor1.setSpeed(0);     // Motor 1 stops.
  motor2.setSpeed(0);     // Motor 2 stops.

  delay(3000);
//
//// turn bot -90 deg
//
//while (pos[1] > -4500){
//  
//    int i = 64;
//    motor1.setSpeed(i-6.5);  
//    motor2.setSpeed(i);  
//    delay(10);
//    pos[0] = -encoder1.getPosition();
//    pos[1] = encoder2.getPosition();
//    Serial.print("Motor 1 Position: ");
//    Serial.println(pos[0]);
//
//    Serial.print("Motor 2 Position: ");
//    Serial.println(pos[1]);
//}
//  motor1.setSpeed(0);     // Motor 1 stops.
//  motor2.setSpeed(0);     // Motor 2 stops.
//  delay(2000);
//
//  
////bot moves 28in 
//while (pos[1] > -6900){
//  
//    int i = -128;
//    motor1.setSpeed(i-6.5);   
//    motor2.setSpeed(-i);  
//    delay(10);
//    pos[0] = -encoder1.getPosition();
//    pos[1] = encoder2.getPosition();
//    Serial.print("Motor 1 Position: ");
//    Serial.println(pos[0]);
//
//    Serial.print("Motor 2 Position: ");
//    Serial.println(pos[1]);
//}
//  motor1.setSpeed(0);     // Motor 1 stops.
//  motor2.setSpeed(0);     // Motor 2 stops.
//  delay(3000);
//
//  // turn bot 90 deg
//
//while (pos[1] > -4200){
//  
//    int i = 64;
//    motor1.setSpeed(i-6.5);  
//    motor2.setSpeed(-i);  
//    delay(10);
//    pos[0] = -encoder1.getPosition();
//    pos[1] = encoder2.getPosition();
//    Serial.print("Motor 1 Position: ");
//    Serial.println(pos[0]);
//
//    Serial.print("Motor 2 Position: ");
//    Serial.println(pos[1]);
//}
//  motor1.setSpeed(0);     // Motor 1 stops.
//  motor2.setSpeed(0);     // Motor 2 stops.
//  delay(20000);

  
// Call PID function 
/*
PIDcontroller1.calculateNewSignal(target_speed1, actual_speed1);
PIDcontroller2.calculateNewSignal(target_speed2, actual_speed2); 
// Set Motor send the corrected signal to the motor; need motor driver 
*/
Serial.print("Motor 1 Position: ");
Serial.println(pos[0]);

Serial.print("Motor 2 Position: ");
Serial.println(pos[1]);

}

// Interrupt service routines for encoders
// Need to make sure encoder reads correct dir travel 
void readEncoder1() {
  encoder1.readEncoder();
}

void readEncoder2() {
  encoder2.readEncoder();
}
