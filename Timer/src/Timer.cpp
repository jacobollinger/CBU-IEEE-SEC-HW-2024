#include "Timer.hpp"

Timer::Timer()
{
    running = false;
    startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
    endTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
}

void Timer::start()
{
    startTime = std::chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop()
{
    endTime = std::chrono::high_resolution_clock::now();
    running = false;
}

double Timer::getDuration()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
    if (running)
    {
        endTime = std::chrono::high_resolution_clock::now();
    }
    else
    {
        endTime = this->endTime;
    }
    return (double) std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
}
