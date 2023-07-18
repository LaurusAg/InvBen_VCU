#include <Arduino.h>
#include "HAL.h"

void halSetup()
{
    pinMode(BACKUPVENT_PIN,OUTPUT);
    pinMode(VALVE_PIN,OUTPUT);
    pinMode(SENSOR_PIN,INPUT);
    pinMode(PRESURIZATION_PIN,OUTPUT);
}

void turnON(uint8_t pin)
{
    digitalWrite(pin, HIGH);
}

void turnOFF(uint8_t pin)
{
    digitalWrite(pin, LOW);
}
