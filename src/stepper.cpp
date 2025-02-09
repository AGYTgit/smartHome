// #include <Arduino.h>
// #include <Stepper.h>
// #include <Wire.h>

// // !! not working (probably bad motor)

// #define n1 8
// #define n2 10
// #define n3 9
// #define n4 11

// const int stepsPerRevolution = 2048;
// Stepper myStepper(stepsPerRevolution, n1, n2, n3, n4);

// void setup() {
//   Serial.begin(115200);

//   Serial.println("Start");

//   myStepper.setSpeed(5);
// }

// void loop() {
//     Serial.println("Clockwise");
//     myStepper.step(stepsPerRevolution);
//     delay(1000);
  
//     Serial.println("Counterclockwise");
//     myStepper.step(-stepsPerRevolution);
//     delay(1000);
// }