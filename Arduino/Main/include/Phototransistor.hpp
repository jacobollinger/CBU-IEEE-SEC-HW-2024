#ifndef PHOTOTRANSISTOR_HPP
#define PHOTOTRANSISTOR_HPP

#include <Arduino.h>

class Phototransistor {
  public:
    Phototransistor(int pin);
    int read();
    bool isIlluminated(int threshold);
  private:
    int _pin;
};

#endif // PHOTOTRANSISTOR_HPP
