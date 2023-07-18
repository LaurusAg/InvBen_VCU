#include <Arduino.h>
#include "logic.h"
#include "connect.h"
#include "delay.h"
#include "HAL.h"

  ventilator backupVentilator;
  ventilator presurizationFan;
  
  Delay safetyTimeDelay;
  Delay valveTimer;

  #define closed 0
  #define open 1
  #define valveTime 30000

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
  backupVentilator.valvePosition = closed; //Assuming that closed is false.
  
  presurizationFan.vent_state = false;
  presurizationFan.on_pressure = 650;
  presurizationFan.off_pressure = 900;
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


/**
 * @brief logicProcess takes the value of pressure from pressureControl and use it to check if it's neccesary to turn ON or OFF the backup ventilator
 *        also start a timer when the backup it's ON in order to turn ON a presurization vent if too much time pass and we don't reach a threshold pressure.
 * 
 * @param pressure pressure coming from the diferential pressure sensor, reading on pressureControl function.
 * 
 * @return NULL.
 */
bool logicProcess(float pressure)
{
  float actualPressure = pressure;

  if ( backupVentilator.vent_state == false)
  {
    if(actualPressure < backupVentilator.on_pressure)
    {
      //Change valve position.
      backupVentilator.valvePosition = open;
      valveTimer.start(valveTime);
      //digitalWrite(D1, open)
      turnON(VALVE_PIN);

      //Wait 30 seconds minimun.
      if (valveTimer.isExpired() == true) 
      {
          turnON(BACKUPVENT_PIN);
           backupVentilator.vent_state = true;
           valveTimer.stop();
      }     
    }
    return backupVentilator.vent_state;

  } else if ( backupVentilator.vent_state == true)
  {
    if (actualPressure > backupVentilator.off_pressure)
    {
      //Change valve position.
      backupVentilator.valvePosition = closed;
      turnOFF(VALVE_PIN);
      valveTimer.start(valveTime);
      

      //Wait 30 seconds minimun.
      if(valveTimer.isExpired() == true)
      {
          //TURN OFF DIGITAL OUTPUT!
          turnOFF(BACKUPVENT_PIN);
          backupVentilator.vent_state = false;
          valveTimer.stop();
      }
    }
    return backupVentilator.vent_state;
  }
  
  publishVentState(backupVentilator.vent_state);
  presurization (backupVentilator.vent_state, actualPressure);

  return false;

}


void presurization (bool backupVentState, float pressure)
{
  bool ventState = backupVentState ;
  float actualPressure = pressure ;

  const uint32_t safetyTime(120000); // Two minutes to reach the pressure value. 


  if (ventState == true)
  {
    safetyTimeDelay.start(safetyTime);

      if (safetyTimeDelay.isExpired() == true ) //if it's been 2 minutes since we started the backupVent and hasn't reached the minimun pressure.
      {
        if ((actualPressure < presurizationFan.on_pressure))
        {
              //TURN ON EXIT for presurization fan.
              turnON(PRESURIZATION_PIN);
        
        safetyTimeDelay.reset();
        }else 
        {
          //TURN OFF EXIT for presurization fan.
          turnOFF(PRESURIZATION_PIN);
          safetyTimeDelay.reset();
        }
    
      } 
  }
}