#include "app_settings.h"
#include "app_time.h"
#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "app_ui.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedTime;

int updateInterval = 1000;
long lastTick = 0;
bool loaded = false;
const int secondsInHour = 3600;
#ifdef GMT_OFFSET
int gmtOffset = GMT_OFFSET;
#else
int gmtOffset = 0;
#endif

void time_setup() {
  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(secondsInHour * gmtOffset);
}

void time_loop() {
  long now = millis();
  if (now - lastTick > updateInterval) {
    lastTick = now;
    updateTime();
  }
}

void updateTime() {
  if(!loaded || !timeClient.isTimeSet()){
    timeClient.forceUpdate();
    loaded = true;
  } else {
    timeClient.update();
  }
  // hh:mm:ss
  formattedTime = timeClient.getFormattedTime();
  setTimeText(formattedTime.c_str());
}