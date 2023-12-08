#include "src/ui.h"
#include "src/ui_helpers.h"
#include <Arduino_GFX_Library.h>
#include <WiFi.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>

// serial communciation
#define SERIAL_BAUD 115200

// enable static ip config
#define STATIC_IP 1
// enable mqtt client
#define MQTT_ENABLED 0
// enable led_strip on pin 38
#define LED_STRIP_ENABLED 0

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

// This display is horizontal by default. 1=90 degrees 2=180 3=270
#define SCREEN_ROTATION 2
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480


// initialize databus
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
  GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
  41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 0 /* PCLK */,
  14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
  9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
  15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3 */, 4 /* B4 */
);

// initialize graphics
// 7 inch 50 pin 800x480
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
  bus,
  SCREEN_WIDTH /* width */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 1 /* hsync_pulse_width */, 46 /* hsync_back_porch */,
  SCREEN_HEIGHT /* height */, 0 /* vsync_polarity */, 22 /* vsync_front_porch */, 1 /* vsync_pulse_width */, 23 /* vsync_back_porch */,
  0 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */);

// led backlight
#define TFT_BL 2

//SD card
#define SD_MOSI 11
#define SD_MISO 13
#define SD_SCK  12
#define SD_CS   10
// audio
#define I2S_DOUT 17
#define I2S_BCLK 42
#define I2S_LRC  18

#define Z_THRESHOLD 350 // Touch pressure threshold for validating touches
#define _RAWERR 20 // Deadband error allowed in successive position samples

SPIClass& spi = SPI;
uint16_t touchCalibration_x0 = 300, touchCalibration_x1 = 3600, touchCalibration_y0 = 300, touchCalibration_y1 = 3600;
uint8_t  touchCalibration_rotate = 1, touchCalibration_invert_x = 2, touchCalibration_invert_y = 0;

#include "src/touch.h"

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
//static lv_color_t *disp_draw_buf;
static lv_color_t disp_draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 15];
static lv_disp_drv_t disp_drv;

WiFiClient wifiClient;

#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

boolean loadComplete = false;

void setup() {

  Serial.begin(SERIAL_BAUD);
  Serial.println( "begin setup" );
  lcd->begin();
  lcd->fillScreen(BLACK);
  lcd->setTextSize(2);
  lcd->setRotation(SCREEN_ROTATION);
  delay(300);

#ifdef TFT_BL
  Serial.println( "init TFT BL" );
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  ledcSetup(1, 300, 8);
  ledcAttachPin(TFT_BL, 1);
  ledcWrite(1, 255); /* Screen brightness can be modified by adjusting this parameter. (0-255) */

#endif
  Serial.println( "init lvgl" );
  lv_init();

  // Init touch device
  Serial.println( "init touch" );
  touch_init();

  screenWidth = lcd->width();
  screenHeight = lcd->height();
  
  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 15); //4
  Serial.println( "init display" );
  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
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
  thisui_init();

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

  // lcd->fillScreen(BLACK);
  // lcd->setCursor(10, 30);
  // lcd->setTextColor(WHITE);
  // lcd->drawRect(0, 0, 800, 480, ORANGE);
  // lcd->println("Hello World!");
  

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

/* Display flushing */
void disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1) + 1;
  uint32_t h = (area->y2 - area->y1) + 1;

#if (LV_COLOR_16_SWAP != 0)
  lcd->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  lcd->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp);
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
      if(touchValid == false && (touch_last_x > screenWidth || touch_last_y > screenHeight)){
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
          if(!loadComplete){
            _ui_state_modify(ui_imgWifi, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
            setLoadingPercent(wifiProgress);
            setIpText(localIp.toString().c_str());
          }
        break;
    }
}

