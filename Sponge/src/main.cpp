#include <Arduino.h>
/*
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int enA = 9;
const int in1 = 8;
const int in2 = 7;

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP); // Button with internal pullup
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  if (digitalRead(buttonPin1) == LOW) { // If button pressed
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 255); // Set speed (0-255)
  } 
  else if (digitalRead(buttonPin2) == LOW) { // If second button pressed
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, 200); // Set speed (0-255)
  }
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}
*/
/*
#include <Stepper.h>

// Number of steps per revolution for your motor
const int stepsPerRevolution = 400; 
const int buttonPin1 = 4;
const int buttonPin2 = 17;

// Initialize stepper library on pins 8, 9, 10, 11
// L298N IN1=8, IN2=9, IN3=10, IN4=11
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  myStepper.setSpeed(60); // Speed in RPM
  pinMode(buttonPin1, INPUT_PULLUP); 
  Serial.begin(9600);
  //pinMode(buttonPin2, INPUT_PULLUP); 
}

void loop() {
  // Rotate forward
    Serial.println(digitalRead(4));

  
  if (digitalRead(buttonPin1) == LOW){

    myStepper.step(stepsPerRevolution);
   
  }
  // Rotate backward
  else if (digitalRead(buttonPin2) == HIGH){
      myStepper.step(-stepsPerRevolution);
  }
  else{
    myStepper.step(stepsPerRevolution); // Stop the motor
  }
}
*/


// void setup() {
//   pinMode(6, OUTPUT);
//   pinMode(5, OUTPUT);
// }

// void loop() {
//   digitalWrite(6, HIGH); 
//   digitalWrite(5, LOW);
// // ON
//   //delay(20000); // Wait for 20 seconds

// }

// #include <Stepper.h>

// // Number of steps per output revolution of your motor
// const int stepsPerRevolution = 200; 
// const int heaterPin = 6;

// // Initialize library on pins 8-11
// Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// void setup() {
//   myStepper.setSpeed(60); // Speed in RPM
//   pinMode(heaterPin, OUTPUT);
// }

// void loop() {
//   myStepper.step(stepsPerRevolution); // Rotate clockwise
//   digitalWrite(heaterPin, HIGH); 
//   delay(20000); // Wait for 20 seconds
//   myStepper.step(-stepsPerRevolution); // Rotate counterclockwise
//   digitalWrite(heaterPin, LOW);
//   delay(5000); 
// }
// #include <Stepper.h>
// int fanPin = 6; // Pin connected to Transistor Base
// const int stepsPerRev = 400;
// Stepper stepper(stepsPerRev, 8, 9, 10, 11);

// const int buttonPin1 = 3;

// void setup() {                
//   pinMode(fanPin, OUTPUT);
//   pinMode(buttonPin1, INPUT_PULLUP); 
//   stepper.setSpeed(60);
// }

// void loop() {
//   if (digitalRead(buttonPin1) == LOW) { // If button pressed
//     digitalWrite(fanPin,HIGH); // Full Speed
//     stepper.step(1);

//      // Run for 20 seconds
//   } 
//   else {
//     digitalWrite(fanPin, LOW); // Stop Fan
//     stepper.step(0); // Stop Stepper

//   }
// }
  

// #include <Stepper.h>

// const int stepsPerRev = 200;
// Stepper stepper(stepsPerRev, 8, 9, 10, 11); // example pins

// const int buttonPin = 4;
// bool motorOn = false;
// bool lastState = HIGH;

// void setup() {
//   pinMode(buttonPin, INPUT_PULLUP);
//   stepper.setSpeed(60);
// }

// void loop() {
//   bool currentState = digitalRead(buttonPin);

//   // toggle on press
//   if (lastState == HIGH && currentState == LOW) {
//     motorOn = !motorOn;
//     delay(200); // debounce
//   }

//   lastState = currentState;

//   // run motor ONLY if on
//   if (motorOn) {
//     stepper.step(1);  // 👈 KEY CHANGE (small step)
//   }
// }



// #include <Stepper.h>

// // Number of steps per revolution for your motor
// const int stepsPerRevolution = 400; 
// const int buttonPin1 = 4;
// const int buttonPin2 = 17;

// // Initialize stepper library on pins 8, 9, 10, 11
// // L298N IN1=8, IN2=9, IN3=10, IN4=11
// Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// void setup() {
//   myStepper.setSpeed(60); // Speed in RPM
//   pinMode(buttonPin1, INPUT_PULLUP); 
//   Serial.begin(9600);
//   //pinMode(buttonPin2, INPUT_PULLUP); 
// }

// void loop() {
//   // Rotate forward
//     Serial.println(digitalRead(4));

  
//   if (digitalRead(buttonPin1) == LOW){
//     Serial.println("Button 1 Pressed");
//     myStepper.step(-stepsPerRevolution);
   
//   }
//   // Rotate backward
//   else if (digitalRead(buttonPin1) == HIGH){
//     Serial.println("Button 1 Not Pressed");
//       myStepper.step(stepsPerRevolution);
//   }
//   else{
//     myStepper.step(stepsPerRevolution); // Stop the motor
//   }
// }
// */

#include <Stepper.h>

int fanPin = 6;
int heaterPin = 5;
const int stepsPerRev = 400;
Stepper stepper(stepsPerRev, 8, 9, 10, 11);

const int buttonPin1 = 3;

bool running = false;
unsigned long startTime = 0;
const unsigned long runDuration = 20000; // 20 seconds

void setup() {                
  pinMode(fanPin, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP); 
  pinMode(heaterPin, OUTPUT);
  stepper.setSpeed(200);
}

void loop() {

  // Detect button press (start only if not already running)
  if (digitalRead(buttonPin1) == LOW && !running) {
    running = true;
    startTime = millis();
  }

  if (running) {
    digitalWrite(fanPin, HIGH);
    digitalWrite(heaterPin, HIGH);

    // Keep motor moving continuously
    stepper.step(1);

    // Check if 20 seconds passed
    if (millis() - startTime >= runDuration) {
      running = false;
      digitalWrite(fanPin, LOW);
      digitalWrite(heaterPin, LOW);
    }
  }
}