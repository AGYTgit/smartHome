// #include <Arduino.h>
// #include <SPI.h>
// #include <MFRC522.h>
// #include <Wire.h>

// #define RFID_RST_PIN 9
// #define RFID_SDA_PIN 10
// MFRC522 rfid(RFID_SDA_PIN, RFID_RST_PIN);
// // pins sck - 13, miso - 12, mosi - 11, sda - 10, rst - 9

// const unsigned long TARGET_UID = 3543600632;

// void setup() {
//   Serial.begin(115200);
//   SPI.begin();
//   rfid.PCD_Init();

//   Serial.println("Place RFID card/chip to scan");
//   delay(2000);
// }

// void loop() {
//   if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
//     return;
//   }

//   unsigned long readUID = 0;
//   Serial.print("UID tag (in hex):");
//   for (byte i = 0; i < rfid.uid.size; i++) {
//     Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(rfid.uid.uidByte[i], HEX);

//     readUID = (readUID << 8) | rfid.uid.uidByte[i];
//   }
//   Serial.println();

//   Serial.print("Combined UID (decimal): ");
//   Serial.println(readUID);

//   if (readUID == TARGET_UID) {
//     Serial.println("Welcome!");
//   } else {
//     Serial.println("Incorrect uid");
//   }

//   rfid.PICC_HaltA();
//   delay(1000);
// }
