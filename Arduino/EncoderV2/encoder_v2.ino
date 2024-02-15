#include <Arduino.h>
#include <Encoder.h>
#include <PID.h>
#include <util/atomic.h>


// intiallize the two encoders and PID controllers store in array 
Encoder encoder1(2, 5);
Encoder encoder2(3, 4);
int ENCA_M1 = 2; 
int ENCB_M1 = 5; 
int ENCA_M2 = 3; 
int ENCB_M2 = 4; 
PID PIDcontroller1;
PID PIDcontroller2;
// Intialize variables
int prev_time = 0; 
float actual_speed1 = 0;
float actual_speed2 = 0;
//int pos[2];
volatile long int left_pos = 0;
volatile long int right_pos = 0;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

// These are digital inputs
pinMode(ENCA_M1, INPUT);
pinMode(ENCB_M1, INPUT);
pinMode(ENCA_M2, INPUT);
pinMode(ENCB_M2, INPUT);

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
/*float current_time = millis();
float dt = current_time - prev_time;

// Define target speed(should be part of the movement/sensor code)
// Reverse sign PWM to get them to move in same direction (make sure correct pos are read)
// may need to change signs of motor 
int target_speed1 = 400; 
int target_speed2 = -400; */

left_pos = encoder1.getPosition();
right_pos = encoder2.getPosition();

// Get actual speed (need to fix)
actual_speed1 = encoder1.speedInRPM(left_pos);
actual_speed2 = encoder2.speedInRPM(right_pos);
// Call PID function 
/*
PIDcontroller1.calculateNewSignal(target_speed1, actual_speed1);
PIDcontroller2.calculateNewSignal(target_speed2, actual_speed2); 
// Set Motor send the corrected signal to the motor; need motor driver */

Serial.print("Motor 1 Position: ");
Serial.println(left_pos);
Serial.println();
Serial.print("Motor 2 Position: ");
Serial.println(right_pos);
Serial.println();//
}

// Interrupt service routines for encoders
// Need to make sure encoder reads correct dir travel 
void readEncoder1() {
  encoder1.readEncoder();
}

void readEncoder2() {
  encoder2.readEncoder();
}
