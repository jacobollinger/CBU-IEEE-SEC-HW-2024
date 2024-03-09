#include "./include/Defines.hpp"
#include "./include/FunctionMap.hpp"
#include "./include/Logger.hpp"
#include "./include/Phototransistor.hpp"
#include "./include/RobotArmControl.hpp"
#include "./include/ServoLocks.hpp"
#include "./include/WheelControls.hpp"

bool hasExecutedOnce = false;

Phototransistor phototransistor = Phototransistor(PHOTOTRANSISTOR_PIN);
RobotArmControl robotArmControl = RobotArmControl();
ServoLocks servoLocks = ServoLocks();
WheelControls wheelControls = WheelControls();

void setup()
{
    Logger::init();

    Logger::log("Setting up FunctionMap");
    FunctionMap::init();
    // FunctionMap::addFunctions(Class::getFunctions(), Class::getFunctionCount());
    // TODO: Add functions from other modules

    Logger::log("Initializing robot arm control");
    robotArmControl.initialize();
    robotArmControl.updatePosition("initial");

    Logger::log("Initializing servo locks");
    servoLocks.init();

    Logger::log("Initializing wheel controls");
    wheelControls.init();
}

void loop()
{
    if (hasExecutedOnce)
    {
        return;
    }

    // Wait for phototransistor to be triggered
    while (!phototransistor.isIlluminated(PHOTOTRANSISTOR_THRESHOLD))
    {
        delay(100);
    }

    Logger::log("Collecting large packages");
    collectLargePackages();
    Logger::log("Done collecting large packages");
    delay(1000);

    Logger::log("Collecting small packages");
    collectSmallPackages();
    Logger::log("Done collecting small packages");

    // Do the rest of the tasks
    doEverythingElse();

    // Prevents the loop from running again
    hasExecutedOnce = true;
}

void collectLargePackages(){
    //delay(1000);
    // Collect Center package 
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
}

void collectSmallPackages()
{
    // Give Jetson controls to pick up small packages
    bool pickingUpSmallPackages = true;
    Serial.println("ready");
    while (pickingUpSmallPackages)
    {
        if (!Serial.available())
        {
            continue;
        }

        String buffer = Serial.readStringUntil('\n');

        if (buffer == "done")
        {
            pickingUpSmallPackages = false;
            continue;
        }

        String command = buffer.substring(0, buffer.indexOf(' '));
        String args = buffer.substring(buffer.indexOf(' ') + 1);

        // TODO: Execute command from buffer
        // FunctionMap::callFunction(command.c_str(), args.c_str());
    }
}

void doEverythingElse()
{
    wheelControls.rotateCounterClockwise(15, 100);
    delay(1000);

    wheelControls.moveForwardEncoders(2, 100);
    delay(1000);

    wheelControls.rotateCounterClockwise(60, 100);
    delay(1000);

    wheelControls.moveBackwardEncoders(1, 100);
    delay(100);

    wheelControls.moveForwardEncoders(35.0, 400);
    delay(1000);

    wheelControls.rotateClockwise(180, 100);
    delay(1000);

    wheelControls.moveBackwardEncoders(25.0, 35);
    delay(1000);

    wheelControls.rotateCounterClockwise(80, 100);
    delay(500);

    wheelControls.moveUltrasonicsForward(3, 150);
    delay(500);

    wheelControls.rotateCounterClockwise(90, 100);
    delay(500);

    wheelControls.moveUltrasonicsForward(5, 150);
    delay(500);

    wheelControls.rotateClockwise(90, 100);
    delay(500);

    servoLocks.unlockLargePackageContainer();
    delay(100);

    wheelControls.moveUltrasonicsBackward(6, 150);
    delay(500);

    wheelControls.rotateCounterClockwise(135, 100);
    delay(500);

    servoLocks.unlockSmallPackageContainer();
    delay(500);

    wheelControls.rotateClockwise(45, 100);
    delay(1000);

    Serial.println("UltraBackward...");
    wheelControls.moveUltrasonicsBackward(8, 150);
    delay(1000);

    wheelControls.rotateCounterClockwise(85, 200);
    delay(1000);

    wheelControls.lineFollowConstant(15.0, 100, 75, 75);
    delay(100);

    wheelControls.moveUltrasonicsForward(6, 150);
    delay(500);

    wheelControls.rotateCounterClockwise(83, 100);
    delay(100);

    wheelControls.moveBackwardEncoders(6.0, 150);
    delay(1000);

    wheelControls.moveForwardEncoders(38.0, 400);
    delay(2000);

    wheelControls.rotateClockwise(180, 100);
    delay(1000);

    wheelControls.moveBackwardUntilSensors(70, 50);
    delay(100);

    wheelControls.moveForwardEncoders(1.0, 100);
    delay(100);

    servoLocks.unlockBridge();
    delay(2000);

    wheelControls.moveForwardEncoders(3.0, 100);
    delay(1000);

    wheelControls.rotateClockwise(184, 100);
    delay(100);

    wheelControls.moveForwardEncoders(5.0, 100);
    delay(1000);

    wheelControls.lineFollowConstant(5.0, 100, 75, 75);
    delay(100);

    wheelControls.moveForwardEncoders(10.0, 100);
    delay(100);

    wheelControls.moveUltrasonicsForward(3, 200);
    delay(100);

    wheelControls.rotateClockwise(80, 100);
    delay(100);

    wheelControls.moveForwardEncoders(5.0, 200);
    delay(100);
}
