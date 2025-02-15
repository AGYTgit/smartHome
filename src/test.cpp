// #include <Arduino.h>
// #include <Adafruit_Fingerprint.h>
// #include <SoftwareSerial.h>
// #include <Wire.h>

// SoftwareSerial mySerial(2, 3);  // RX, TX for SoftwareSerial

// Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// void setup() {
//   Serial.begin(115200);
//   finger.begin(57600);

//   if (finger.verifyPassword()) {
//     Serial.println("Fingerprint sensor found!");
//   } else {
//     Serial.println("Fingerprint sensor not found");
//     while (true);  // Stop execution if sensor is not found
//   }

//   Serial.println("Waiting for fingerprint...");
// }

// void loop() {
//   if (finger.getImage() == FINGERPRINT_OK) {
//     if (finger.image2Tz() == FINGERPRINT_OK && finger.fingerSearch() == FINGERPRINT_OK) {
//       Serial.println("Fingerprint recognized!");
//     } else {
//       Serial.println("Fingerprint not recognized.");
//     }
//   }
//   delay(1000);  // Wait for 1 second before trying again
// }
