#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>

// vars
bool alarmActive = false;
bool alarmTriggered = false;
char password[20] = "";
String input = "";

// lcd
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
// sda - 20, scl - 21

// keypad
#include <Keypad.h>
const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
uint8_t rowPins[ROWS] = { 31, 33, 35, 37 };
uint8_t colPins[COLS] = { 39, 41, 43, 45 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// rfid
#include <SPI.h>
#include <MFRC522.h>
#define RFID_RST_PIN 9
#define RFID_SDA_PIN 53
// mosi - 50, miso - 51, sck - 52
MFRC522 rfid(RFID_SDA_PIN, RFID_RST_PIN);
const unsigned long TARGET_UID = 3543600632;

// fingerprint sensor
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#define FINGERPRINT_SERIAL Serial1
// rx - 19, tx - 18 for Serial1
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

// remote
#define REMOTE_PIN_A 6
#define REMOTE_PIN_B 4
#define REMOTE_PIN_C 7
#define REMOTE_PIN_D 5

// sensors
// magnet
#define magnetPin 8
bool magnetState = false;
unsigned long magnetTimer = 0;
const unsigned long magnetDelay = 5000;

// smoke sensor
#define smokePin A1
bool smokeState = false;
int smokeThreshold = 50;
unsigned long smokeTimer = 0;
const unsigned long smokeDelay = 5000;

// water sensor
#define waterPin A2
bool waterState = false;
int waterThreshold = 75;
unsigned long waterTimer = 0;
const unsigned long waterDelay = 5000;

// motion sensor
#define motionPin 11
bool motionState = false;
unsigned long motionTimer = 0;
const unsigned long motionDelay = 5000;


// buzzer
#define buzzerPin 10
bool buzzerState = false;

// servo
#include <Servo.h>
#define servoPin 12
Servo servo;


// helper functions
void alarmOn() {
  alarmActive = true;
  lcd.setCursor(0, 0);
  lcd.print("         ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("Locked!");
}

void alarmOff() {
  alarmActive = false;
  lcd.setCursor(0, 0);
  lcd.print("       ");
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("Unlocked!");
}

void buzzerOn() {
  buzzerState = true;
  tone(buzzerPin, 1000);
}

void buzzerOff() {
  buzzerState = false;
  noTone(buzzerPin);
}

void servoForward() {
  servo.write(45);
}

void servoBackward() {
  servo.write(135);
}

void servoStop() {
  servo.write(90);
}

void triggerAlarm() {
  alarmTriggered = true;
  buzzerOn();
  lcd.clear();
  lcd.print("ALARM  TRIGGERED");
  lcd.setCursor(0, 1);
  lcd.print("!!!!!!!!!!!!!!!!");
}

void keymapToResetAlarm() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key == '#') {
      EEPROM.get(0, password);
      input = "";
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      while (true) {
        key = keypad.getKey();
        if (key == '*') {
          break;
        }
        if (key == 'A' || key == 'B' || key == 'C' || key == 'D' || key == '#') {
          continue;
        }
        if (key != NO_KEY) {
          input += key;
          lcd.print('*');
        }
      }
      if (input.equals(password)) {
        lcd.clear();
        lcd.print("Deactivated!");
        motionState = false;
        alarmTriggered = false;
        buzzerOff();
        delay(1000);
        lcd.clear();
        alarmOff();
      } else {
        lcd.clear();
        lcd.print("Wrong password!");
        delay(1000);
        lcd.clear();
        lcd.print("ALARM  TRIGGERED");
        lcd.setCursor(0, 1);
        lcd.print("!!!!!!!!!!!!!!!!");
      }
    }
  }
}


// setup functions
void setupLCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void setupKeymap() {
  pinMode(31, INPUT);
  pinMode(33, INPUT);
  pinMode(35, INPUT);
  pinMode(37, INPUT);
  pinMode(39, INPUT);
  pinMode(41, INPUT);
  pinMode(43, INPUT);
  pinMode(45, INPUT);
}

void setupRemote() {
  pinMode(REMOTE_PIN_A, INPUT);
  pinMode(REMOTE_PIN_B, INPUT);
  pinMode(REMOTE_PIN_C, INPUT);
  pinMode(REMOTE_PIN_D, INPUT);
}

