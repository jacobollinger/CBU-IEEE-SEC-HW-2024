#include "./include/Defines.hpp"
#include "./include/FunctionMap.hpp"
#include "./include/Logger.hpp"
#include "./include/RobotArmControl.hpp"
#include "./include/Wheels.hpp"

RobotArmControl robotArmControl = RobotArmControl();

void setup()
{
    Logger::init();

    Logger::log("Setting up FunctionMap");
    FunctionMap::init();
    FunctionMap::addFunctions(Wheels::getFunctions(), Wheels::getFunctionCount());
    // TODO: Add functions from other modules

    Logger::log("Initializing robot arm control");
    robotArmControl.initialize();

}

void loop()
{
    if(Serial.available())
    {
        String buffer = Serial.readString();
        String command = buffer.substring(0, buffer.indexOf(' '));
        String args = buffer.substring(buffer.indexOf(' ') + 1);

        // TODO: Execute command from buffer
        FunctionMap::callFunction(command.c_str(), args.c_str();
    }
}
