#include <Arduino.h>

#include "./include/Defines.hpp"
#include "./include/FunctionMap.hpp"
#include "./include/LCDScreen.hpp"
#include "./include/Logger.hpp"
#include "./include/Phototransistor.hpp"
#include "./include/RobotArmControl.hpp"
#include "./include/ServoLocks.hpp"
#include "./include/ManualStartButton.hpp"
#include "./include/WheelControls.hpp"

#define MAX_ARGS 10

bool hasExecutedOnce = false;

ManualStartButton manualStartButton = ManualStartButton(START_BUTTON_PIN);
LCDScreen lcdScreen = LCDScreen();
Phototransistor phototransistor = Phototransistor(PHOTOTRANSISTOR_PIN);
RobotArmControl robotArmControl = RobotArmControl();
ServoLocks servoLocks = ServoLocks();
WheelControls wheelControls;

void setup()
{
    Logger::init();

    Logger::log("Initializing robot arm control...");
    robotArmControl.initialize();
    robotArmControl.updatePosition("negativeInitial");

    servoLocks.init();
    wheelControls = WheelControls();

    lcdScreen.init();

    // FunctionMap::init();
    // FunctionMap::addFunctions(robotArmControl.getFunctions(), robotArmControl.getFunctionCount());

    // Attach interrupt == Start button
    attachInterrupt(
        digitalPinToInterrupt(START_BUTTON_PIN), []()
        { manualStartButton.readPin(); },
        FALLING);

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

    String input = "";
    // while (!startButton.armed() && input != "arm")
    // {
    //     Logger::log("Waiting for input...");
    //     if (Serial.available())
    //     {
    //         input = Serial.readString();
    //         String command = input.substring(0, input.indexOf(" "));
    //         String args[MAX_ARGS];
    //         input = input.substring(input.indexOf(" ") + 1); // Remove the command and the following space from the input
    //         if (input.indexOf(" ") != -1)
    //         {
    //             for (int i = 0; input.indexOf(" ") != -1 && i < MAX_ARGS; i++)
    //             {
    //                 int spaceIndex = input.indexOf(" ");
    //                 args[i] = input.substring(0, spaceIndex);
    //                 input = input.substring(spaceIndex + 1);
    //             }
    //         }
    //         if (command == "updatePosition")
    //         {
    //             robotArmControl.updatePosition(args[0]);
    //         }
    //         else if (command == "solveIK")
    //         {
    //             robotArmControl.solveIK(args[0].toDouble(), args[1].toDouble(), args[2].toDouble());
    //         }
    //         else if (command == "rotateCounterClockwise")
    //         {
    //             wheelControls.rotateCounterClockwise(args[0].toFloat(), args[1].toInt());
    //         }
    //         else if (command == "rotateClockwise")
    //         {
    //             wheelControls.rotateClockwise(args[0].toFloat(), args[1].toInt());
    //         }
    //         else if (command == "moveForwardEncoders")
    //         {
    //             Logger::log("Moving forward...");
    //             wheelControls.moveForwardEncoders(args[0].toFloat(), args[1].toInt());
    //         }
    //         else if (command == "moveBackwardEncoders")
    //         {
    //             Logger::log("Moving backward...");
    //             wheelControls.moveBackwardEncoders(args[0].toFloat(), args[1].toInt());
    //         }
    //         else if (command == "collectLargePackages")
    //         {
    //             collectLargePackages();
    //         }
    //         else if (command == "initial")
    //         {
    //             robotArmControl.updatePosition("initial");
    //         }
    //         else if (command == "sweepPackages")
    //         {
    //             sweepSmallPackages();
    //         }
    //         else if (command == "sweep")
    //         {
    //             robotArmControl.updatePosition("sweep");
    //         }
    //         else if (command == "promo")
    //         {
    //             lcdScreen.teamPromo();
    //         }
    //         else if (command == "unlock")
    //         {
    //             servoLocks.unlockAll();
    //         }
    //         else if (command == "lock")
    //         {
    //             servoLocks.lockAll();
    //         }
    //         else
    //         {
    //             Logger::log("Command not found: ", false);
    //             Logger::log(command);
    //         }
    //     }
    // }

    // Logger::log("Armed! Waiting for start signal or button press...");
}

