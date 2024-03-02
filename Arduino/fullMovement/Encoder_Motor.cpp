#include <Arduino.h>
#include "Encoder_Motor.h"

Encoder:: Encoder(int encA, int encB ){
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);
  pin1 = encA;
  pin2 = encB;
  pos = 0;
  old_pos = 0;
  old_time =0;
  actual_speed = 0;   
}
// To record number pulses
// May need to readjust due to opposite spinning motors
void Encoder::readEncoder(){
  volatile long int encB_data = digitalRead(pin2);
  if (encB_data == HIGH){
    pos++;
  }
  else {
    pos--;
  }
}; 
float Encoder::speedInRPM(int pos){
  int t_1 = millis();
  int time_elapsed = t_1 - old_time;
  float d_pos = pos - old_pos; // # of pulses
  // # pulses / ( pulses per revolution * elapsed time); 
  actual_speed = d_pos / (2400 * time_elapsed / 60000); 
  old_time = t_1; 
  old_pos = pos;
  return actual_speed;
   
} 
volatile long int Encoder:: getPosition(){
      return pos;
    }; 

volatile long int Encoder:: getOldPosition(){
      return old_pos;
    }; 
void Encoder:: clrEncoder(){
  pos = 0;
}