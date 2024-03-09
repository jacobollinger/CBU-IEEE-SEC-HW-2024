#include <Arduino.h>

#include "./include/ServoLocks.hpp"
#include "./include/WheelControls.hpp"

WheelControls wheelControls = WheelControls();
ServoLocks servoLocks = ServoLocks();

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting...");

    servoLocks.init();
    wheelControls.init();

    // Attach interrupts == Once a high ENCA is read pulse counting begins
    attachInterrupt(
        digitalPinToInterrupt(WHEELS_M1_ENCA), []()
        { wheelControls.updateLeftEncoder(); },
        RISING);
    attachInterrupt(
        digitalPinToInterrupt(WHEELS_M2_ENCA), []()
        { wheelControls.updateRightEncoder(); },
        RISING);

    for (int i = 0; i < 3; i++)
    {
        Serial.println(3 - i);
        delay(1000);
    }
}

void loop()
{
    Serial.println("Top of the loop");
    delay(50); // Small delay for stability

    // pickupLargePackages();

    // pickupSmallPackages();

    doEverythingElse();

    Serial.print("done");

    delay(100000);
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

    wheelControls.moveForwardEncoders(15.0, 100);
    delay(100);

    wheelControls.moveUltrasonicsForward(3, 200);
    delay(100);

    wheelControls.rotateClockwise(80, 100);
    delay(100);

    wheelControls.moveForwardEncoders(5.0, 200);
    delay(100);
}