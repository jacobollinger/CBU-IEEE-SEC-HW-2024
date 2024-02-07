#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("GO BUCS!");
}

void loop() {
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.print("CBU IEEERobotics");
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.noDisplay();
}
