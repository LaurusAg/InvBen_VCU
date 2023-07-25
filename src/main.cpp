/*Firmware for VCU (Ventilator Control Unit)
  The system takes values of pressure from the sensor Sensirion SDP2000-l
  whenever the value of P < 200 Pascals return on for the vent and inform to the central.
  if the ventilator is on it has to keep that state until the pressure reaches P > 700. and inform the 
  change of state.
  Every time it measure pressure has to send the value by mqtt protocol to the central.
*/


#include <Arduino.h>
//#include <ESP8266WiFi.h>
//#include <PubSubClient.h>
//#include "connect.h"
#include "logic.h"
#include "delay.h"
#include "HAL.h"

 Delay sensorDelay;
 Delay reconnectionDelay;
// delay_t  reconnectionDelay;
// delay_t sensorDelay;

void setup() {
  Serial.begin(115200);
  Serial.println("START");
 // setup_wifi();
 // setup_mqtt();

   halSetup();
   halINIT();
  ventilatorInit();
  
  //time declarations:
  sensorDelay.start(DELAY_5_S);
  reconnectionDelay.start(DELAY_250_MS);

 /*  delayInit(&reconnectionDelay, DELAY_250_MS);
  delayInit(&sensorDelay, DELAY_5_S); */ 

}

void loop() {
  

  /*  if(reconnectionDelay.isExpired())
  {
      if(!client.connected()) 
        {
          reconnect();
        }
        reconnectionDelay.reset();
  }*/
  
    /*  if(delayRead(&reconnectionDelay))
        {
          if(!client.connected())
          {
            reconnect();
          }
          delayWrite(&reconnectionDelay, DELAY_250_MS);
        }*/


  
 if(sensorDelay.isExpired())
  {
        float pressureValue = pressureControl();
        //bool result = logicProcess(pressureValue);
        bool result = logicProcess(pressureValue);
        presurization(result, pressureValue);
        sensorDelay.reset();
  }


/*  if(delayRead(&sensorDelay))
  {
    float pressureValue = pressureControl();
    delay(10);
    Serial.println(pressureValue);
    bool result = logicProcess(pressureValue);
    delay(10);
    Serial.println(result);
    delayWrite(&sensorDelay, DELAY_5_S);
    */


//Declare client loop to handle PubSubclient service.
 // client.loop();
 delay(10);
}

