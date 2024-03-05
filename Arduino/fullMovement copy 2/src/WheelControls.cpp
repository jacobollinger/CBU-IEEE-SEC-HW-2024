#include "../include/WheelControls.hpp"

#define INCH_PER_REV 32.0 / 7100.0
#define ULTRASONIC_THRESHOLD 0.5

WheelControls::WheelControls() : motorDriver(DualG2HighPowerMotorShield24v14(WHEELS_M1_SLP, WHEELS_M1_DIR, WHEELS_M1_PWM, WHEELS_M1_FLT, WHEELS_M1_CS, WHEELS_M2_SLP, WHEELS_M2_DIR, WHEELS_M2_PWM, WHEELS_M2_FLT, WHEELS_M2_CS)), leftEncoder(WheelEncoder(WHEELS_M1_ENCA, WHEELS_M1_ENCB, false)), rightEncoder(WheelEncoder(WHEELS_M2_ENCA, WHEELS_M2_ENCB, true))
{
    motorDriver.init();
    //! This makes the arduino freeze
    // motorDriver.calibrateCurrentOffsets();
    motorDriver.enableDrivers();
    ultrasonics = Ultrasonics();
    leftEncoder.clear();
    rightEncoder.clear();
}

int *WheelControls::getEncoderPositions()
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

void WheelControls::updateLeftEncoder()
{
    leftEncoder.update();
}

void WheelControls::updateRightEncoder()
{
    rightEncoder.update();
}

void WheelControls::moveForwardEncoders(float distance, int targetSpeed)
{
    clearEncoders();
    float targetRotations = distance / (INCH_PER_REV);
    int *currentPositions = getEncoderPositions();
    int speed = 400;
    // targetSpeed = min(targetSpeed, WHEEL_MAX_SPEED);

    while (currentPositions[0] < targetRotations)
    {
        Serial.print(currentPositions[0]);
        Serial.print(" ");
        Serial.print(targetRotations);
        bool temp = currentPositions[0] < targetRotations;
        Serial.println(temp);

        motorDriver.setSpeeds(speed, speed);
        currentPositions = getEncoderPositions();

        // speed = min(speed + 25, targetSpeed);
    }
    Serial.print(currentPositions[0]);
    Serial.print(" ");
    Serial.print(targetRotations);
    bool temp = currentPositions[0] < targetRotations;
    Serial.println(temp);
    motorDriver.setSpeeds(0, 0);
}

void WheelControls::moveBackwardEncoders(float distance, int targetSpeed)
{
    clearEncoders();
    float targetRotations = distance / (INCH_PER_REV);
    int *currentPositions = getEncoderPositions();
    int speed = 400;
    // targetSpeed = min(targetSpeed, WHEEL_MAX_SPEED);

    while (currentPositions[0] < targetRotations)
    {
        Serial.print(currentPositions[1]);
        Serial.print(" ");
        Serial.println(targetRotations);
        
        motorDriver.setM1Speed(-400);
        motorDriver.setM2Speed(-400);
        currentPositions = getEncoderPositions();
        delay(100);

        // speed = min(speed + 25, targetSpeed);
    }
    motorDriver.setSpeeds(0, 0);
}

void WheelControls::rotateClockwise(float degrees, int targetSpeed)
{
    clearEncoders();
    float targetRotations = degrees * PULSE_PER_DEG;
    int *currentPositions = getEncoderPositions();
    int speed = 200;
    targetSpeed = min(targetSpeed, WHEEL_MAX_SPEED);

    while (currentPositions[0] < targetRotations && currentPositions[1] > -targetRotations)
    {
        motorDriver.setSpeeds(speed, -speed);
        currentPositions = getEncoderPositions();

        // speed = min(speed + 50, targetSpeed);
    }
    motorDriver.setSpeeds(0, 0);
}

void WheelControls::rotateCounterClockwise(float degrees, int targetSpeed)
{
    clearEncoders();
    float targetRotations = degrees * PULSE_PER_DEG;
    int *currentPositions = getEncoderPositions();
    int speed = 200;
    targetSpeed = min(targetSpeed, WHEEL_MAX_SPEED);

    while (currentPositions[1] < targetRotations)
    {
        Serial.print(currentPositions[1]);
        Serial.print(" ");
        Serial.println(targetRotations);

        motorDriver.setSpeeds(speed, -speed);
        currentPositions = getEncoderPositions();
        delay(100);

        // speed = min(speed + 50, targetSpeed);
    }
    motorDriver.setSpeeds(0, 0);
}

void WheelControls::moveUltrasonicsForward(float targetDistance, int speed)
{
    float distanceFront = ultrasonics.getFrontDistance();
    while (distanceFront > targetDistance) // + ULTRASONIC_THRESHOLD || distanceFront < targetDistance - ULTRASONIC_THRESHOLD)
    {
        distanceFront = ultrasonics.getFrontDistance();
        Serial.println(distanceFront);
        // if (distanceFront > targetDistance)
        // {
        motorDriver.setSpeeds(speed, speed);
        // }
        // else
        // {
        //     motorDriver.setSpeeds(-speed, -speed);
        // }
        delay(100);
    }
    motorDriver.setSpeeds(0, 0);
}

void WheelControls::lineFollowConstant(float targetDistance, int targetSpeed, int right, int left)
{
    clearEncoders();
    int *currentPositions = getEncoderPositions();
    int speed = WHEEL_MIN_SPEED;
    targetSpeed = min(targetSpeed, WHEEL_MAX_SPEED);

    while (currentPositions[0] < targetDistance && currentPositions[1] < targetDistance)
    {
        const float targetRotations = targetDistance / INCH_PER_REV;
        clearEncoders();
        int *currentPositions = getEncoderPositions();
        int leftSensorValue = analogRead(LINE_FOLLOW_LEFT);
        int rightSensorValue = analogRead(LINE_FOLLOW_RIGHT_THRESHOLD);

        while (currentPositions[1] < targetRotations)
        {
            // Read encoder positions
            currentPositions = getEncoderPositions();

            int leftSensorValue = analogRead(LINE_FOLLOW_LEFT_THRESHOLD);
            int rightSensorValue = analogRead(LINE_FOLLOW_RIGHT_THRESHOLD);

            if (leftSensorValue < LINE_FOLLOW_LEFT_THRESHOLD && rightSensorValue < LINE_FOLLOW_RIGHT_THRESHOLD)
            {
                // Both sensors on the line - move forward
                motorDriver.setSpeeds(speed, speed);
            }
            else if (leftSensorValue < LINE_FOLLOW_LEFT_THRESHOLD)
            {
                // Left sensor on the line - turn right
                motorDriver.setSpeeds(right, -right);
            }
            else if (rightSensorValue < LINE_FOLLOW_RIGHT_THRESHOLD)
            {
                // Right sensor on the line - turn left
                motorDriver.setSpeeds(-left, left);
            }
            else
            {
                // Both sensors off the line - stop
                motorDriver.setM1Speed(0);
                motorDriver.setM2Speed(0);
            }
        }

        motorDriver.setSpeeds(0, 0);
    }
}
