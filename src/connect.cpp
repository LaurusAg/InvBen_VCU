#include <Arduino.h>
#include "connect.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "WiFiManager.h"

WiFiClient VCU;
PubSubClient client(VCU);

connectionInfo benavidezConnection = 
{
    "Laurus 2.4GHz", 
    "LaurusBialetti",
    "192.168.0.8",
    1883,
    "pi",
    "laurus"
};    



/**
 * @brief Calls wifi manager, start as an AP, save data for WiFi connection.
 *         has to be called from SETUP!
 * @return true if connected, stay on the bucle if not.
 */

void setup_wifi()
{
    WiFiManager WiFiManager;
    if(!WiFiManager.autoConnect("VCU"))
    {
        Serial.println("Failed to connect(timeout)");
        ESP.reset();
        delay(1000);
    }
    
    Serial.println("");
    Serial.println("Connected to the WiFi Network");
}


/**
 * @brief connects the device with the mqtt server.
 *        after it connects, you can subscribe to topics to hear them!
 *        has to be called from SETUP!
 */
void setup_mqtt()
{
    client.setServer(benavidezConnection.mqtt_server, benavidezConnection.mqttPort);    

    while(!client.connected()) 
    {
        Serial.println("Connecting to mqtt server..");
        if(client.connect("VCU", benavidezConnection.mqttUser, benavidezConnection.mqttPassword))
        {
            Serial.println("Connected to MQTT server!");
        } else
        {
            Serial.println("That didn't work, failed with state: ");
            Serial.println(client.state());
            delay(2000);
        }
    }
    
    /*
    Make subscriptions here if necessary!
    client.subscribe("TOPIC");
    Serial.println("subscript to TOPIC");
    */
    
    delay(10);

}



/**
 * @brief once we are connected, we run the loop,
 *if we go offline in any moment, we call this function 
 *from loop and stay here until we reconnect to all services! 
 * @return true if interval has expired, false if not.
 */
void reconnect()
{

    while(!client.connected()) 
    {
        //make a clock period here to use non-blocking functions!
        Serial.println("Reconnecting client with mqtt server..");

        if(client.connect("VCU",benavidezConnection.mqttUser,benavidezConnection.mqttPassword))
        {
            Serial.println("Reconnected!");
                //Make all subscriptions here again.
        }
    }
}


/**
 * @brief use if you have to receive orders from CCU.
 *first subscribe in setup_mqtt & reconnect.
 * 
 * @return true if interval has expired, false if not.
 */
void callback()
{
        //make subscriptions.
}


/** 
* @brief Publish value of pressure
*
*@return NULL
*/
void publishPressure(float pressure)
{
    const char* topic = "VCU/PRESSURE";
    char message[10];
    snprintf(message, sizeof(message), "%.2f", pressure);
    client.publish(topic,message);
}


/** 
* @brief publish value of ventilator state.
*
*@return NULL
*/
void publishVentState(bool ventState)
{
    const char* topic = "backupVentilator/ventState";
    const char* message = ventState ? "true" : "false";
    client.publish(topic, message);
}