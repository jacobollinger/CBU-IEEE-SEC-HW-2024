#include "../include/StartButton.hpp"

StartButton::StartButton(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
    pressed = 0;
}

bool StartButton::isPressed()
{
    return digitalRead(pin) == LOW;
}

bool StartButton::armed()
{
    return pressed > 0;
}

bool StartButton::starting()
{
    return pressed > 1;
}

void StartButton::readPin()
{
    pressed += isPressed();
}