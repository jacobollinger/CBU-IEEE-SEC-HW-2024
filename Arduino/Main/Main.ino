#include "./include/Defines.hpp"
#include "./include/FunctionMap.hpp"
#include "./include/Logger.hpp"
#include "./include/Phototransistor.hpp"
#include "./include/RobotArmControl.hpp"

Phototransistor phototransistor = Phototransistor(PHOTOTRANSISTOR_PIN);
RobotArmControl robotArmControl = RobotArmControl();

void setup()
{
    Logger::init();

    Logger::log("Setting up FunctionMap");
    FunctionMap::init();
    // FunctionMap::addFunctions(Class::getFunctions(), Class::getFunctionCount());
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
        // FunctionMap::callFunction(command.c_str(), args.c_str();

        int values[4];
        int i = 0;
        int pos = 0;
        while (i < 4)
        {
            int nextPos = buffer.indexOf(' ', pos);
            if (nextPos == -1)
            {
                values[i] = buffer.substring(pos).toInt();
                break;
            }
            values[i] = buffer.substring(pos, nextPos).toInt();
            pos = nextPos + 1;
            i++;
        }
        Serial.print("Moving to: ");
        Serial.print(values[0]);
        Serial.print(" ");
        Serial.print(values[1]);
        Serial.print(" ");
        Serial.print(values[2]);
        Serial.print(" ");
        Serial.println(values[3]);
        robotArmControl.solveIK(values[0], values[1], values[2]);
    }
}
