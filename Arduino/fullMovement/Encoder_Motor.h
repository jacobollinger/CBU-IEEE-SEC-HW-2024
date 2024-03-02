#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

class Encoder{
  public: 
    Encoder(int encA, int encB);
    void readEncoder(); 
    float speedInRPM(int pos); 
    volatile long int getPosition();
    volatile long int getOldPosition();
    void Encoder:: clrEncoder();
    int old_time; 
    float actual_speed; 
    int pin1, pin2;
    
  private:
  volatile long int pos, old_pos; 
}; 
#endif
