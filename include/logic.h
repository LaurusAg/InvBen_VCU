//Header file for logic functions
//In this file we can find al the function declarations.

#ifndef LOGIC_H
#define LOGIC_H

    typedef struct 
    {
    uint16_t on_pressure;
    uint16_t off_pressure;
    bool vent_state;
    float pressure;
    bool valvePosition;
    }ventilator;

   

//Functions: 
void ventilatorInit();
float pressureControl();
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
bool logicProcess(float pressure);
void presurization(bool estadoBackup, float pressure);
float voltageToPressure(float voltage);

#endif