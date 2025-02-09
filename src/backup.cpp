// #include <Wire.h>              // I2C komunikácia
// #include <LiquidCrystal_I2C.h> // LCD
// #include <Keypad.h>            // Keypad
// #include <AccelStepper.h>      // Krokový motor
// #include <SPI.h>               // SPI pre RFID
// #include <MFRC522.h>           // RFID knižnica
// #include <Servo.h>             // Servo


// LiquidCrystal_I2C lcd(0x27, 20, 4);

// //krokovy
// #define motorPin1 8
// #define motorPin2 9
// #define motorPin3 10
// #define motorPin4 11
// AccelStepper motor(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

// //RFID
// #define RST_PIN 13
// #define SDA_PIN 53
// MFRC522 rfid(SDA_PIN, RST_PIN);


// Servo alarmServo;
// #define SERVO_PIN 12
// #define BUZZER_PIN 5


// #define PIR_PIN 22
// #define GAS_SENSOR_PIN A0


// #define REMOTE_CH1 47
// #define REMOTE_CH2 48


// const byte ROWS = 4;
// const byte COLS = 4;

// char keys[ROWS][COLS] = {
//   {'1', '2', '3', 'A'},
//   {'4', '5', '6', 'B'},
//   {'7', '8', '9', 'C'},
//   {'*', '0', '#', 'D'}
// };

// byte rowPins[ROWS] = {24, 25, 26, 27};
// byte colPins[COLS] = {28, 29, 30, 31};

// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


// bool alarmActive = false;   // Alarm zapnutý/vypnutý
// bool gateOpen    = false;   // Brána otvorená/zatvorená

// bool pirLatched  = false;
// bool gasLatched  = false;

// const byte knownUIDs[][4] = {
//   {0xDE, 0xAD, 0xBE, 0xEF},
//   {0x11, 0x22, 0x33, 0x44} 
// };

// const byte knownUIDCount = sizeof(knownUIDs) / sizeof(knownUIDs[2]);

// void toggleGate() {
//   if (gateOpen) {
//     motor.moveTo(200);
//     gateOpen = false;
//   } else {
//     motor.moveTo(0);
//     gateOpen = true;
//   }
//   motor.runToPosition();
// }



// bool checkRFID() {
//   for (byte i = 0; i < knownUIDCount; i++) {
//     bool match = true;
//     for (byte j = 0; j < 4; j++) {
//       if (rfid.uid.uidByte[j] != knownUIDs[i][j]) {
//         match = false;
//         break;
//       }
//     }
//     if (match) {
//       return true;
//     }
//   }
//   return false;
// }


// void buzzError() {
//   for (int i = 0; i < 3; i++) {
//     digitalWrite(BUZZER_PIN, HIGH);
//     delay(500);
//     digitalWrite(BUZZER_PIN, LOW);
//     delay(150);
//   }
// }

// void setup() {
//   Serial.begin(9600);

  

//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("System starting...");

  
//   motor.setMaxSpeed(10000);
//   motor.setAcceleration(50);

  
//   alarmServo.attach(SERVO_PIN);
//   alarmServo.write(0); 

  
//   pinMode(PIR_PIN, INPUT);
//   pinMode(GAS_SENSOR_PIN, INPUT);


//   pinMode(REMOTE_CH1, INPUT);
//   pinMode(REMOTE_CH2, INPUT);

//   pinMode(BUZZER_PIN, OUTPUT);
//   digitalWrite(BUZZER_PIN, LOW);


//   SPI.begin();
//   rfid.PCD_Init();

//   delay(2000);
//   lcd.clear();
// }



// void loop() {

//   bool motionDetected = digitalRead(PIR_PIN);   // PIR
//   int  gasValue       = analogRead(GAS_SENSOR_PIN);

//   bool remoteCh1 = digitalRead(REMOTE_CH1);
//   bool remoteCh2 = digitalRead(REMOTE_CH2);

  
//   lcd.setCursor(0, 0);
//   lcd.print("Alarm: ");
//   lcd.print(alarmActive ? "ZAPNUTY  " : "VYPNUTY  ");

//   lcd.setCursor(0, 1);
//   lcd.print("Gate:  ");
//   lcd.print(gateOpen ? "OTVORENA  " : "ZATVORENA ");


//   if (alarmActive) {

//     if (motionDetected && !pirLatched) {
//       pirLatched = true;

//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("POHYB DETEKOVANY!");
     
//       buzzError();
//       alarmServo.write(90);
//       delay(2000);

     
//       alarmServo.write(0);
//       lcd.clear();
//     }
    
//     else if (!motionDetected) {
//       pirLatched = false;
//     }
//   }

 
//   if (alarmActive) {
    
//     if (gasValue > 400 && !gasLatched) {
//       gasLatched = true;

//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("PLYN DETEKOVANY!");
//       buzzError();
//       alarmServo.write(90);
//       delay(2000);

      
//       alarmServo.write(0);
//       lcd.clear();
//     }
  
//     else if (gasValue <= 400) {
//       gasLatched = false;
//     }
//   }

  
//   if (remoteCh1) {
//     toggleGate();
//   }
//   if (remoteCh2) {
//     alarmActive = !alarmActive;
    
//     if (!alarmActive) {
//       alarmServo.write(0);
//     }
//     delay(500); 
//   }

  
//   char key = keypad.getKey();
//   if (key) {
//     if (key == 'A') {
//       toggleGate();
//     }
//     if (key == 'B') {
//       alarmActive = !alarmActive;
//       if (!alarmActive) {
//         alarmServo.write(0);
//       }
//     }
//   }

  
//   if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
//     if (checkRFID()) {
//       alarmActive = false;
//       alarmServo.write(0);

//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("RFID: Odomknute");
//       delay(2000);
//     } else {
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("RFID: Neplatne");
//       buzzError();
//       delay(2000);
//     }
//     rfid.PICC_HaltA();
//   }
// }