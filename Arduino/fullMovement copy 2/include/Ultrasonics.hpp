#include <NewPing.h>

#define FRONT_TRIG 26
#define FRONT_ECHO 27
#define RIGHT_TRIG 26
#define RIGHT_ECHO 27

#define MAX_DISTANCE 200

class Ultrasonics
{
public:
    Ultrasonics();
    float getFrontDistance();
    float getRightDistance();

private:
    NewPing front, right;
};