#include "../include/ServoLocks.hpp"

ServoLocks::ServoLocks()
{
}

void ServoLocks::init()
{
    smallPackageContainerLock.attach(4);
    largePackageContainerLock.attach(5);
    bridgeLock.attach(13);

    smallPackageContainerLock.write(smallPackageLockPos);
    delay(600);
    bridgeLock.write(bridgeLockPos);
    delay(600);
    largePackageContainerLock.write(largePackageLockPos);
    delay(600);
}

void ServoLocks::unlockSmallPackageContainer()
{
    smallPackageContainerLock.write(smallPackageUnlockPos);
    delay(600);
}

void ServoLocks::unlockLargePackageContainer()
{
    largePackageContainerLock.write(largePackageUnlockPos);
    delay(600);
}

void ServoLocks::unlockBridge()
{
    bridgeLock.write(bridgeUnlockPos);
    delay(600);
}

void ServoLocks::lockAll()
{
    smallPackageContainerLock.write(smallPackageLockPos);
    delay(600);
    largePackageContainerLock.write(largePackageLockPos);
    delay(600);
    bridgeLock.write(bridgeLockPos);
    delay(600);
}

void ServoLocks::unlockAll()
{
    smallPackageContainerLock.write(bridgeLockPos);
    delay(600);
    largePackageContainerLock.write(largePackageUnlockPos);
    delay(600);
    bridgeLock.write(bridgeUnlockPos);
    delay(600);
}

