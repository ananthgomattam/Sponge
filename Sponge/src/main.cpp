#include <Arduino.h>

// ===== Pins =====
const int motorPin = 3;
const int motorDirPin = 4;
const int heaterPin = 5;
const int uvPin = 6;
const int fanPin = 9;

const int quickButtonPin = 7;
const int deepButtonPin = 8;
const int lidSwitchPin = 10;

const int tempSensorPin = A0;

// ===== Config =====
float targetTemp = 60.0;
float maxTemp = 80.0;

// ===== State Machine =====
enum SystemState {
    IDLE,
    QUICK_RUN,
    HEATING,
    PROCESSING,
    COOLDOWN
};

SystemState currentState = IDLE;

// ===== Timing =====
unsigned long stateStartTime = 0;
unsigned long processDuration = 15000;
unsigned long cooldownDuration = 10000;

// ===== Helpers =====
float readTemperature() {
    int raw = analogRead(tempSensorPin);
    float voltage = raw * (5.0 / 1023.0);
    return voltage * 100; // adjust per your sensor
}

void setMotor(int speed) {
    analogWrite(motorPin, speed);
    digitalWrite(motorDirPin, HIGH);
}

void setHeater(bool on) {
    analogWrite(heaterPin, on ? 255 : 0);
}

void setUV(bool on) {
    digitalWrite(uvPin, on ? HIGH : LOW);
}

void setFan(bool on) {
    digitalWrite(fanPin, on ? HIGH : LOW);
}

bool lidOpen() {
    return digitalRead(lidSwitchPin) == HIGH;
}

// ===== Setup =====
void setup() {
    pinMode(motorPin, OUTPUT);
    pinMode(motorDirPin, OUTPUT);
    pinMode(heaterPin, OUTPUT);
    pinMode(uvPin, OUTPUT);
    pinMode(fanPin, OUTPUT);

    pinMode(quickButtonPin, INPUT_PULLUP);
    pinMode(deepButtonPin, INPUT_PULLUP);
    pinMode(lidSwitchPin, INPUT_PULLUP);

    Serial.begin(9600);
}

// ===== Loop =====
void loop() {
    float temp = readTemperature();

    // GLOBAL SAFETY
    if (temp > maxTemp || lidOpen()) {
        setHeater(false);
        setUV(false);
        currentState = COOLDOWN;
        stateStartTime = millis();
    }

    switch (currentState) {

        case IDLE:
            setMotor(0);
            setHeater(false);
            setUV(false);
            setFan(false);

            if (digitalRead(quickButtonPin) == LOW) {
                currentState = QUICK_RUN;
            }

            if (digitalRead(deepButtonPin) == LOW) {
                currentState = HEATING;
                stateStartTime = millis();
            }
            break;

        case QUICK_RUN:
            setMotor(200);
            setFan(false);
            setHeater(false);
            setUV(false);

            if (digitalRead(quickButtonPin) == HIGH) {
                currentState = IDLE;
            }
            break;

        case HEATING:
            setFan(true);
            setMotor(0);

            if (temp < targetTemp) {
                setHeater(true);
            } else {
                setHeater(false);
                currentState = PROCESSING;
                stateStartTime = millis();
            }
            break;

        case PROCESSING:
            setMotor(200);
            setFan(true);

            if (temp < targetTemp) {
                setHeater(true);
            } else {
                setHeater(false);
            }

            if (!lidOpen()) {
                setUV(true);
            } else {
                setUV(false);
            }

            if (millis() - stateStartTime > processDuration) {
                currentState = COOLDOWN;
                stateStartTime = millis();
            }
            break;

        case COOLDOWN:
            setMotor(0);
            setHeater(false);
            setUV(false);
            setFan(true);

            if (millis() - stateStartTime > cooldownDuration) {
                currentState = IDLE;
            }
            break;
    }

    Serial.print("State: ");
    Serial.print(currentState);
    Serial.print(" Temp: ");
    Serial.println(temp);

    delay(50);
}