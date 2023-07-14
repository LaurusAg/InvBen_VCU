#include <Arduino.h>
#include "sensor.h"

    extern uint16_t on_pressure = 200;
    extern uint16_t off_pressure = 700;
    extern bool vent_state = false;
    extern float p;

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return ( ((x - in_min) *  (out_max - out_min)) / ((in_max - in_min) + out_min ) ) ; 
}

float pressureControl()
{

    //Variables declaration: 
    float min_tension = 0.2 ;
    float max_tension = 5.0 ;
    float min_pressure = 0.0 ;
    float max_pressure = 3500.0;
    float adc_value = 1023.0;
    float v;
    uint16_t sensor;

    sensor = analogRead(A0);
    v =((sensor * max_tension)/adc_value);
    p = mapfloat(v,min_tension,max_tension,min_pressure,max_pressure);

    return p;
    
}


