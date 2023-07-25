#include <Arduino.h>
#include "HAL.h"

void halSetup()
{
    pinMode(BACKUPVENT_PIN,OUTPUT);
    pinMode(OPEN_VALVE_PIN,OUTPUT);
    pinMode(SENSOR_PIN,INPUT);
    pinMode(PRESURIZATION_PIN,OUTPUT);
    pinMode(CLOSE_VALVE_PIN, OUTPUT);
}

void turnON(uint8_t pin)
{
    digitalWrite(pin, HIGH);
}

void turnOFF(uint8_t pin)
{
    digitalWrite(pin, LOW);
}

void turnOnRelay(uint8_t pin)
{
    digitalWrite(pin, LOW);
}

void turnOffRelay(uint8_t pin)
{
    digitalWrite(pin, HIGH);
}
void openValve()
{
    digitalWrite(OPEN_VALVE_PIN, LOW);
    delay(10);
    digitalWrite(CLOSE_VALVE_PIN,HIGH);
}

void closeValve()
{
    digitalWrite(CLOSE_VALVE_PIN, LOW);
    delay(10);
    digitalWrite(OPEN_VALVE_PIN, HIGH);
}


void halINIT()
{
    turnOffRelay(BACKUPVENT_PIN);
    turnOffRelay(OPEN_VALVE_PIN);
    turnOnRelay(CLOSE_VALVE_PIN);
    turnOffRelay(PRESURIZATION_PIN);
}