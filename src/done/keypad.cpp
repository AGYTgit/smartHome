// #include <Arduino.h>
// #include <Keypad.h>
// #include <Wire.h>

// const uint8_t ROWS = 4;
// const uint8_t COLS = 4;
// char keys[ROWS][COLS] = {
//   { '1', '2', '3', 'A' },
//   { '4', '5', '6', 'B' },
//   { '7', '8', '9', 'C' },
//   { '*', '0', '#', 'D' }
// };

// uint8_t colPins[COLS] = { 5, 4, 3, 2 };
// uint8_t rowPins[ROWS] = { 9, 8, 7, 6 };

// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   char key = keypad.getKey();

//   if (key != NO_KEY) {
//     Serial.println(key);
//   }
// }