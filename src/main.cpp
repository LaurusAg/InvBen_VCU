/*Firmware for VCU (Ventilator Control Unit)
  The system takes values of pressure from the sensor Sensirion SDP2000-l
  whenever the value of P < 200 Pascals return on for the vent and inform to the central.
  if the ventilator is on it has to keep that state until the pressure reaches P > 700. and inform the 
  change of state.
  Every time it measure pressure has to send the value by mqtt protocol to the central.
*/


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "connect.h"
#include "sensor.h"
#include "delay.h"

Delay sensorDelay;


void setup() {
  Serial.begin(115200);

  setup_wifi();
  setup_mqtt();

  //time declarations:
  sensorDelay.start(5000);

}

void loop() {
  

        //make a clock period here to use non-blocking functions!
        if(!client.connected()) 
        {
          reconnect();
        }

        client.loop(); 

  
  if(sensorDelay.isExpired())
  {
       float pressureValue = pressureControl();
        Serial.println(pressureValue);

        sensorDelay.reset();
  }


}

