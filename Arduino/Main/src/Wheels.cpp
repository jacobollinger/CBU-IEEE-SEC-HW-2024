#include "../include/Wheels.hpp"

DualG2HighPowerMotorShield24v14 Wheels::md(
    WHEELS_M1_SLP, WHEELS_M1_DIR, WHEELS_M1_PWM, WHEELS_M1_FLT, WHEELS_M1_CS,
    WHEELS_M2_SLP, WHEELS_M2_DIR, WHEELS_M2_PWM, WHEELS_M2_FLT, WHEELS_M2_CS);

void Wheels::init(const char *args[])
{
    md.init();
    md.calibrateCurrentOffsets();
    // md.flipM1(true);
    // md.flipM2(true);
    md.enableDrivers();
}

void Wheels::moveForward(const char *args[])
{
    int speed = 100; // atoi(args[0]);
    float distance = 1; // atof(args[1]);
    move(min(speed, WHEEL_MAX_SPEED), 1, distance);
}

void Wheels::moveBackward(const char *args[])
{
    int speed = 100; // atoi(args[0]);
    float distance = 1; // atof(args[1]);
    move(min(speed, WHEEL_MAX_SPEED), -1, distance);
}

void Wheels::rotate(const char *args[])
{
}

void Wheels::stop(const char *args[])
{
    md.setSpeeds(0, 0);
}

void Wheels::move(int speed, int direction, int distance)
{
    md.setSpeeds(speed * direction, speed * direction);
    // TODO: Replace with encoder feedback
    while (distance > 0)
    {
        delay(100);
        distance -= 0.1;
    }
    md.setSpeeds(0, 0);
}

void Wheels::rampUp(int speed, int motor1Direction, int motor2Direction)
{
    // int rampSpeed = 0;
    // while (rampSpeed < speed)
    // {
    //     motor1.setSpeed(rampSpeed * motor1Direction);
    //     motor2.setSpeed(rampSpeed * motor2Direction);
    //     rampSpeed += 10;
    //     delay(100);
    // }
    // return rampSpeed;
}

int Wheels::getFunctionCount()
{
    return 5;
}

FunctionMap::Function *Wheels::getFunctions()
{
    FunctionMap::Function *functions = new FunctionMap::Function[getFunctionCount()];
    functions[0].name = "init";
    functions[0].function = &Wheels::init;
    functions[1].name = "moveForward";
    functions[1].function = &Wheels::moveForward;
    functions[2].name = "moveBackward";
    functions[2].function = &Wheels::moveBackward;
    functions[3].name = "rotate";
    functions[3].function = &Wheels::rotate;
    functions[4].name = "stop";
    functions[4].function = &Wheels::stop;
    return functions;
}
