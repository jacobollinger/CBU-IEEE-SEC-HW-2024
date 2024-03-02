#include <Arduino.h>
#include "../include/WheelEncoder.h"

WheelEncoder::WheelEncoder(int encoderA, int encoderB, bool flip=false)
{
    pinMode(encoderA, INPUT);
    pinMode(encoderB, INPUT);
    encA = encoderA;
    encB = encoderB;
    pos = 0;
    old_pos = 0;
    old_time = 0;
    actual_speed = 0;
    flip = flip;
}
// To record number pulses
// May need to readjust due to opposite spinning motors
void WheelEncoder::read()
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
}

float WheelEncoder::speedInRPM()
{
    int t_1 = millis();
    int time_elapsed = t_1 - old_time;
    float d_pos = pos - old_pos; // # of pulses
    // # pulses / ( pulses per revolution * elapsed time);
    actual_speed = d_pos / (2400 * time_elapsed / 60000);
    old_time = t_1;
    old_pos = pos;
    return actual_speed;
}

volatile long int WheelEncoder::getPosition()
{
    return pos;
}

volatile long int WheelEncoder::getPrevPosition()
{
    return old_pos;
}

void WheelEncoder::clear()
{
    pos = 0;
}