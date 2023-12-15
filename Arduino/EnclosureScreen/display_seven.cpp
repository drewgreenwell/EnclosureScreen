#include "app_settings.h"
#include "display_seven.h"

#define TFT_BL 2

void display_setup(){
    lcd.begin();
    lcd.fillScreen(TFT_BLACK);
    lcd.setTextSize(2);
    lcd.setRotation(SCREEN_ROTATION);
    delay(300);

  #ifdef TFT_BL
    Serial.println( "init TFT BL" );
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    ledcSetup(1, 300, 8);
    ledcAttachPin(TFT_BL, 1);
    ledcWrite(1, 255); /* Screen brightness can be modified by adjusting this parameter. (0-255) */

  #endif
}

/* Display flushing */
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1); 
  //lcd.fillScreen(TFT_WHITE);
  #if (LV_COLOR_16_SWAP != 0)
  lcd.pushImageDMA(area->x1, area->y1, w, h,(lgfx::rgb565_t*)&color_p->full);
  #else
    lcd.pushImageDMA(area->x1, area->y1, w, h,(lgfx::rgb565_t*)&color_p->full);//
  #endif
    lv_disp_flush_ready(disp);
}


static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
//static lv_color_t *disp_draw_buf;
static lv_color_t disp_draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 15];
static lv_disp_drv_t disp_drv;


void display_register() {
  screenWidth = lcd.width();
  screenHeight = lcd.height();  
  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 15); //4
  Serial.println( "init display" );
  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = display_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
}

LGFX::LGFX(void){
  // Configure the RGB bus.
  {
    auto cfg = _bus_instance.config();
    cfg.panel = &_panel_instance;


    // Configure data pins.
    cfg.pin_d0  = GPIO_NUM_15; // B0
    cfg.pin_d1  = GPIO_NUM_7;  // B1
    cfg.pin_d2  = GPIO_NUM_6;  // B2
    cfg.pin_d3  = GPIO_NUM_5;  // B3
    cfg.pin_d4  = GPIO_NUM_4;  // B4
    
    cfg.pin_d5  = GPIO_NUM_9;  // G0
    cfg.pin_d6  = GPIO_NUM_46; // G1
    cfg.pin_d7  = GPIO_NUM_3;  // G2
    cfg.pin_d8  = GPIO_NUM_8;  // G3
    cfg.pin_d9  = GPIO_NUM_16; // G4
    cfg.pin_d10 = GPIO_NUM_1;  // G5
    
    cfg.pin_d11 = GPIO_NUM_14; // R0
    cfg.pin_d12 = GPIO_NUM_21; // R1
    cfg.pin_d13 = GPIO_NUM_47; // R2
    cfg.pin_d14 = GPIO_NUM_48; // R3
    cfg.pin_d15 = GPIO_NUM_45; // R4


    // Configure sync and clock pins.
    cfg.pin_henable = GPIO_NUM_41;
    cfg.pin_vsync   = GPIO_NUM_40;
    cfg.pin_hsync   = GPIO_NUM_39;
    cfg.pin_pclk    = GPIO_NUM_0;
    cfg.freq_write  = 15000000;


    // Configure timing parameters for horizontal and vertical sync.
    cfg.hsync_polarity    = 0;
    cfg.hsync_front_porch = 40;
    cfg.hsync_pulse_width = 48;
    cfg.hsync_back_porch  = 40;
    
    cfg.vsync_polarity    = 0;
    cfg.vsync_front_porch = 1;
    cfg.vsync_pulse_width = 31;
    cfg.vsync_back_porch  = 13;


    // Configure polarity for clock and data transmission.
    cfg.pclk_active_neg   = 1;
    cfg.de_idle_high      = 0;
    cfg.pclk_idle_high    = 0;


    // Apply configuration to the RGB bus instance.
    _bus_instance.config(cfg);
  }

  // Configure the panel.
  {
    auto cfg = _panel_instance.config();
    cfg.memory_width  = SCREEN_WIDTH;
    cfg.memory_height = SCREEN_HEIGHT;
    cfg.panel_width   = SCREEN_WIDTH;
    cfg.panel_height  = SCREEN_HEIGHT;
    cfg.offset_x      = 0;
    cfg.offset_y      = 0;


    // Apply configuration to the panel instance.
    _panel_instance.config(cfg);
  }


  // Set the RGB bus and panel instances.
  _panel_instance.setBus(&_bus_instance);
  setPanel(&_panel_instance);
}


LGFX lcd;

