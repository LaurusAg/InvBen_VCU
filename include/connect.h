//Header file for connection functions like wifi, mqtt, and reconnect.
//In this file we can find al the function declarations.

#ifndef CONNECT_H
#define CONNECT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

extern WiFiClient VCU;
extern PubSubClient client;

void setup_wifi();
void setup_mqtt();
void reconnect();
void callback();

#endif