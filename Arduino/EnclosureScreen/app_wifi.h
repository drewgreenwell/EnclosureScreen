#ifndef APP_WIFI_H
#define APP_WIFI_H
#include <WiFi.h>

extern WiFiClient wifiClient;
void wifi_setup(int progress);
void WiFiEvent(WiFiEvent_t event);

#endif
