#include "../include/LCDScreen.hpp"

// Initialize your object with the necessary pin numbers
LCDScreen::LCDScreen() : promoLCD(LCD_SCREEN_RS_PIN, LCD_SCREEN_E_PIN, LCD_SCREEN_D4_PIN, LCD_SCREEN_D5_PIN, LCD_SCREEN_D6_PIN, LCD_SCREEN_D7_PIN)
{
}

void LCDScreen::init()
{
    promoLCD.begin(16, 2);
}

void LCDScreen::teamPromo()
{
    promoLCD.print("GO BUCS!");
    delay(10);
    promoLCD.setCursor(0, 0);
    promoLCD.print("CBU IEEE");
    promoLCD.setCursor(0, 1);
    promoLCD.print("Robotics");
    // promoLCD.noDisplay();
}
