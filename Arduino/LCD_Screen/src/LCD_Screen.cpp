#include <Arduino.h>
#include "../include/LCD_Screen.hpp"

// Initialize your object with the necessary pin numbers
LCD_Screen::LCD_Screen() : promoLCD(42, 43, 44, 45, 46, 47) {
}

void LCD_Screen::init() {
    promoLCD.begin(16, 2);
}

void LCD_Screen::teamPromo() {
    promoLCD.print("GO BUCS!");
    delay(2000);
    promoLCD.clear();
    promoLCD.setCursor(0, 0);
    promoLCD.print("CBU IEEERobotic");
    delay(2000);
    promoLCD.noDisplay();
}
