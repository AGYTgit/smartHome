// #include <Arduino.h>
// #include <Wire.h>

// #define magnetPin 7
// bool magnetState = false;

// void setup() {
//     Serial.begin(115200);

//     pinMode(magnetPin, INPUT_PULLUP);
// }

// void loop() {
//     if (digitalRead(magnetPin) != LOW && !magnetState) {
//         Serial.println("Magnet detected");
//         magnetState = true;
//         delay(10);
//     } else if (digitalRead(magnetPin) == LOW && magnetState) {
//         Serial.println("Magnet removed");
//         magnetState = false;
//         delay(100);
//     }
// }