// Sensors connected to Arduino:
// 1. Ultrasonic sensor
// 5. IMU
// 6. GPS

// Actuators connected to Arduino:
// 1. Movement motors (2)
// 2. Collector motor(s) (?)
// 3. Buzzer

void setup()
{
    // TODO: Initialize sensors, actuators, and I2C bus between Arduino and Jetson Nano
}

void loop()
{
    // TODO: wait for a command from the Jetson Nano and execute it
}

bool detectStartSignal()
{
    // TODO: returns true if the green LED is on
}

void moveForward()
{
    // TODO: set direction to forward and drive motors
}

void moveBackward()
{
    // TODO: set direction to backward and drive motors
}

void rotateClockwise()
{
    // TODO: set direction to clockwise and drive motors
}

void rotateCounterClockwise()
{
    // TODO: set direction to counter-clockwise and drive motors
}

void stop()
{
    // TODO: stop motors
}

void returnSensorData()
{
    // TODO: send sensor data to Jetson Nano via I2C bus
}

void errorHandler(String error)
{
    int errorCode = 0;
    // TODO: set error code based on error
    if (error == "")
    {
        return;
    }
    else
    {
    }

    bool errorFixed = false;
    do
    {
        if (!errorFixed)
        {
            playErrorCode(errorCode);
        }
        else
        {
            playErrorFixed();
        }

        errorFixed = isErrorFixed(errorCode);
        delay(5000);
    } while (isDebilitatingError(errorCode));
}

bool isErrorFixed(int errorCode)
{
    // TODO: return true if error code is fixed
    return false;
}

bool isDebilitatingError(int errorCode)
{
    // TODO: return true if error code is debilitating
    return false;
}

void playErrorCode(int errorCode)
{
    // TODO: play sound based on error code using playSound()
}

void playErrorFixed()
{
    // TODO: play sound to indicate error has been fixed
}

void playSound(int freq, int ms)
{
    // TODO: play sound for given number of milliseconds at given frequency
}

// TODO: functions to control collector motor(s)
