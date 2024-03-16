#include <Arduino.h>

#include "./include/Defines.hpp"
#include "./include/FunctionMap.hpp"
#include "./include/Logger.hpp"
#include "./include/Phototransistor.hpp"
#include "./include/RobotArmControl.hpp"
#include "./include/ServoLocks.hpp"
#include "./include/WheelControls.hpp"

#define MAX_ARGS 10

bool hasExecutedOnce = false;

Phototransistor phototransistor = Phototransistor(PHOTOTRANSISTOR_PIN);
RobotArmControl robotArmControl = RobotArmControl();
ServoLocks servoLocks = ServoLocks();
WheelControls wheelControls;

void setup()
{
    Logger::init();

    Logger::log("Initializing robot arm control...");
    robotArmControl.initialize();
    robotArmControl.updatePosition("initial");

    servoLocks.init();
    wheelControls = WheelControls();

    // FunctionMap::init();
    // FunctionMap::addFunctions(robotArmControl.getFunctions(), robotArmControl.getFunctionCount());

    // Attach interrupts == Once a high ENCA is read pulse counting begins
    attachInterrupt(
        digitalPinToInterrupt(WHEELS_M1_ENCA), []()
        { wheelControls.updateLeftEncoder(); },
        RISING);
    attachInterrupt(
        digitalPinToInterrupt(WHEELS_M2_ENCA), []()
        { wheelControls.updateRightEncoder(); },
        RISING);

    Logger::log("Setup complete!");
    delay(5000);
}

void loop()
{
    if (hasExecutedOnce)
    {
        return;
    }

    Logger::log("Starting loop...");
    delay(50); // Small delay for stability
    // collectLargePackages();

    collectSmallPackages();

    // everythingElse();
}

void collectLargePackages()
{
    // delay(1000);
    //  Collect Center package
    robotArmControl.solveIK(-3.81, 13, 1.27);
    robotArmControl.updatePosition("largePackage");

    // Collect Right1 package
    robotArmControl.solveIK(2.54, 14, 2.54);
    robotArmControl.updatePosition("largePackage");

    // Collect Left1 package
    robotArmControl.solveIK(-10, 12, 0);
    robotArmControl.updatePosition("largePackage");

    // Collect Right2 package
    robotArmControl.solveIK(10, 17, 0);
    robotArmControl.updatePosition("largePackage");

    // Collect Left2 package
    robotArmControl.solveIK(-18, 13, -3);
    robotArmControl.updatePosition("largePackage");

    // Return to initial position
    robotArmControl.updatePosition("initial");
}

void collectSmallPackages()
{
    Serial.println("START");
    Serial.println("WAITING");

    while (true)
    {
        if (!Serial.available())
        {
            Logger::log("Waiting for input...");
            delay(1000);
            continue;
        }

        String input = Serial.readString();
        Logger::log("Received input: ");
        Logger::log(input);

        if (input == "END")
        {
            break;
        }

        String command = input.substring(0, input.indexOf(" "));
        input = input.substring(input.indexOf(" ") + 1); // Remove the command and the following space from the input

        String args[MAX_ARGS];

        for (int i = 0; input.indexOf(" ") != -1 && i < MAX_ARGS; i++)
        {
            int spaceIndex = input.indexOf(" ");
            args[i] = input.substring(0, spaceIndex);
            input = input.substring(spaceIndex + 1);
        }

        String log = "Command: ";
        log += command;
        log += " Args: ";
        for (int i = 0; i < MAX_ARGS; i++)
        {
            log += args[i];
            log += " ";
        }
        Logger::log(log);

        if (command == "updatePosition")
        {
            robotArmControl.updatePosition(args[0]);
        }
        else if (command == "solveIK")
        {
            robotArmControl.solveIK(args[0].toDouble(), args[1].toDouble(), args[2].toDouble());
        }
        else if (command == "rotateCounterClockwise")
        {
            // delay(100);
            wheelControls.rotateCounterClockwise(args[0].toFloat(), args[1].toInt());
            Serial.println("WAITING");
        }
        else if (command == "rotateClockwise")
        {
            wheelControls.rotateClockwise(args[0].toFloat(), args[1].toInt());
            Serial.println("WAITING");
        }
        else if (command == "moveForwardEncoders")
        {
            Logger::log("Moving forward...");
            wheelControls.moveForwardEncoders(args[0].toFloat(), args[1].toInt());
            delay(100);
            Serial.println("WAITING");
        }
        else if (command == "moveBackwardEncoders")
        {
            Logger::log("Moving backward...");
            wheelControls.moveBackwardEncoders(args[0].toFloat(), args[1].toInt());
            delay(100);
            Serial.println("WAITING");
            
        }
        else if (command == "pickupSmallPackage")
        {
            robotArmControl.updatePosition("smallPackage");
            delay(100);
            robotArmControl.updatePosition("initial");
            Serial.println("WAITING");
        }
        else if (command == "initial")
        {
            robotArmControl.updatePosition("initial");
            delay(100);
            Serial.println("WAITING");
        }
        else
        {
            Logger::log("Command not found: ", false);
            Logger::log(command);
        }

        Serial.println("WAITING");
    }
}

