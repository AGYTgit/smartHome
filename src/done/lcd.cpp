// #include <Arduino.h>
// #include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27, 20, 2);
// // pins 4, 5 for Arduino Uno/Nano
// // pins 21, 22 for Arduino Mega

// void setup() {
//   Serial.begin(115200);

//   Serial.println("Start");

//   lcd.init();
//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("System starting...");

//   lcd.clear();
// }

// void loop() {
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Hello World! ");
//   lcd.println(millis());
//   Serial.println(millis());
//   delay(100);
// }