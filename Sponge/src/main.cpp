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

#include <Stepper.h>

// Number of steps per revolution for your motor
const int stepsPerRevolution = 400; 
const int buttonPin1 = 16;
const int buttonPin2 = 17;

// Initialize stepper library on pins 8, 9, 10, 11
// L298N IN1=8, IN2=9, IN3=10, IN4=11
Stepper myStepper(stepsPerRevolution, 12, 13, 14, 15);

void setup() {
  myStepper.setSpeed(60); // Speed in RPM
  pinMode(buttonPin1, INPUT_PULLUP); 
  pinMode(buttonPin2, INPUT_PULLUP); 
}

void loop() {
  // Rotate forward
  if (digitalRead(buttonPin1) == LOW){
    myStepper.step(stepsPerRevolution);
   
  }
  // Rotate backward
  else if (digitalRead(buttonPin2) == LOW){
      myStepper.step(-stepsPerRevolution);
     
  }
  else{
    myStepper.step(0); // Stop the motor
  }
}

/*
void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  digitalWrite(9, HIGH); // ON
  delay(20000); // Wait for 20 seconds

}
*/