void loop()
{
    if (hasExecutedOnce)
    {
        return;
    }

    delay(50); // Small delay for stability

    // Logger::log("Waiting for start button press...");
    // while (!startButton.isPressed())
    // {
    // }

    waitForStartLED();

    collectLargePackages();

    // // collectSmallPackages();
    sweepSmallPackages();

    everythingElse();

    Logger::log("Done!");
    hasExecutedOnce = true;
}

void waitForStartLED()
{
    while (!phototransistor.isIlluminated(PHOTOTRANSISTOR_THRESHOLD) && !manualStartButton.isPressed())
    {
        String log = "Waiting for light. Light level: ";
        log += phototransistor.read();
        Logger::log(log);
        delay(20);
    }
}

void collectLargePackages()
{
    // // Collect Center package
    // robotArmControl.solveIK(-3.25, 13, 1.27);
    // robotArmControl.updatePosition("largePackage2");

    // // Collect Right1 package
    // robotArmControl.solveIK(2.25, 15, 1.27);
    // robotArmControl.updatePosition("largePackage");

    // // Collect Left1 package
    // robotArmControl.solveIK(-10, 13, 0);
    // robotArmControl.updatePosition("largePackage");

    // // Collect Right2 package
    // // robotArmControl.solveIK(9, 17, 0);
    // // robotArmControl.updatePosition("largePackage");

    // // Collect Left2 package
    // robotArmControl.solveIK(-16.5, 14.75, -1);
    // robotArmControl.updatePosition("largePackage");

    robotArmControl.solveIK(-3.5, 14, 4);
    robotArmControl.updatePosition("largePackage2");

    // Collect Right1 package
    robotArmControl.solveIK(2.5, 15.5, 3);
    robotArmControl.updatePosition("largePackage");

    // Collect Left1 package
    robotArmControl.solveIK(-10, 13, 0);
    robotArmControl.updatePosition("largePackage");
}

