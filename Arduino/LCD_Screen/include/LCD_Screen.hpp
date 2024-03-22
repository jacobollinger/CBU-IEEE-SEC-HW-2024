// Define your Library; makes sure name is not taken 
#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H

// Include libraries you will use 
#include <Arduino.h>
#include <LiquidCrystal.h> 
// #include "Defines.hpp"

class LCD_Screen {
    public:
        // define functions 
        LCD_Screen();
        void init();
        void teamPromo();   
    private: 
        LiquidCrystal promoLCD; // Update Pins 
};
// finish definition 
#endif


