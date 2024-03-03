#ifndef WHEELENCODER_H
#define WHEELENCODER_H

#include <util/atomic.h>

class WheelEncoder
{
public:
    WheelEncoder(int encoderA, int encoderB, bool flip);
    void update();
    void clear();
    float speedInRPM(int pos);
    volatile long int getPosition();
    volatile long int getPrevPosition();

private:
    int encA, encB;
    int prevTime;
    float actualSpeed;
    volatile long int pos, prevPos;
    bool flip;
};
#endif
