#include <Arduino.h>
#include <Stepper.h>

const int fanPin = 6;
const int heaterPin = 5;
const int uvPin = 7;
const int stepsPerRev = 400;
Stepper stepper(stepsPerRev, 8, 9, 10, 11);

const int buttonPinShort = 3;
const int buttonPinLong = 4;

enum RunMode { NONE, SHORT, LONG };
RunMode currentMode = NONE;
unsigned long startTime = 0;
const unsigned long runDurationShort = 5000;
const unsigned long runDurationLong = 20000;

void setOutputs(RunMode mode) {
  if (mode == SHORT) {
    digitalWrite(fanPin, LOW);
    digitalWrite(heaterPin, LOW);
    digitalWrite(uvPin, HIGH);
  } else if (mode == LONG) {
    digitalWrite(fanPin, HIGH);
    digitalWrite(heaterPin, HIGH);
    digitalWrite(uvPin, HIGH);
  } else {
    digitalWrite(fanPin, LOW);
    digitalWrite(heaterPin, LOW);
    digitalWrite(uvPin, LOW);
  }
}

void setup() {
  pinMode(fanPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
  pinMode(uvPin, OUTPUT);
  pinMode(buttonPinShort, INPUT_PULLUP);
  pinMode(buttonPinLong, INPUT_PULLUP);
  stepper.setSpeed(200);
  setOutputs(NONE);
}

void loop() {
  bool shortPressed = digitalRead(buttonPinShort) == LOW;
  bool longPressed = digitalRead(buttonPinLong) == LOW;

  if (currentMode == NONE) {
    if (shortPressed) {
      currentMode = SHORT;
      startTime = millis();
      setOutputs(SHORT);
    } else if (longPressed) {
      currentMode = LONG;
      startTime = millis();
      setOutputs(LONG);
    }
  }

  if (currentMode != NONE) {
    stepper.step(1);
    unsigned long elapsed = millis() - startTime;

    if ((currentMode == SHORT && elapsed >= runDurationShort) ||
        (currentMode == LONG && elapsed >= runDurationLong)) {
      currentMode = NONE;
      setOutputs(NONE);
    }
  }
}
