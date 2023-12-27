// app_settings.h includes all defines/settings related to the app
// wifi/mqtt credentials, toggle functionality, sreen/input rotation, time, etc.
#include "app_settings.h"
#include "src/squareline/ui.h"
#include "src/squareline/ui_helpers.h"
#include "display_seven.h"  // Elecrow 7" HMI setup
#include "app_ui.h"         // ui helpers specific to this app
#include "app_wifi.h"       // wifi setup
#include "app_mqtt.h"       // mqtt pub sub
#include "app_time.h"       // ntp client
#include "app_led_strip.h"  // led using adafruit neopixel
#include "app_sd.h"         // SD card setup and helpers
#include "src/touch.h"


void setup() {

  Serial.begin(SERIAL_BAUD);
  
  Serial.println( "begin setup" );
  // initialize the display
  // initialize lvgl
  // register the display with lvgl
  display_setup();
  // initialize the touchscreen
  Serial.println( "init touch" );
  touch_init();  
  Serial.println( "Register touchpad" );
  // register the touchscreen with lvgl
  touch_register();  
  // initialize the squareline ui
  ui_init();
  // initialize app ui. e.g. setup variables and do any prep
  appui_setup();
  // initialize sd card
  sd_setup();
  // initialize network
  setLoadingText( "Initializing WiFi.." );
  setLoadingPercent(33);
  Serial.println( "Setup done, init WiFi" );
  // initialize wifi, set loading screen bar to 66% when complete
  wifi_setup(66);
  lv_timer_handler(); // todo swap to call backs for non-blocking wifi/mqtt connection

#if(TIME_ENABLED == 1)
  time_setup();
#endif
  
#if (MQTT_ENABLED == 1)
  Serial.println("WiFi is connected, init mqtt");
  // initialize mqtt, set loading screen bar to 100% when complete
  mqtt_setup(100);
#else
  Serial.println("WiFi is connected");
  setLoadingPercent(100);
#endif

}

// simple ui tick
long uiUpdateInterval = 5;
long lastUiTick = 0;

void loop() {
  // update the ui timer every n milliseconds
  long now = millis();
  if(lastUiTick = 0 || now - lastUiTick > uiUpdateInterval) {
    lastUiTick = now;
    lv_timer_handler();
  }
  // update charts, show screensaver, etc.
  appui_loop();

#if (MQTT_ENABLED == 1)
  // check mqtt connection
  mqtt_loop();
#endif

#if (LED_STRIP_ENABLED == 1)
  // run led animations
  led_strip_loop();
#endif

#if (TIME_ENABLED == 1)
  // update time from ntpclient
  time_loop();
#endif

}

void touch_register() {
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = touchpad_read;
  lv_indev_drv_register(&indev_drv);
  Serial.println( "init ui" );
}

bool touchValid = false;
long invalidTickLimit = 100;
long touchTicks = 0;
void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      #if (SCREENSAVER_ENABLED == 1)
        dismissScreenSaver();
      #endif
      data->state = LV_INDEV_STATE_PR;
      if(touchValid == false && (touch_last_x > SCREEN_WIDTH || touch_last_y > SCREEN_HEIGHT)){
        touchTicks += 1; 
        if (touchTicks > invalidTickLimit) {
          Serial.println("Touch Screen readings are not valid. Restarting..");
          ESP.restart();
        }
      } else {
        touchValid = true;
      }
      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
      Serial.print( "Data x " );
      Serial.println( data->point.x );
      Serial.print( "Data y " );
      Serial.println( data->point.y );
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}



