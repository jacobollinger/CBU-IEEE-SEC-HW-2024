#include "../include/ManualStartButton.hpp"

ManualStartButton::ManualStartButton(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
    pressed = 0;
}

bool ManualStartButton::isPressed()
{
    return digitalRead(pin) == LOW;
}

void ManualStartButton::readPin()
{
    pressed += isPressed();
}