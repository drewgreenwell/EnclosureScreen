// global include for app settings
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

// audio
#define I2S_DOUT 17
#define I2S_BCLK 42
#define I2S_LRC  18

// #define MSG_BUFFER_SIZE	(50)
// char msg[MSG_BUFFER_SIZE];

void setup() {

  Serial.begin(SERIAL_BAUD);
  Serial.println( "begin setup" );
  display_setup();

  Serial.println( "init lvgl" );
  lv_init();
  display_register();

  // Init touch device
  Serial.println( "init touch" );
  touch_init();
  
  Serial.println( "Register touchpad" );
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = touchpad_read;
  lv_indev_drv_register(&indev_drv);
  Serial.println( "init ui" );
  
  // initialize the squareline ui
  ui_init();
  // setup variables and do any prep
  appui_init();
  
  sd_setup();

  setLoadingText( "Initializing WiFi.." );
  setLoadingPercent(33);
  Serial.println( "Setup done, init WiFi" );
  // initialize wifi, set loading screen bar to 66% when complete
  wifi_init(66);
  lv_timer_handler(); // todo swap to call backs for non-blocking wifi/mqtt connection
  
#if(TIME_ENABLED == 1)
  time_init();
#endif
  
#if (MQTT_ENABLED == 1)
  Serial.println("WiFi is connected, init mqtt");
  // initialize mqtt, set loading screen bar to 100% when complete
  mqtt_init(100);
#else
  Serial.println("WiFi is connected");
  setLoadingPercent(100);
#endif

}

// simple ui tick
long uiUpdateInterval = 5;
long lastUiTick = 0;

// testing dynamic chart updating
long chartUpdateInterval = 5000;
long lastChartTick = 0;
bool swapChartData = false;

long screenSaverDelay = SCREENSAVER_TIMEOUT;
long lastScreenSaverTick = 0;
bool screenSaverActive = false;

void loop() {
    // update the ui timer every n milliseconds
  long now = millis();
  if(lastUiTick = 0 || now - lastUiTick > uiUpdateInterval) {
    lastUiTick = now;
    lv_timer_handler();
  }


#if (MQTT_ENABLED == 1)
  loop_mqtt();
#endif

#if (LED_STRIP_ENABLED == 1)
  loop_led_strip();
#endif

#if (TIME_ENABLED == 1)
  loop_time();
#endif

  now = millis();
  if(now - lastChartTick > chartUpdateInterval){
    swapChartData = !swapChartData;
    lastChartTick = now;
    setChartSeries1Data(ui_chartEnder, swapChartData);
    setChartSeries1Data(ui_chartPrusa, swapChartData);
  }

#if (SCREENSAVER_ENABLED == 1)
  now = millis();
  if(loadComplete){
    if(now - lastScreenSaverTick > screenSaverDelay){
      lastScreenSaverTick = now;
      if(!screenSaverActive) {
        screenSaverActive = true;
        changeToScreenSaverScreen();
      }
    } 
  } else {
    lastScreenSaverTick = now;
  }
#endif
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
      // reset the screensaver idle time
      lastScreenSaverTick = millis();
      // if the screensaver is visible swap back to main screen
      // todo pop from a stack or prev_screen variable
      if(screenSaverActive) {
        screenSaverActive = false;
        changeToMainScreen();
      }
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



