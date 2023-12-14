#include <WiFi.h>
// #include <Wire.h>
#include "src/squareline/ui.h"
#include "src/squareline/ui_helpers.h"
#include "display_seven.h"  // Elecrow 7" HMI setup
#include "app_ui.h"         // ui helpers specific to this app
#include "app_mqtt.h"       // mqtt pub sub functionality
#include "app_time.h"       // ntp client
#include "app_led_strip.h"  // led using adafruit neopixel
#include "app_sd.h"         // SD card setup and helpers
/*
1 - ROTATION_RIGHT
2 - ROTATION_NORMAL
3 - ROTATION_LEFT
4 - ROTATION_INVERTED
*/
// screen rotation is currently set in display_seven.h
#define INPUT_TOUCH_ROTATION ROTATION_INVERTED
#include "src/touch.h"

// serial communciation
#define SERIAL_BAUD 115200

// enable static ip config
#define STATIC_IP 1
// enable mqtt client
#define MQTT_ENABLED 1
// enable led_strip on pin 38
#define LED_STRIP_ENABLED 1

#define TIME_ENABLED 1
#define GMT_OFFSET -8

//wifi credentials
const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

// network config
#if (STATIC_IP == 1)
IPAddress local_ip(192, 168, 1, 42);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns1(192, 168, 1, 1);
IPAddress dns2(8, 8, 8, 8);
#endif

// audio
#define I2S_DOUT 17
#define I2S_BCLK 42
#define I2S_LRC  18

#define Z_THRESHOLD 350 // Touch pressure threshold for validating touches
#define _RAWERR 20 // Deadband error allowed in successive position samples

// uint16_t touchCalibration_x0 = 300, touchCalibration_x1 = 3600, touchCalibration_y0 = 300, touchCalibration_y1 = 3600;
// uint8_t  touchCalibration_rotate = 1, touchCalibration_invert_x = 2, touchCalibration_invert_y = 0;

WiFiClient wifiClient;

#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

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

  // sd_setup();
  // LV_IMG_DECLARE(bulb_gif);
  // lv_gif_set_src(ui_imgLoading, &bulb_gif);

  setLoadingPercent(33);
  
  setLoadingText("Initializing WiFi..");

  Serial.println( "Setup done, init WiFi" );
  
  // initialize wifi, set loading screen bar to 66% when complete
  wifi_init(66);

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

}



// todo: check for bad input on startup
bool touchValid = false;
long invalidTickLimit = 100;
long touchTicks = 0;
void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
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

// amount to display in progress bar when connected if loading
int wifiProgress = 0;
void wifi_init(int progress) {
  // WiFi.mode(WIFI_STA);
  wifiProgress = progress;
  WiFi.disconnect();
  WiFi.onEvent(WiFiEvent);
#if (STATIC_IP == 1)
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
            _ui_state_modify(ui_imgWifi, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
            setLoadingPercent(wifiProgress);
          }
        break;
    }
}

