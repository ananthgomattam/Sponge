#include <Arduino.h>
#include <Stepper.h>

const int fanPin = 6;
const int heaterPin = 5;

void setup() {
  pinMode(fanPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
}

void loop() {
  digitalWrite(fanPin, HIGH); // Turn on the fan
  digitalWrite(heaterPin, HIGH); // Turn on the heater
}