void sweepSmallPackages()
{
    wheelControls.rotateClockwise(63, 250);
    delay(20);
    wheelControls.moveBackwardEncoders(2, 100);
    delay(20);
    wheelControls.rotateCounterClockwise(162, 250);
    delay(20);
    // wheelControls.moveBackwardEncoders(2, 100);
    // delay(20);

    wheelControls.moveForwardEncoders(2, 100);
    delay(20);
    wheelControls.lineFollowConstant(6, 100, 75, 75);
    delay(20);
    wheelControls.moveBackwardEncoders(7, 100);
    delay(20);
    robotArmControl.updatePosition("sweep");
    delay(20);
    robotArmControl.updatePosition("disposeSweep");
    delay(10);
    robotArmControl.updatePosition("negativeInitial");
    delay(10);
    wheelControls.moveBackwardEncoders(4, 100);
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
            wheelControls.rotateCounterClockwise(args[0].toFloat(), args[1].toInt());
        }
        else if (command == "rotateClockwise")
        {
            wheelControls.rotateClockwise(args[0].toFloat(), args[1].toInt());
        }
        else if (command == "moveForwardEncoders")
        {
            Logger::log("Moving forward...");
            wheelControls.moveForwardEncoders(args[0].toFloat(), args[1].toInt());
        }
        else if (command == "moveBackwardEncoders")
        {
            Logger::log("Moving backward...");
            wheelControls.moveBackwardEncoders(args[0].toFloat(), args[1].toInt());
        }
        else if (command == "pickupSmallPackage")
        {
            robotArmControl.updatePosition("smallPackage");
            robotArmControl.updatePosition("initial");
        }
        else if (command == "initial")
        {
            robotArmControl.updatePosition("initial");
        }
        else if (command == "sweep")
        {
            robotArmControl.updatePosition("sweep");
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
    // robotArmControl.updatePosition("initial");
    // delay(20);

    // robotArmControl.updatePosition("centerGravityForward");
    // delay(20);

    wheelControls.moveForwardEncoders(32.0, 400);
    delay(20);
    // delay(100);

    // robotArmControl.updatePosition("negativeInitial");
    // delay(20);

    wheelControls.rotateClockwise(175, 250);
    delay(20);

    wheelControls.moveBackwardEncoders(19.0, 200);
    delay(20);

    wheelControls.rotateCounterClockwise(90, 250);
    delay(20);

    wheelControls.moveUltrasonicsForward(3, 250);
    delay(20);

    wheelControls.moveUltrasonicsBackward(6, 200);
    delay(20);

    wheelControls.rotateCounterClockwise(90, 225);
    delay(20);

    wheelControls.lineFollowConstant(9.0, 100, 75, 75);

    wheelControls.moveUltrasonicsForward(8, 250);

    wheelControls.rotateClockwise(85, 250);
    delay(20);

    wheelControls.moveUltrasonicsBackward(9, 250);
    delay(20);

    // wheelControls.rotateClockwise(90, 100);
    // delay(20);

    servoLocks.unlockLargePackageContainer();
    delay(20);

    robotArmControl.updatePosition("dropLarge");
    delay(20);

    robotArmControl.updatePosition("negativeInitial");
    delay(20);

    // wheelControls.moveUltrasonicsBackward(7, 250);
    // delay(20);

    wheelControls.rotateCounterClockwise(100, 250);
    delay(20);

    // servoLocks.unlockSmallPackageContainer();
    // delay(20);

    // robotArmControl.updatePosition("dropSmall");
    // delay(20);

    // robotArmControl.updatePosition("initial");
    // delay(20);

    // wheelControls.rotateClockwise(45, 100);
    // delay(20);

    wheelControls.moveUltrasonicsBackward(7, 200);
    delay(20);

    wheelControls.rotateCounterClockwise(80, 250);
    // delay(20);

    wheelControls.lineFollowConstant(9.0, 100, 75, 75);
    delay(20);

    wheelControls.moveUltrasonicsForward(8, 200);
    delay(20);

    wheelControls.rotateCounterClockwise(85, 250);
    delay(20);

    // robotArmControl.updatePosition("initial");
    // delay(20);

    // robotArmControl.updatePosition("centerGravityForward");
    // delay(20);

    wheelControls.moveForwardEncoders(27.5, 400);
    delay(500);
    // delay(1500);

    // robotArmControl.updatePosition("initial");
    // delay(20);

    // robotArmControl.updatePosition("negativeInitial");
    // delay(20);

    wheelControls.rotateClockwise(180, 250);
    delay(20);

    wheelControls.moveBackwardUntilSensors(40, 50);
    delay(20);

    wheelControls.moveForwardEncoders(0.5, 100);
    delay(20);

    servoLocks.unlockBridge();
    delay(1300);

    // wheelControls.moveBackwardEncoders(2.0, 100);
    // delay(20);

    wheelControls.moveForwardEncoders(1.0, 200);
    delay(20);

    wheelControls.rotateClockwise(180, 200);
    delay(20);

    wheelControls.moveForwardEncoders(7.0, 200);
    delay(100);

    Logger::log("Line follow");
    wheelControls.lineFollowConstant(5.0, 100, 75, 75);
    delay(100);

    // robotArmControl.updatePosition("centerGravityForward");
    // robotArmControl.updatePosition("negativeInitial");
    // delay(20);

    Logger::log("Forward after line follow");
    wheelControls.moveForwardEncoders(20.0, 400);
    delay(20);

    Logger::log("Team promo");
    lcdScreen.teamPromo();
    delay(20);

    Logger::log("Ultrasonics after team promo");
    wheelControls.moveUltrasonicsForward(3, 400);
    delay(20);

    Logger::log("Rotate after ultrasonics");
    wheelControls.rotateClockwise(80, 250);
    delay(20);

    Logger::log("Push button");
    wheelControls.moveForwardEncoders(8.0, 200);
    delay(20);
}
