#include "Main.hpp"

int main()
{
    // DEBUG("Initializing...");
    init();
    // DEBUG("Initialization complete. Waiting to start.");
    waitToStart();
    // DEBUG("Starting...");
    start();
    
    // TODO: Main block of code

    stop();

    return 0;
}

void init()
{
    timer = Timer();
}

void waitToStart()
{
}

void start()
{
    timer.start();
}

void stop()
{
    timer.stop();
    // DEBUG("Time elapsed: " << timer.getDuration() << " seconds.");
}
