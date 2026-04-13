#include <Arduino.h>

int motor1pin1 = 2;
int motor1pin2 = 3;

int enablePin = 9; // ENA

void setup() {
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
}

void loop() {

  // Set speed
  analogWrite(enablePin, 150); // 0–255

  // Forward
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  delay(3000);

  // Stop
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  delay(3000);
}