#include "../include/Ultrasonics.hpp"

Ultrasonics::Ultrasonics() : front(FRONT_TRIG, FRONT_ECHO, MAX_DISTANCE), right(RIGHT_TRIG, RIGHT_ECHO, MAX_DISTANCE)
{
}

float Ultrasonics::getFrontDistance()
{
    return front.ping_in();
}

float Ultrasonics::getRightDistance()
{
    return right.ping_in();
}