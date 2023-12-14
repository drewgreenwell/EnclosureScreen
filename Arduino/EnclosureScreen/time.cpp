#include "time.h"
#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "app_ui.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedTime;

int updateInterval = 1000;
long lastTick = 0;
boolean loaded = false;
const int secondsInHour = 3600;
#ifdef GMT_OFFSET
int gmtOffset = GMT_OFFSET;
#else
int gmtOffset = -8;
#endif

void time_init() {
  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(secondsInHour * gmtOffset);
}

void loop_time() {
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
  formattedTime = timeClient.getFormattedTime();
  // Serial.println(formattedTime);

  // Extract date
  // int splitT = formattedDate.indexOf("T");
  // dayStamp = formattedDate.substring(0, splitT);
  // Serial.print("DATE: ");
  // Serial.println(dayStamp);
  // // Extract time
  // timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  // Serial.print("HOUR: ");
  // Serial.println(timeStamp);
  setTimeText(formattedTime.c_str());
}