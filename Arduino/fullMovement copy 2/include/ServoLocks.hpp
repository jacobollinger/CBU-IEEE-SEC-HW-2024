#ifndef SERVOLOCKS_HPP
#define SERVOLOCKS_HPP

#include <Arduino.h>
#include <Servo.h>

class ServoLocks
{
public:
    ServoLocks();
    void init();
    void unlockSmallPackageContainer();
    void unlockLargePackageContainer();
    void unlockBridge();
    void lockAll();
    void unlockAll();

private:
    Servo smallPackageContainerLock; // servo for the small container d4
    Servo largePackageContainerLock; // servo for the large container d5
    Servo bridgeLock;                // servo for the bridge d13

    int smallPackageLockPos = 90;    // servo1 position for setup
    int smallPackageUnlockPos = 0;   // servo1 to drop container and bridge
    int bridgeLockPos = 0;           // servo1 to drop container and bridge
    int bridgeUnlockPos = 180;       // servo3 position for the bridge
    int largePackageLockPos = 50;    // servo2 posiiton for setup
    int largePackageUnlockPos = 150; // servo2 to drop container
};

#endif // SERVOLOCKS_HPP
