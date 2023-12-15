#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480
// default is landscape, set to inverted here so GPIOD is facing down
#define SCREEN_ROTATION 2     // 0=0 1=90 2=180 3=270
/*
1 - ROTATION_RIGHT
2 - ROTATION_NORMAL
3 - ROTATION_LEFT
4 - ROTATION_INVERTED
*/
#define INPUT_TOUCH_ROTATION ROTATION_INVERTED

//wifi credentials
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"
// network config for static ip, set to 0 to disable
#define STATIC_IP 1
#define LOCAL_IP "192.168.1.42"
#define GATEWAY_IP "192.168.1.1"
#define SUBNET_IP "255.255.255.0"
#define DNS1_IP "192.168.1.1"
#define DNS2_IP "8.8.8.8"
// mqtt server
#define MQTT_SERVER "YOUR_MQTT_BROKER_URL_OR_IP"
#define MQTT_USER "YOUR_MQTT_USER"
#define MQTT_PASSWORD "YOUR_MQTT_PASSWORD"
#define MQTT_CLIENTID "A_UNIQUE_CLIENT_ID"

// serial communciation
#define SERIAL_BAUD 115200

// enable mqtt client
#define MQTT_ENABLED 1
// enable led_strip on pin 38
#define LED_STRIP_ENABLED 1
// enabled ntp time and set offset
#define TIME_ENABLED 1
#define GMT_OFFSET -8
// enable screen saver view and set a timeout
#define SCREENSAVER_ENABLED 1
#define SCREENSAVER_TIMEOUT 10000

#endif