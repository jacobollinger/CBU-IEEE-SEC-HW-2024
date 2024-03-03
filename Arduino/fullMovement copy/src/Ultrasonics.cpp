#include "../include/Ultrasonics.hpp"
#include <NewPing.h> // Add the include statement for the "NewPing" library


Ultrasonics::Ultrasonics() : frontSensor(26, 27, 200)
{
}

float Ultrasonics::getFrontDistance()
{
    return frontSensor.ping_in();
}

float Ultrasonics::getLeftDistance()
{
    return 0;
}
