#include <Arduino.h>
#include <Stepper.h>

const int fanPin = 6;
const int heaterPin = 5;
const int uvPin = 7;
const int stepsPerRev = 400;
Stepper stepper(stepsPerRev, 8, 9, 10, 11);

const int buttonPinShort = 3;
const int buttonPinLong = 4;

void setup() {
  stepper.setSpeed(60);
  //stepper.step(0);
  pinMode(fanPin, OUTPUT);
  // pinMode(heaterPin, OUTPUT);
  pinMode(buttonPinShort, INPUT_PULLUP);
  pinMode(buttonPinLong, INPUT_PULLUP);
  // pinMode(uvPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //stepper.step(stepsPerRev);
  //Serial.print("Button Fan: ");
  Serial.println(digitalRead(buttonPinLong));
  if (digitalRead(buttonPinLong)== LOW)
{
  stepper.step(stepsPerRev);

} else {
  stepper.step(0);
}  //Serial.print("Button Motor: ");
  //Serial.println(digitalRead(buttonPinLong));
  // if (digitalRead(buttonPinLong) == LOW) {
  //   digitalWrite(fanPin, HIGH);
  //   stepper.step(0);
  // } else if (digitalRead(buttonPinLong) == HIGH && digitalRead(buttonPinShort) == HIGH) {
  //   digitalWrite(fanPin, LOW);
  //   stepper.step(0);
  // }
  // else if (digitalRead(buttonPinShort) == LOW){
  //   digitalWrite(fanPin, LOW);
  //   stepper.step(stepsPerRev);
  // }
  // else {
  //   digitalWrite(fanPin, LOW);
  //   stepper.step(0);
  //}
  
}