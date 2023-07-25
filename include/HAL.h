#ifndef HAL_H
#define HAL_H

#include <Arduino.h>


#define BACKUPVENT_PIN D1
#define OPEN_VALVE_PIN D2
#define CLOSE_VALVE_PIN D4
#define SENSOR_PIN A0
#define PRESURIZATION_PIN D3

void halSetup();
void turnON(uint8_t pin);
void turnOFF(uint8_t pin);
void halINIT();
void turnOnRelay(uint8_t pin);
void turnOffRelay(uint8_t pin);
void openValve();
void closeValve();

#endif