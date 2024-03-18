#include "./include/LCD_Screen.hpp"

LCD_Screen lcd_screen = LCD_Screen();


void setup() {
lcd_screen.init();

// The following is your old code 
/*
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("GO BUCS!");
*/
}

void loop() {
lcd_screen.teamPromo();

// The following is your old code 
/*
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.print("CBU IEEERobotics");
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.noDisplay();
*/
}
