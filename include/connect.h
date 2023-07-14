//Header file for connection functions like wifi, mqtt, and reconnect.
//In this file we can find al the function declarations.

#ifndef CONNECT_H
#define CONNECT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

struct connectionInfo
{
    const char* ssid;
    const char* password;
    const char* mqtt_server;
    const int   mqttPort;
    const char* mqttUser;
    const char* mqttPassword;
};


extern WiFiClient VCU;
extern PubSubClient client;
extern connectionInfo benavidezConnection;


void setup_wifi();
void setup_mqtt();
void reconnect();
void callback();
void publishPressure(float pressure);
void publishVentState(bool ventState);

#endif