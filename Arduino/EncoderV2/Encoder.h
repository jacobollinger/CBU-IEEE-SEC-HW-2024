#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

class Encoder{
  public: 
    Encoder(int encA, int encB);
    void readEncoder(); 
    float speedInRPM(int pos); 
    int getPosition();
    int old_time; 
    float actual_speed; 
  private:
  int pin1, pin2;
  volatile int pos, old_pos; 
}; 
#endif