void setupRFID() {
  SPI.begin();
  // SPI.setClockDivider(SPI_CLOCK_DIV4);
  rfid.PCD_Init();
}

void setupFingerprint() {
  finger.begin(57600);
  delay(5);

  if (!finger.verifyPassword()) {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }

  finger.getTemplateCount();
  if (finger.templateCount == 0) {
    Serial.println("No fingerprints enrolled. Please enroll some.");
  } else {
    Serial.print("Sensor contains ");
    Serial.print(finger.templateCount);
    Serial.println(" fingerprints");
  }
}

void setupBuzzer() {
  pinMode(buzzerPin, OUTPUT);
}

void setupMagnet() {
  pinMode(magnetPin, INPUT_PULLUP);
}

void setupSmokeSensor() {
  pinMode(smokePin, INPUT);
}

void setupWaterSensor() {
  pinMode(waterPin, INPUT);
}

void setupMotionSensor() {
  pinMode(motionPin, INPUT);
}

void setupServo() {
  servo.attach(12);
}


// check functions
bool checkMagnet() {
  return digitalRead(magnetPin) != LOW;
}

bool checkSmokeSensor() {
  int value = analogRead(smokePin);
  // Serial.println(value);
  return value < smokeThreshold;
}

bool checkAverageSmokeSensor() {
  int total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(smokePin);
  }
  // Serial.println(total / 10);
  return (total / 10) < smokeThreshold;
}

bool checkWaterSensor() {
  int value = analogRead(waterPin);
  // Serial.println(value);
  return value > waterThreshold;
}

bool checkMotionSensor() {
  return digitalRead(motionPin) != LOW;
}


// handle functions
void handleKeymap() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key == '#') { // unlocking
      EEPROM.get(0, password);
      if (alarmActive) {
        lcd.clear();
        lcd.print("enter password:");
        lcd.setCursor(0, 1);
        input = "";
        while (true) {
          key = keypad.getKey();
          if (key == '*') {
            break;
          }
          if (key == 'A' || key == 'B' || key == 'C' || key == 'D' || key == '#') {
            continue;
          }
          if (key != NO_KEY) {
            input += key;
            lcd.print('*');
          }
        }
        if (input.equals(password)) {
          lcd.clear();
          lcd.print("Welcome!");
          delay(1000);
          alarmOff();
        } else {
          lcd.clear();
          lcd.print("Wrong password!");
          delay(1000);
          lcd.clear();
          lcd.print("Locked!");
        }
      } else if (!alarmActive) {
        alarmOn();
      }
    } else if (key == 'D') {
      if (!alarmActive) { // locking
        while (true) {
          lcd.clear();
          lcd.print("Set password:");
          lcd.setCursor(0, 1);
          input = "";
          while (true) {
            key = keypad.getKey();
            if (key == '*') {
              break;
            }
            if (key != NO_KEY) {
              input += key;
              lcd.print('*');
            }
          }
          strncpy(password, input.c_str(), sizeof(password));
          lcd.clear();
          lcd.print("Confirm pass:");
          lcd.setCursor(0, 1);
          input = "";
          while (true) {
            key = keypad.getKey();
            if (key == '*') {
              break;
            }
            if (key != NO_KEY) {
              input += key;
              lcd.print('*');
            }
          }
          if (input.equals(password)) {
            lcd.clear();
            break;
          } else {
            lcd.clear();
            lcd.print("Wrong password!");
            delay(500);
          }
        }
        password[sizeof(password) - 1] = '\0';
        EEPROM.put(0, password);
        alarmOn();
      }
    }
  }
}

void handleRemote() {
  if (digitalRead(REMOTE_PIN_A) != LOW && !alarmActive) {
    alarmOn();
    while (digitalRead(REMOTE_PIN_A) != LOW);
  } else if (digitalRead(REMOTE_PIN_B) != LOW && alarmActive) {
    alarmOff();
    while (digitalRead(REMOTE_PIN_B) != LOW);
  }

  int total[2] = {0,0};

  for (int i = 0; i < 1000; i++) {
    if (digitalRead(REMOTE_PIN_C) != LOW) {
      total[0]++;
    } else if (digitalRead(REMOTE_PIN_D) != LOW) {
      total[1]++;
    }
    delayMicroseconds(200);
  }

  if (total[0] < 5 && total[1] < 5) {
    servoStop();
    return;
  }

  if (total[0] >= 5) {
    servoBackward();
  } else if (total[1] >= 5) {
    servoForward();
  }
}

