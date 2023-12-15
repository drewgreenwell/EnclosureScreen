#ifndef DISPLAY_SEVEN_H
#define DISPLAY_SEVEN_H

#include <lvgl.h>

#define LGFX_USE_V1

#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>

class LGFX : public lgfx::LGFX_Device {
public:
  // Instances for the RGB bus and panel.
  lgfx::Bus_RGB     _bus_instance;
  lgfx::Panel_RGB   _panel_instance;
  // Constructor for the LGFX class.
  LGFX(void);
};

extern LGFX lcd;

void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void display_setup();
void display_register();

#endif