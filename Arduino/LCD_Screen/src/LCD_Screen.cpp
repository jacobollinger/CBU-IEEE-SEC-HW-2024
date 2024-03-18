#include <Arduino.h>
#include "../include/LCD_Screen.hpp"

// Initialize your object with the necessary pin numbers
LCD_Screen::LCD_Screen() : promoLCD(12, 11, 5, 4, 3, 2) {
}

void LCD_Screen::init() {
    promoLCD.begin(16, 2);
}

void LCD_Screen::teamPromo() {
    promoLCD.print("GO BUCS!");
    delay(2000);
    promoLCD.clear();
    promoLCD.setCursor(0, 0);
    promoLCD.print("CBU IEEERobotics");
    delay(2000);
    promoLCD.noDisplay();
}
