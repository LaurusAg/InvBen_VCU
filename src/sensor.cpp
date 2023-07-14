#include <Arduino.h>
#include "sensor.h"

struct conversion
{
  float min_tension;
  float max_tension;
  float min_pressure;
  float max_pressure;
  float adc_value;
};


float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return ( ((x - in_min) *  (out_max - out_min)) / ((in_max - in_min) + out_min ) ) ; 
}


float pressureControl()
{

    //Variables declaration: 
    conversion actualValues = {0.2, 5.0, 0.0, 3500.0, 1023.0};
    float v;
    uint16_t sensor;
    ventilator miPressure;

    sensor = analogRead(A0);
    v =((sensor * actualValues.max_tension)/actualValues.adc_value);
    miPressure.pressure = mapfloat(v, actualValues.min_tension, actualValues.max_tension, actualValues.min_pressure, actualValues.max_pressure);

    return miPressure.pressure;
    
}


