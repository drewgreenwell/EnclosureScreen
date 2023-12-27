#ifndef APP_MQTT_H
#define APP_MQTT_H

#include <WiFi.h>

extern WiFiClient wifiClient;
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void mqtt_setup(int progress);
void connect_mqtt();
void mqtt_loop();
#endif