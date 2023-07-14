//Header file for sensor functions
//In this file we can find al the function declarations.

#ifndef SENSOR_H
#define SENSOR_H

    typedef struct 
    {
    uint16_t on_pressure;
    uint16_t off_pressure;
    bool vent_state;
    float pressure;
    }ventilator;



//Functions: 
void ventilatorInit();
float pressureControl();
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
bool logicProcess(float pressure);

#endif