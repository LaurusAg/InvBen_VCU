#include <Arduino.h>
#include "logic.h"
#include "connect.h"
#include "delay.h"
#include "HAL.h"
#include "APIdelay.h"

  ventilator backupVentilator;
  ventilator presurizationFan;

//delay_t valveTimer;

    #define closed 0
    #define open 1 
 
unsigned long timerCounter = 0;
unsigned long timerCounter2 = 0;
const uint8_t timerCounterInterval = 5;
const uint8_t timerCounterInterval2 = 4;
const uint8_t timerCounterInterval3 = 18;
#define RESET 0


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
  backupVentilator.vent_state = true;
  backupVentilator.on_pressure = 300; 
  backupVentilator.off_pressure = 700;
  backupVentilator.valvePosition = closed; //Assuming that closed is false.
  
  presurizationFan.vent_state = false;
  presurizationFan.on_pressure = 650;
  presurizationFan.off_pressure = 900;

 // delayInit(&safetyTimeDelay, DELAY_2_M);
 // delayInit(&valveTimer,DELAY_30_S);
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
    conversion actualValues = {0.23, 4.7, 0.0, 3500.0, 1023.0};
    float v;
    uint16_t sensor;

    sensor = analogRead(A0);
    v = constrain (v,actualValues.min_tension, actualValues.max_tension);
    v = (sensor * (actualValues.max_tension/actualValues.adc_value));
    backupVentilator.pressure = (mapfloat(v, actualValues.min_tension, actualValues.max_tension, actualValues.min_pressure, actualValues.max_pressure)-110);
    delay(10);
    Serial.println("Pressure: ");
    Serial.println(backupVentilator.pressure);
    delay(10);
    //publishPressure(backupVentilator.pressure);

    return backupVentilator.pressure;
    
}


void presurization (bool backupVentState, float pressure)
{
  Serial.println("Entramos en presurization");
  bool ventState = backupVentState;
  float actualPressure = pressure;


  if ( ventState == true)
  {
    //increase timer 18 times to reach 100 seconds
    timerCounter2++;
    Serial.println("timer counter: ");
      Serial.println(timerCounter2);
    if(timerCounter2 >= timerCounterInterval3)
    {
      if(actualPressure < presurizationFan.on_pressure)
      {
        turnOnRelay(PRESURIZATION_PIN);
        Serial.println("PRESURIZADOR PRENDIDO");
        timerCounter2 = RESET;
      }
      else if (actualPressure > presurizationFan.on_pressure)
      {
        turnOffRelay(PRESURIZATION_PIN);
        Serial.println("PRESURIZADOR APAGADO");
        timerCounter2 = RESET;
      }
      

    }

  }

  if ( ventState == false)
  {
    turnOffRelay(PRESURIZATION_PIN);
    Serial.println("PRESURIZADOR APAGADO por las dudas");
  }

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
  Serial.println("PRESION: ");
  Serial.println(pressure);

  if ( backupVentilator.vent_state == false)
  {
    if(actualPressure < backupVentilator.on_pressure)
    {
      backupVentilator.valvePosition = open;
      turnOnRelay(VALVE_PIN);
      Serial.println("VALVULA PRENDIDA, presion menor a 300");
      //Increase timer by 1.
      timerCounter++;
      Serial.println("timer counter: ");
      Serial.println(timerCounter);
      //logicProcess executes every 5.3 seconds. 5 timer counter means 27 seconds.
      if( timerCounter >= timerCounterInterval )
       {
          turnOnRelay(BACKUPVENT_PIN);
          Serial.println("VENTILADOR PRENDIDO");
           backupVentilator.vent_state = true;
           timerCounter = RESET;
      }   
    }
    return backupVentilator.vent_state;
     

  } 

if ( backupVentilator.vent_state == true)
  {
    if (actualPressure > backupVentilator.off_pressure)
    {Serial.println("VALVULA APAGADA, presion mayor a 700");

      backupVentilator.valvePosition = closed;
      turnOffRelay(VALVE_PIN);
      //Increase timer by 1.
      timerCounter++; 
      Serial.println("timer counter: ");
      Serial.println(timerCounter);
      //logicProcess executes every 5.3 seconds. 4 timer counter means 22 seconds.
      if(timerCounter >= timerCounterInterval2)
      {
          turnOffRelay(BACKUPVENT_PIN);
           Serial.println("VENTILADOR APAGADO");
          backupVentilator.vent_state = false;
          timerCounter = RESET;
      }
    }
    return backupVentilator.vent_state;
    presurization (backupVentilator.vent_state, actualPressure);
  }
  
 // publishVentState(backupVentilator.vent_state);
  presurization (backupVentilator.vent_state, actualPressure);

  return false;

}







 /*  if(delayRead(&safetyTimeDelay))
    {
      if( actualPressure < presurizationFan.on_pressure)
      {
        turnOnRelay(PRESURIZATION_PIN);
      }
      else
      {
        turnOffRelay(PRESURIZATION_PIN);
      }
      delayWrite(&safetyTimeDelay, DELAY_2_M);
    }

  */ 





/*
bool logicProcess(float pressure)
{
    float actualPressure = pressure;

    if (backupVentilator.vent_state == false)
    {
        if (actualPressure < backupVentilator.on_pressure)
        {
            // Change valve position.
            backupVentilator.valvePosition = open;
            turnOnRelay(VALVE_PIN);

            if (!delayRead(&valveTimer))
            {
                // The valve is still opening, no need to turn on the ventilator yet.
                turnOnRelay(VALVE_PIN);
            }
            else
            {
                // The valve has opened completely, turn on the ventilator.
                turnOnRelay(BACKUPVENT_PIN);
                backupVentilator.vent_state = true;
                delayWrite(&valveTimer, DELAY_30_S); // Reiniciar el temporizador para su uso futuro
            }
        }
        return backupVentilator.vent_state;
    }
    else
    {
        if (actualPressure > backupVentilator.off_pressure)
        {
            // Close the valve, wait 30 seconds, and turn off the ventilator.
            backupVentilator.valvePosition = closed;
            if (!delayRead(&valveTimer))
            {
                // The valve is still closing, no need to turn off the ventilator yet.
                turnOffRelay(VALVE_PIN);
            }
            else
            {
                // The valve has closed completely, turn off the ventilator.
                turnOffRelay(BACKUPVENT_PIN);
                backupVentilator.vent_state = false;
                delayWrite(&valveTimer, DELAY_30_S); // Reiniciar el temporizador para su uso futuro
            }
        }
        return backupVentilator.vent_state;
    }

    // Si no se cumple ninguna de las condiciones anteriores, se ejecutan estas líneas.
    publishVentState(backupVentilator.vent_state);
    presurization(backupVentilator.vent_state, actualPressure);

    return false;
}
*/

/*void presurization (bool backupVentState, float pressure)
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
              turnOnRelay(PRESURIZATION_PIN);
        
        safetyTimeDelay.reset();
        }else 
        {
          //TURN OFF EXIT for presurization fan.
          turnOffRelay(PRESURIZATION_PIN);
          safetyTimeDelay.reset();
        }
    
      } 
  }
}*/