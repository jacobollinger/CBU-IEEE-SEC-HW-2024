#ifndef START_BUTTON_HPP
#define START_BUTTON_HPP

#include "Arduino.h"

class StartButton {
public:
    StartButton(int pin);
    bool isPressed();
    bool armed();
    bool starting();
    void readPin();

private:
    int pin;
    int pressed;
};

#endif // START_BUTTON_HPP