void everythingElse()
{
    wheelControls.rotateClockwise(55, 100);
    delay(500);

    wheelControls.rotateCounterClockwise(145, 100);
    delay(500);

    wheelControls.moveBackwardEncoders(1, 100);
    delay(100);

    wheelControls.moveForwardEncoders(35.0, 400);
    delay(1000);

    wheelControls.rotateClockwise(180, 100); // 180 degrees
    delay(500);

    Serial.println("Moving backwards...");
    wheelControls.moveBackwardEncoders(25.0, 35);
    delay(500);

    Serial.println("Rotating counterclockwise...");
    wheelControls.rotateCounterClockwise(80, 100);
    delay(500);

    Serial.println("Moving ultrasonics forward...");
    wheelControls.moveUltrasonicsForward(3, 150);
    delay(500);

    Serial.println("Rotating clockwise...");
    wheelControls.rotateCounterClockwise(90, 100);
    delay(500);

    wheelControls.moveUltrasonicsForward(5, 150);
    delay(500);

    wheelControls.rotateClockwise(90, 100);
    delay(500);

    servoLocks.unlockLargePackageContainer();
    delay(100);

    robotArmControl.updatePosition("dropLarge");
    robotArmControl.updatePosition("initial");
    delay(500);

    wheelControls.moveUltrasonicsBackward(6, 150);
    delay(500);

    wheelControls.rotateCounterClockwise(135, 100);
    delay(500);

    servoLocks.unlockSmallPackageContainer();
    delay(500);

    wheelControls.rotateClockwise(45, 100);
    delay(500);

    Serial.println("UltraBackward...");
    wheelControls.moveUltrasonicsBackward(8, 150);
    delay(500);

    wheelControls.rotateCounterClockwise(90, 200);
    delay(500);

    wheelControls.lineFollowConstant(13.0, 100, 75, 75);
    delay(500);

    wheelControls.moveUltrasonicsForward(6, 150);
    delay(500);

    wheelControls.rotateCounterClockwise(83, 100);
    delay(300);

    wheelControls.moveBackwardEncoders(6.0, 150);
    delay(500);

    wheelControls.moveForwardEncoders(38.0, 400);
    delay(1500);

    wheelControls.rotateClockwise(185, 100);
    delay(500);

    wheelControls.moveBackwardUntilSensors(70, 50);
    delay(200);

    wheelControls.moveForwardEncoders(1.0, 100);
    delay(200);

    servoLocks.unlockBridge();
    delay(2000);

    wheelControls.moveBackwardEncoders(2.0,100);
    delay(500);

    wheelControls.moveForwardEncoders(6.0, 100);
    delay(500);

    wheelControls.rotateClockwise(184, 100);
    delay(100);

    wheelControls.moveForwardEncoders(9.0, 200);
    delay(300);

    wheelControls.lineFollowConstant(8.0, 100, 75, 75);
    delay(700);

    wheelControls.moveForwardEncoders(20.0, 200);
    delay(500);

    wheelControls.moveUltrasonicsForward(3, 200);
    delay(500);

    wheelControls.rotateClockwise(80, 100);
    delay(500);

    wheelControls.moveForwardEncoders(5.0, 200);
    delay(500);
}
