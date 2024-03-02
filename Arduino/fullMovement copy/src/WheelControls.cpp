#include "../include/WheelControls.hpp"

void WheelControls::init()
{
    motorDriver = DualG2HighPowerMotorShield24v14(WHEELS_M1_SLP, WHEELS_M1_DIR, WHEELS_M1_PWM, WHEELS_M1_FLT, WHEELS_M1_CS, WHEELS_M2_SLP, WHEELS_M2_DIR, WHEELS_M2_PWM, WHEELS_M2_FLT, WHEELS_M2_CS);
    motorDriver.init();
    motorDriver.calibrateCurrentOffsets();
    motorDriver.enableDrivers();

    leftEncoder = WheelEncoder(WHEELS_M1_ENCA, WHEELS_M1_ENCB);
    rightEncoder = WheelEncoder(WHEELS_M2_ENCA, WHEELS_M2_ENCB);
    leftEncoder.clear();
    rightEncoder.clear();
}

int *WheelControls::getEncoderValues()
{
    int *values = new int[2];
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        values[0] = leftEncoder.getPosition();
        values[1] = rightEncoder.getPosition();
    }
    return values;
}

void WheelControls::clearEncoders()
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        leftEncoder.clear();
        rightEncoder.clear();
    }
}

void WheelControls::moveForward(float distance, int targetSpeed)
{
    clearEncoders();
    float targetRotations = distance / INCH_PER_REV;
    int *currentPositions = getEncoderValues();
    int speed = WHEEL_MIN_SPEED;
    targetSpeed = min(targetSpeed, WHEEL_MAX_SPEED);

    while (currentPositions[0] < targetRotations && currentPositions[1] < targetRotations)
    {
        motorDriver.setSpeeds(speed, speed);
        currentPositions = getEncoderValues();
        
        speed = min(speed + 25, targetSpeed);
    }
    motorDriver.setSpeeds(0, 0);
}

void WheelControls::moveBackward(float distance, int targetSpeed)
{
    clearEncoders()
    float targetRotations = distance / INCH_PER_REV;
    int *currentPositions = getEncoderValues();
    int speed = WHEEL_MIN_SPEED;
    targetSpeed = min(targetSpeed, WHEEL_MAX_SPEED);

    while (currentPositions[0] > -targetRotations && currentPositions[1] > -targetRotations)
    {
        motorDriver.setSpeeds(-speed, -speed);
        currentPositions = getEncoderValues();
        
        speed = min(speed + 25, targetSpeed);
    }
    motorDriver.setSpeeds(0, 0);
}

void WheelControls::move(float distance, int direction, int targetSpeed)
{
    // float targetRotations = distance / INCH_PER_REV;
    // int *currentPositions = getEncoderValues();
    // int speed = WHEEL_MIN_SPEED;
    // targetSpeed = min(targetSpeed, WHEEL_MAX_SPEED);

    // while (currentPositions[0] < targetRotations && currentPositions[1] < targetRotations)
    // {
    //     motorDriver.setSpeeds(speed * direction, speed * direction);
    //     currentPositions = getEncoderValues();
        
    //     speed = min(speed + 25, targetSpeed);
    // }
}

void WheelControls::rotateClockwise(int degrees, int targetSpeed)
{
    clearEncoders();
    float targetRotations = degrees * PULSE_PER_DEG;
    int *currentPositions = getEncoderValues();
    int speed = WHEEL_MIN_SPEED;
    targetSpeed = min(targetSpeed, WHEEL_MAX_SPEED);

    while(currentPositions[0] < targetRotations && currentPositions[1] > -targetRotations)
    {
        motorDriver.setSpeeds(speed, -speed);
        currentPositions = getEncoderValues();

        speed = min(speed + 50, targetSpeed);
    }
    motorDriver.setSpeeds(0, 0);
}

void WheelControls::rotateCounterClockwise(int degrees, int targetSpeed)
{
    clearEncoders();
    float targetRotations = degrees * PULSE_PER_DEG;
    int *currentPositions = getEncoderValues();
    int speed = WHEEL_MIN_SPEED;
    targetSpeed = min(targetSpeed, WHEEL_MAX_SPEED);

    while(currentPositions[0] > -targetRotations && currentPositions[1] < targetRotations)
    {
        motorDriver.setSpeeds(-speed, speed);
        currentPositions = getEncoderValues();

        speed = min(speed + 50, targetSpeed);
    }
    motorDriver.setSpeeds(0, 0);
}

void WheelControls::rotate(int degrees, int targetSpeed)
{

}
