// #include <Adafruit_Fingerprint.h>
// #include <SoftwareSerial.h>

// #define FINGERPRINT_RX_PIN 2
// #define FINGERPRINT_TX_PIN 3

// SoftwareSerial mySerial(FINGERPRINT_RX_PIN, FINGERPRINT_TX_PIN);
// Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// void setupFingerprint() {
//   finger.begin(57600);
//   delay(5);

//   if (!finger.verifyPassword()) {
//     Serial.println("Did not find fingerprint sensor :(");
//     while (1);
//   }

//   finger.getTemplateCount();
//   if (finger.templateCount == 0) {
//     Serial.println("No fingerprints enrolled. Please enroll some.");
//   } else {
//     Serial.print("Sensor contains ");
//     Serial.print(finger.templateCount);
//     Serial.println(" fingerprints");
//   }
// }

// void handleFingerprint() {
//   uint8_t p = finger.getImage();
//   if (p == FINGERPRINT_OK) {
//     p = finger.image2Tz();
//     if (p == FINGERPRINT_OK) {
//       p = finger.fingerFastSearch();
//       if (p == FINGERPRINT_OK) {
//         Serial.print("Confidence: ");
//         Serial.println(finger.confidence);
//         Serial.print("Fingerprint matched! ID: ");
//         Serial.println(finger.fingerID);
//       } else if (p == FINGERPRINT_NOTFOUND) {
//         Serial.println("Fingerprint found, but no match.");
//       }
//     }
//   } 
// }

// void setup() {
//   Serial.begin(9600);

//   setupFingerprint();
// }

// void loop() {
//   checkFingerprint(); // Check for a fingerprint, but don't block
// }