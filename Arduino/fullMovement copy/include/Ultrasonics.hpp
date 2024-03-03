#include <NewPing.h>

#define FRONT_TRIG 26
#define FRONT_ECHO 27
#define LEFT_TRIG
#define LEFT_ECHO
#define MAX_DISTANCE 200

class Ultrasonics
{
public:
    Ultrasonics();
    float getFrontDistance();
    float getLeftDistance();

private:
    NewPing frontSensor;
    // NewPing leftSensor;
};