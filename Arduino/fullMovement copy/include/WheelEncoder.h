#ifndef Encoder_h
#define Encoder_h

class WheelEncoder
{
public:
    WheelEncoder(int encoderA, int encoderB, bool flip);
    void read();
    void clear();
    float speedInRPM();
    volatile long int getPosition();
    volatile long int getPrevPosition();

private:
    int encA, encB;
    int prevTime;
    volatile long int pos, prevPos;
    float actualSpeed;
    bool flip;
};
#endif
