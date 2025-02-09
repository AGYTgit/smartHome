// #include <Arduino.h>
// #include <Wire.h>


// #define REMOTE_CH1 6
// #define REMOTE_CH2 4
// #define REMOTE_CH3 7
// #define REMOTE_CH4 5

// void setup() {
//   Serial.begin(115200);

//   pinMode(REMOTE_CH1, INPUT);
//   pinMode(REMOTE_CH2, INPUT);
//   pinMode(REMOTE_CH3, INPUT);
//   pinMode(REMOTE_CH4, INPUT);
// }

// void loop() {
//   bool remoteCh1 = digitalRead(REMOTE_CH1);
//   bool remoteCh2 = digitalRead(REMOTE_CH2);
//   bool remoteCh3 = digitalRead(REMOTE_CH3);
//   bool remoteCh4 = digitalRead(REMOTE_CH4);

//   if (remoteCh1) {
//     Serial.println("A");
//     delay(100);
//   }
//   if (remoteCh2) {
//     Serial.println("B");
//     delay(100);
//   }
//   if (remoteCh3) {
//     Serial.println("C");
//     delay(100);
//   }
//   if (remoteCh4) {
//     Serial.println("D");
//     delay(100);
//   }
// }