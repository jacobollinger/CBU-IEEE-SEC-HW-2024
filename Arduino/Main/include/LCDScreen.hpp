// Define your Library; makes sure name is not taken
#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H

// Include libraries you will use
#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Defines.hpp"

class LCDScreen
{
public:
    // define functions
    LCDScreen();
    void init();
    void teamPromo();

private:
    LiquidCrystal promoLCD; // Update Pins
};
// finish definition
#endif
