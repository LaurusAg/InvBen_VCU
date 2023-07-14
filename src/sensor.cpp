#include <Arduino.h>
#include "sensor.h"
#include "connect.h"

  ventilator backupVentilator;

struct conversion
{
  float min_tension;
  float max_tension;
  float min_pressure;
  float max_pressure;
  float adc_value;
};



/**
 * @brief initialize ventilator state in false in order to start OFF.
 * @return NULL
 */
void ventilatorInit()
{
  backupVentilator.vent_state = false;
  backupVentilator.on_pressure = 200; 
  backupVentilator.off_pressure = 700;

}



/**
 * @brief map values of tension to Pascal unit.
 * 
 * @param x is the actual tension value, call it "v".
 * @param in_min minimum value of tension provided by sensor.
 * @param in_max maximum value of tension provided by sensor.
 * @param out_min minimum value of pressure in Pascal units.
 * @param out_max maximum value of pressure in Pascal units.
 * 
 * @return value of pressure.
 */
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return ( ((x - in_min) *  (out_max - out_min)) / ((in_max - in_min) + out_min ) ) ; 
}

/**
 * @brief Read sensor pin, process the ADC value trough the mapfloat function.
 * 
 * @return pressure value.
 */
float pressureControl()
{

    //Variables declaration: 
    conversion actualValues = {0.2, 5.0, 0.0, 3500.0, 1023.0};
    float v;
    uint16_t sensor;

    sensor = analogRead(A0);
    v =((sensor * actualValues.max_tension)/actualValues.adc_value);
    backupVentilator.pressure = mapfloat(v, actualValues.min_tension, actualValues.max_tension, actualValues.min_pressure, actualValues.max_pressure);

    publishPressure(backupVentilator.pressure);

    return backupVentilator.pressure;
    
}

bool logicProcess(float pressure)
{
  float actualPressure = pressure;

  if ( backupVentilator.vent_state == false)
  {
    if(actualPressure < backupVentilator.on_pressure)
    {
      //TURN ON DIGITAL OUTPUT!.
      backupVentilator.vent_state = true;
      return backupVentilator.vent_state;
    }
  } else if ( backupVentilator.vent_state == true)
  {
    if (actualPressure < backupVentilator.off_pressure)
    {
      //TURN OFF DIGITAL OUTPUT!
      backupVentilator.vent_state = false;
      return backupVentilator.vent_state;
    }
  }
  
  publishVentState(backupVentilator.vent_state);


  return false;

}

