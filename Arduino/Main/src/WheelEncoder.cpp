#include <Arduino.h>
#include "../include/WheelEncoder.hpp"

WheelEncoder::WheelEncoder(int encoderA, int encoderB, bool flip=false)
{
    pinMode(encoderA, INPUT);
    pinMode(encoderB, INPUT);
    encA = encoderA;
    encB = encoderB;
    pos = 0;
    prevPos = 0;
    prevTime = 0;
    actualSpeed = 0;
    flip = flip;
}
// To record number pulses
// May need to readjust due to opposite spinning motors
void WheelEncoder::update()
{
    volatile long int encB_data = digitalRead(encB);
    if (encB_data != flip)
    {
        pos++;
    }
    else
    {
        pos--;
    }
};
float WheelEncoder::speedInRPM(int pos)
{
    int t_1 = millis();
    int time_elapsed = t_1 - prevTime;
    float d_pos = pos - prevPos; // # of pulses
    // # pulses / ( pulses per revolution * elapsed time);
    actualSpeed = d_pos / (2400 * time_elapsed / 60000);
    prevTime = t_1;
    prevPos = pos;
    return actualSpeed;
}
volatile long int WheelEncoder::getPosition()
{
    return pos;
};

volatile long int WheelEncoder::getPrevPosition()
{
    return prevPos;
};
void WheelEncoder::clear()
{
    pos = 0;
}