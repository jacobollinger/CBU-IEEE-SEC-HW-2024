#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("CBU Bucs!");
}

void loop() {
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("GO BUCS");
  delay(2000);
}
