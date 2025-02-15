// #include <Arduino.h>
// #include <SPI.h>
// #include <MFRC522.h>
// #include <Wire.h>

// #define RFID_RST_PIN 9
// #define RFID_SDA_PIN 10

// MFRC522 rfid(RFID_SDA_PIN, RFID_RST_PIN);
// // pins miso - 50, mosi - 51, sck - 52, sda - 53

// const unsigned long TARGET_UID = 3543600632;

// bool compareUID(byte* uid1, byte* uid2, byte len) {
//     for (byte i = 0; i < len; i++) {
//         if (uid1[i] != uid2[i]) {
//             return false;
//         }
//     }
//     return true;
// }

// void setup() {
//     Serial.begin(115200);
//     SPI.begin();
//     rfid.PCD_Init();

//     Serial.println("Place RFID card/chip to scan");
//     delay(2000);
// }

// void loop() {
//     if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
//         return;
//     }

//     Serial.print("UID tag (in hex):");
//     for (byte i = 0; i < rfid.uid.size; i++) {
//         Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
//         Serial.print(rfid.uid.uidByte[i], HEX);
//     }
//     Serial.println();

//     if (rfid.uid.size == 4 && compareUID(rfid.uid.uidByte, (byte*)&TARGET_UID, rfid.uid.size)) {
//         Serial.println("Welcome!");
//     } else {
//         Serial.println("Incorrect UID or card read error.");
//     }

//     rfid.PICC_HaltA();
//     delay(1000);
// }