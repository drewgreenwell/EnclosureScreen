#include "app_settings.h"
#include "app_mqtt.h"
#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP32Ping.h>
#include "app_ui.h"

#define MQTT_QOS 0

const char *mqtt_server = MQTT_SERVER;
const char *mqtt_user = MQTT_USER;
const char *mqtt_pass = MQTT_PASSWORD;
// set to your client id
String clientId = MQTT_CLIENTID;

PubSubClient mqttClient(wifiClient);

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
    // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    // digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    // digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
}

// amount to display in progress bar when connected if loading
int mqttProgress = 0;

void mqtt_init(int progress) {
  mqttProgress = progress;
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(mqtt_callback);
  mqttClient.setKeepAlive(90);
}

boolean started = false;
long lastMqttTick = 0;
int mqttStartupDelay = 3000; // add a small delay to let ui update

void loop_mqtt() {
  if (!started) {
    long now = millis();
    if(lastMqttTick == 0) {
      lastMqttTick = now;
    } else if(now - lastMqttTick > mqttStartupDelay) {
      started = true;
    }
  } else {
    if (!mqttClient.connected()) {
      connect_mqtt();
    }
      mqttClient.loop();
    }
}

void connect_mqtt() {
  // Loop until we're reconnected
  if(!loadComplete){
    setLoadingText("Initializing MQTT..");
  }
  while (!mqttClient.connected()) {
   
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqtt_server);
    Serial.print(" ");
    Serial.print(clientId);
    Serial.print("...");
    // clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqttClient.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.print("connected.. pub=");
      // Once connected, publish an announcement...
      boolean pub = mqttClient.publish("homeassistant", "{'msg':'hello world'}");
      // ... and resubscribe
      boolean sub = mqttClient.subscribe("printer");
      Serial.print(pub);
      Serial.print("sub=");
      Serial.println(sub);
      if (!loadComplete && mqttProgress > 0) {
        setMosquittoState(true);
        setLoadingPercent(mqttProgress);
      }
    } else {
      wl_status_t status = WiFi.status();
      Serial.println(status);
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      bool ret = Ping.ping(mqtt_server);
      bool ret2 = Ping.ping("www.google.com");
      Serial.print(" Server/Ext ping=");
      Serial.print(ret);
      Serial.print("/");
      Serial.print(ret2);
      Serial.print("...");
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}