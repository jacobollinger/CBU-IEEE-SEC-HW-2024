#ifndef WHEELS_HPP
#define WHEELS_HPP

#include <Arduino.h>
#include <DualG2HighPowerMotorShield.h>

#include "Defines.hpp"
#include "FunctionMap.hpp"
#include "Logger.hpp"

class Wheels
{
private:
    static DualG2HighPowerMotorShield24v14 md;

    static void move(int speed, int direction, int distance);
    static void rampUp(int speed, int motor1Direction, int motor2Direction);

public:
    static void init(const char *args[] = nullptr);
    static void moveForward(const char *args[]);
    static void moveBackward(const char *args[]);
    static void rotate(const char *args[]);
    static void stop(const char *args[]);

    static int getFunctionCount();
    static FunctionMap::Function *getFunctions();
};
#endif // WHEELS_HPP
