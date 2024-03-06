#include "../include/Phototransistor.hpp"

Phototransistor::Phototransistor(int pin) {
  _pin = pin;
  pinMode(_pin, INPUT);
}

int Phototransistor::read() {
  return analogRead(_pin);
}

bool Phototransistor::isIlluminated(int threshold) {
  return read() > threshold;
}