void handleRFID() {
  Serial.println('1');
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }
  
  Serial.println('2');

  Serial.println("RFID detected");
  unsigned long readUID = 0;
  Serial.print("UID tag (in hex):");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);

    readUID = (readUID << 8) | rfid.uid.uidByte[i];
  }
  Serial.println();

  Serial.print("Combined UID (decimal): ");
  Serial.println(readUID);

  if (readUID == TARGET_UID) {
    Serial.println("Welcome!");
  } else {
    Serial.println("Incorrect uid");
  }

  rfid.PICC_HaltA();
}

void handleFingerprint() {
  uint8_t p = finger.getImage();
  if (p == FINGERPRINT_OK) {
    p = finger.image2Tz();
    if (p == FINGERPRINT_OK) {
      p = finger.fingerFastSearch();
      if (p == FINGERPRINT_OK) {
        // Serial.print("Confidence: ");
        // Serial.println(finger.confidence);
        // Serial.print("Fingerprint matched! ID: ");
        // Serial.println(finger.fingerID);
        alarmOff();
      } else if (p == FINGERPRINT_NOTFOUND) {
        // Serial.println("Fingerprint found, but no match.");
      }
    }
  } 
}

void handleMagnet() {
  bool currMagnetState = checkMagnet();

  if (currMagnetState && !magnetState) {
    magnetState = true;
    magnetTimer = millis();
    lcd.setCursor(12, 0);
    lcd.print('m');
  } else if (magnetState && (millis() - magnetTimer) > magnetDelay) {
    magnetState = false;
    lcd.setCursor(12, 0);
    lcd.print(' ');
  }
}

void handleSmoke() {
  bool currSmokeState = checkAverageSmokeSensor();

  if (currSmokeState && !smokeState) {
    smokeState = true;
    smokeTimer = millis();
    lcd.setCursor(13, 0);
    lcd.print('S');
  } else if (smokeState && (millis() - smokeTimer) > smokeDelay) {
    smokeState = false;
    lcd.setCursor(13, 0);
    lcd.print(' ');
  }
}

void handleWater() {
  bool currWaterState = checkWaterSensor();

  if (currWaterState && !waterState) {
    waterState = true;
    waterTimer = millis();
    lcd.setCursor(14, 0);
    lcd.print('W');
  } else if (waterState && (millis() - waterTimer) > waterDelay) {
    waterState = false;
    lcd.setCursor(14, 0);
    lcd.print(' ');
  }
}

void handleMotion() {
  bool currMotionState = checkMotionSensor();

  if (currMotionState && !motionState) {
    motionState = true;
    motionTimer = millis();
    lcd.setCursor(15, 0);
    lcd.print('M');
    if (alarmActive) {
      triggerAlarm();
    }
  } else if (motionState && (millis() - motionTimer) > motionDelay) {
    motionState = false;
    lcd.setCursor(15, 0);
    lcd.print(' ');
  }
}


void setup() {
  Serial.begin(115200);
  Serial.println("Hello, world!");

  // UI
  setupLCD();
  setupKeymap();
  setupRemote();
  // setupRFID();
  setupFingerprint();

  // sensors
  setupMagnet();
  setupSmokeSensor();
  setupWaterSensor();
  setupMotionSensor();

  setupBuzzer();
  setupServo();

  // setup
  EEPROM.get(0, password);
  alarmOn();
}

void loop() {
  if (alarmTriggered) {
    keymapToResetAlarm();
    return;
  }

  handleKeymap();
  handleRemote();
  if (alarmActive) {
    // handleRFID();
    handleFingerprint();
  }
  
  handleMagnet();
  handleSmoke();
  handleWater();
  handleMotion();
}

// keypad - alarm on/off sensors
// alarm on pin or rfid or fingerprint
// alarm triggered - led, buzzer, lcd