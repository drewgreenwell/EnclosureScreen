#include "app_settings.h"
#include "app_ui.h"
#include "app_wifi.h"

// network config
//wifi credentials
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
#if (STATIC_IP == 1)
IPAddress local_ip;
IPAddress gateway;
IPAddress subnet;
IPAddress dns1;
IPAddress dns2;
#endif

WiFiClient wifiClient;

// amount to display in progress bar when connected if loading
int wifiProgress = 0;

void wifi_init(int progress) {
  // WiFi.mode(WIFI_STA);
  wifiProgress = progress;
  WiFi.disconnect();
  WiFi.onEvent(WiFiEvent);
#if (STATIC_IP == 1)
  local_ip.fromString(LOCAL_IP);
  gateway.fromString(GATEWAY_IP);
  subnet.fromString(SUBNET_IP);
  dns1.fromString(DNS1_IP);
  dns2.fromString(DNS2_IP);
  if(!WiFi.config(local_ip, gateway, subnet, dns1, dns2)){
   Serial.println("Failed to configure Wifi!");
  }
#endif
  WiFi.begin(ssid, password);
  WiFi.setAutoReconnect(true);
  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("connecting..");
  }
}

void WiFiEvent(WiFiEvent_t event){
    Serial.printf("[WiFi-event] event: %d\n", event); 
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP: 
          Serial.print("Obtained IP address: ");
          IPAddress localIp = WiFi.localIP();
          Serial.println(localIp);
          setIpText(localIp.toString().c_str());
          if(!loadComplete){
            
            setWifiState(true);
            setLoadingPercent(wifiProgress);
          }
        break;
    }
}