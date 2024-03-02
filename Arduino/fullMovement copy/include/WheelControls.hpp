#include <DualG2HighPowerMotorShield.h>
#include <util/atomic.h>

#include "Defines.hpp"
#include "WheelEncoder.h"

#define INCH_PER_REV 32.0 / 7100.0
#define PULSE_PER_DEG 17.5

class WheelControls
{
public:
    static void init();
    static int *getEncoderValues();
    static void clearEncoders();
    static void moveForward(float distance, int targetSpeed);
    static void moveBackward(float distance, int targetSpeed);
    static void rotateClockwise(int degrees, int targetSpeed);
    static void rotateCounterClockwise(int degrees, int targetSpeed);

private:
    static DualG2HighPowerMotorShield24v14 motorDriver;
    static WheelEncoder leftEncoder, rightEncoder;

    static void move(float distance, int direction, int targetSpeed);
    static void rotate(int degrees, int targetSpeed);
};