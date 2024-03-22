#include "../include/ServoLocks.hpp"

const int delayTime = 300;

ServoLocks::ServoLocks()
{
}

void ServoLocks::init()
{
    // smallPackageContainerLock.attach(13);
    largePackageContainerLock.attach(4);
    bridgeLock.attach(5);

    smallPackageContainerLock.write(smallPackageLockPos);
    delay(delayTime);
    bridgeLock.write(bridgeLockPos);
    delay(delayTime);
    largePackageContainerLock.write(largePackageLockPos);
    delay(delayTime);
}

void ServoLocks::unlockSmallPackageContainer()
{
    smallPackageContainerLock.write(smallPackageUnlockPos);
    delay(delayTime);
}

void ServoLocks::unlockLargePackageContainer()
{
    largePackageContainerLock.write(largePackageUnlockPos);
    delay(delayTime);
}

void ServoLocks::unlockBridge()
{
    bridgeLock.write(bridgeUnlockPos);
    delay(delayTime);
}

void ServoLocks::lockAll()
{
    smallPackageContainerLock.write(smallPackageLockPos);
    delay(delayTime);
    largePackageContainerLock.write(largePackageLockPos);
    delay(delayTime);
    bridgeLock.write(bridgeLockPos);
    delay(delayTime);
}

void ServoLocks::unlockAll()
{
    smallPackageContainerLock.write(bridgeLockPos);
    delay(delayTime);
    largePackageContainerLock.write(largePackageUnlockPos);
    delay(delayTime);
    bridgeLock.write(bridgeUnlockPos);
    delay(delayTime);
}
