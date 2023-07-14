#include <Arduino.h>
#include "connect.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>




    const char* ssid =         "Laurus 2.4GHz";
    const char* password =     "LaurusBialetti";
    const char* mqtt_server =  "192.168.0.8";
    const int   mqttPort =      1883;
    const char* mqttUser =      "pi";
    const char* mqttPassword =  "laurus";

/*setup_wifi: connects the device to the wifi service!
    has to be called from SETUP!
*/

void setup_wifi()
{
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.println(".-");
    }
    Serial.print("Connected to WiFi!!");
}

    
/*setup_mqtt connects the device with the mqtt server.
after it connects, you can subscribe to topics to hear them!
has to be called from SETUP!
*/
void setup_mqtt()
{


    while(!client.connected()) {
        Serial.println("Connecting to mqtt server..");
        if(!client.connect("CCU", mqttUser, mqttPassword))
        {
            Serial.println("Connected to MQTT server!");
        } else 
        {
            Serial.println("That didn't work, failed with state: ");
            Serial.println(client.state());
        }
    }
    
    /*
    Make subscriptions here if necessary!
    client.subscribe("TOPIC");
    Serial.println("subscript to TOPIC");
    */
    
    delay(10);
client.setServer(mqtt_server, mqttPort);
}


/* Recconect: once we are connected, we run the loop,
 if we go offline in any moment, we call this function 
 from loop and stay here until we reconnect to all services!
 */
void reconnect()
{

    while(!client.connected()) 
    {
        //make a clock period here to use non-blocking functions!
        Serial.println("Reconnecting client with mqtt server..");

        if(client.connect("VCU",mqttUser,mqttPassword))
        {
            Serial.println("Reconnected!");
                //Make all subscriptions here again.
        }
    }
}

/*callback: use if you have to receive orders from CCU.
first subscribe in setup_mqtt & reconnect.
*/

void callback()
{
        //make subscriptions.
}