#ifndef MANUAL_START_BUTTON_HPP
#define MANUAL_START_BUTTON_HPP

#include "Arduino.h"

class ManualStartButton {
public:
    ManualStartButton(int pin);
    bool isPressed();
    void readPin();

private:
    int pin;
    int pressed;
};

#endif // MANUAL_START_BUTTON_HPP
