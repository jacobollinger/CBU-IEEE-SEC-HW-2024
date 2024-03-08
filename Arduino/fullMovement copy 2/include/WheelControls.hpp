#include <DualG2HighPowerMotorShield.h>

#include "Defines.hpp"
#include "Ultrasonics.hpp"
#include "WheelEncoder.hpp"

#define LINE_FOLLOW_LEFT A5
#define LINE_FOLLOW_RIGHT A6
#define LINE_FOLLOW_BACKRIGHT A7
#define LINE_FOLLOW_BACKLEFT A8

#define LINE_FOLLOW_LEFT_THRESHOLD 470
#define LINE_FOLLOW_RIGHT_THRESHOLD 470
#define LINE_FOLLOW_BACKLEFT_THRESHOLD 100
#define LINE_FOLLOW_BACKRIGHT_THRESHOLD 100

#define PULSE_PER_DEG 17.5

class WheelControls
{
public:
    WheelControls();
    void moveForwardEncoders(float targetDistance, int speed);
    void moveBackwardEncoders(float targetDistance, int speed);
    void rotateClockwise(float degree, int target_speed);
    void rotateCounterClockwise(float degree, int target_speed);

    void moveUltrasonicsForward(float targetDistance, int speed);
    void moveUltrasonicsBackward(float targetDistance, int speed);

    // void lineFollow(float targetDistance, int targetSpeed, int right, int left);
    void lineFollowConstant(float targetDistance, int targetSpeed, int right, int left);
    void moveBackwardUntilSensor(int threshold, int speed);

    void stopIfFault();

    void clearEncoders();
    int *getEncoderPositions();
    void updateLeftEncoder();
    void updateRightEncoder();

private:
    DualG2HighPowerMotorShield24v14 motorDriver;
    Ultrasonics ultrasonics;
    WheelEncoder leftEncoder, rightEncoder;
};