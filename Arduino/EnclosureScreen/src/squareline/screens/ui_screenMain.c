// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: PrinterScreen

#include "../ui.h"

void ui_screenMain_screen_init(void)
{
ui_screenMain = lv_obj_create(NULL);
lv_obj_clear_flag( ui_screenMain, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_tabMain = lv_tabview_create(ui_screenMain, LV_DIR_BOTTOM, 50);
lv_obj_set_width( ui_tabMain, 800);
lv_obj_set_height( ui_tabMain, 480);
lv_obj_set_x( ui_tabMain, -1 );
lv_obj_set_y( ui_tabMain, 0 );
lv_obj_set_align( ui_tabMain, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_tabMain, LV_OBJ_FLAG_SCROLLABLE );    /// Flags


ui_StatusTab = lv_tabview_add_tab(ui_tabMain, "Status");
lv_obj_clear_flag( ui_StatusTab, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_StatusTab, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_StatusTab, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_pnlTop = lv_obj_create(ui_StatusTab);
lv_obj_set_width( ui_pnlTop, 180);
lv_obj_set_height( ui_pnlTop, 175);
lv_obj_set_x( ui_pnlTop, -279 );
lv_obj_set_y( ui_pnlTop, -84 );
lv_obj_set_align( ui_pnlTop, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_pnlTop, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_lblTopTitle = lv_label_create(ui_pnlTop);
lv_obj_set_width( ui_lblTopTitle, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblTopTitle, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_lblTopTitle, 0 );
lv_obj_set_y( ui_lblTopTitle, -50 );
lv_obj_set_align( ui_lblTopTitle, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_lblTopTitle,"Top Shelf");
lv_obj_set_style_text_color(ui_lblTopTitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_lblTopTitle, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_lblTopTitle, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_lblTopHumidity = lv_label_create(ui_pnlTop);
lv_obj_set_width( ui_lblTopHumidity, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblTopHumidity, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_lblTopHumidity, 0 );
lv_obj_set_y( ui_lblTopHumidity, 30 );
lv_obj_set_align( ui_lblTopHumidity, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_lblTopHumidity,"Humidity 12%");
lv_obj_set_style_text_font(ui_lblTopHumidity, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_lblTopTemp = lv_label_create(ui_pnlTop);
lv_obj_set_width( ui_lblTopTemp, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblTopTemp, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_lblTopTemp, 0 );
lv_obj_set_y( ui_lblTopTemp, -10 );
lv_obj_set_align( ui_lblTopTemp, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_lblTopTemp,"Temp 100F");
lv_obj_set_style_text_font(ui_lblTopTemp, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_chartPrusa = lv_chart_create(ui_StatusTab);
lv_obj_set_width( ui_chartPrusa, 200);
lv_obj_set_height( ui_chartPrusa, 100);
lv_obj_set_x( ui_chartPrusa, 239 );
lv_obj_set_y( ui_chartPrusa, -90 );
lv_obj_set_align( ui_chartPrusa, LV_ALIGN_CENTER );
lv_chart_set_type( ui_chartPrusa, LV_CHART_TYPE_LINE);
lv_chart_set_range( ui_chartPrusa, LV_CHART_AXIS_PRIMARY_Y, 25, 125);
lv_chart_set_range( ui_chartPrusa, LV_CHART_AXIS_SECONDARY_Y, 25, 125);
lv_chart_set_axis_tick( ui_chartPrusa, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
lv_chart_set_axis_tick( ui_chartPrusa, LV_CHART_AXIS_PRIMARY_Y, 0, 5, 0, 2, true, 50);
lv_chart_set_axis_tick( ui_chartPrusa, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);
lv_chart_series_t* ui_chartPrusa_series_1 = lv_chart_add_series(ui_chartPrusa, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);
static lv_coord_t ui_chartPrusa_series_1_array[] = { 0,10,20,40,80,80,40,20,10,0 };
lv_chart_set_ext_y_array(ui_chartPrusa, ui_chartPrusa_series_1, ui_chartPrusa_series_1_array);
lv_chart_series_t* ui_chartPrusa_series_2 = lv_chart_add_series(ui_chartPrusa, lv_color_hex(0xFF0000), LV_CHART_AXIS_SECONDARY_Y);
static lv_coord_t ui_chartPrusa_series_2_array[] = { 100,80,95,88,110,75,50,80,99,102 };
lv_chart_set_ext_y_array(ui_chartPrusa, ui_chartPrusa_series_2, ui_chartPrusa_series_2_array);



ui_chartEnder = lv_chart_create(ui_StatusTab);
lv_obj_set_width( ui_chartEnder, 200);
lv_obj_set_height( ui_chartEnder, 100);
lv_obj_set_x( ui_chartEnder, 239 );
lv_obj_set_y( ui_chartEnder, 90 );
lv_obj_set_align( ui_chartEnder, LV_ALIGN_CENTER );
lv_chart_set_type( ui_chartEnder, LV_CHART_TYPE_LINE);
lv_chart_set_range( ui_chartEnder, LV_CHART_AXIS_SECONDARY_Y, 25, 125);
lv_chart_set_axis_tick( ui_chartEnder, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
lv_chart_set_axis_tick( ui_chartEnder, LV_CHART_AXIS_PRIMARY_Y, 0, 5, 0, 2, false, 50);
lv_chart_set_axis_tick( ui_chartEnder, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);
lv_chart_series_t* ui_chartEnder_series_1 = lv_chart_add_series(ui_chartEnder, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);
static lv_coord_t ui_chartEnder_series_1_array[] = { 0,10,20,40,80,80,40,20,10,0 };
lv_chart_set_ext_y_array(ui_chartEnder, ui_chartEnder_series_1, ui_chartEnder_series_1_array);
lv_chart_series_t* ui_chartEnder_series_2 = lv_chart_add_series(ui_chartEnder, lv_color_hex(0xE92323), LV_CHART_AXIS_SECONDARY_Y);
static lv_coord_t ui_chartEnder_series_2_array[] = { 100,80,95,88,110,75,50,80,99,102 };
lv_chart_set_ext_y_array(ui_chartEnder, ui_chartEnder_series_2, ui_chartEnder_series_2_array);



ui_pnlBottom = lv_obj_create(ui_StatusTab);
lv_obj_set_width( ui_pnlBottom, 180);
lv_obj_set_height( ui_pnlBottom, 175);
lv_obj_set_x( ui_pnlBottom, -279 );
lv_obj_set_y( ui_pnlBottom, 114 );
lv_obj_set_align( ui_pnlBottom, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_pnlBottom, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_lblBottomTitle = lv_label_create(ui_pnlBottom);
lv_obj_set_width( ui_lblBottomTitle, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblBottomTitle, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_lblBottomTitle, 0 );
lv_obj_set_y( ui_lblBottomTitle, -50 );
lv_obj_set_align( ui_lblBottomTitle, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_lblBottomTitle,"Bottom Shelf");
lv_obj_set_style_text_color(ui_lblBottomTitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_lblBottomTitle, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_lblBottomTitle, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_lblBottomHumidity = lv_label_create(ui_pnlBottom);
lv_obj_set_width( ui_lblBottomHumidity, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblBottomHumidity, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_lblBottomHumidity, 0 );
lv_obj_set_y( ui_lblBottomHumidity, 30 );
lv_obj_set_align( ui_lblBottomHumidity, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_lblBottomHumidity,"Humidity 12%");
lv_obj_set_style_text_font(ui_lblBottomHumidity, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_lblBottomTemp = lv_label_create(ui_pnlBottom);
lv_obj_set_width( ui_lblBottomTemp, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblBottomTemp, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_lblBottomTemp, 0 );
lv_obj_set_y( ui_lblBottomTemp, -10 );
lv_obj_set_align( ui_lblBottomTemp, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_lblBottomTemp,"Temp 100F");
lv_obj_set_style_text_font(ui_lblBottomTemp, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SettingsTab = lv_tabview_add_tab(ui_tabMain, "Settings");
lv_obj_clear_flag( ui_SettingsTab, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_colorWheelPrusaLight = lv_colorwheel_create(ui_SettingsTab,true);
lv_obj_set_width( ui_colorWheelPrusaLight, 150);
lv_obj_set_height( ui_colorWheelPrusaLight, 150);
lv_obj_set_x( ui_colorWheelPrusaLight, -183 );
lv_obj_set_y( ui_colorWheelPrusaLight, 0 );
lv_obj_set_align( ui_colorWheelPrusaLight, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_colorWheelPrusaLight, LV_OBJ_FLAG_GESTURE_BUBBLE );    /// Flags

ui_colorWheelEnderLight = lv_colorwheel_create(ui_SettingsTab,true);
lv_obj_set_width( ui_colorWheelEnderLight, 150);
lv_obj_set_height( ui_colorWheelEnderLight, 150);
lv_obj_set_x( ui_colorWheelEnderLight, 188 );
lv_obj_set_y( ui_colorWheelEnderLight, 0 );
lv_obj_set_align( ui_colorWheelEnderLight, LV_ALIGN_CENTER );

ui_lblEnderLightColor = lv_label_create(ui_SettingsTab);
lv_obj_set_width( ui_lblEnderLightColor, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblEnderLightColor, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_lblEnderLightColor, 183 );
lv_obj_set_y( ui_lblEnderLightColor, -124 );
lv_obj_set_align( ui_lblEnderLightColor, LV_ALIGN_CENTER );
lv_label_set_text(ui_lblEnderLightColor,"Ender Light");

ui_lblPrusaLightColor = lv_label_create(ui_SettingsTab);
lv_obj_set_width( ui_lblPrusaLightColor, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblPrusaLightColor, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_lblPrusaLightColor, -183 );
lv_obj_set_y( ui_lblPrusaLightColor, -127 );
lv_obj_set_align( ui_lblPrusaLightColor, LV_ALIGN_CENTER );
lv_label_set_text(ui_lblPrusaLightColor,"Prusa Light");

ui_pnlStatus = lv_obj_create(ui_screenMain);
lv_obj_set_height( ui_pnlStatus, 30);
lv_obj_set_width( ui_pnlStatus, lv_pct(100));
lv_obj_set_x( ui_pnlStatus, 0 );
lv_obj_set_y( ui_pnlStatus, -1 );
lv_obj_clear_flag( ui_pnlStatus, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_pnlStatus, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_lblTime = lv_label_create(ui_pnlStatus);
lv_obj_set_width( ui_lblTime, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblTime, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_lblTime, LV_ALIGN_CENTER );
lv_label_set_text(ui_lblTime,"23:42");

ui_lblIpAddress = lv_label_create(ui_pnlStatus);
lv_obj_set_width( ui_lblIpAddress, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblIpAddress, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_lblIpAddress, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_lblIpAddress,"127.0.0.1");

ui_lblMosquitto = lv_label_create(ui_pnlStatus);
lv_obj_set_width( ui_lblMosquitto, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblMosquitto, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_lblMosquitto, -50 );
lv_obj_set_y( ui_lblMosquitto, 0 );
lv_obj_set_align( ui_lblMosquitto, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_lblMosquitto,"mqtt");
lv_obj_set_style_text_font(ui_lblMosquitto, &lv_font_montserrat_10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(ui_lblMosquitto, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_outline_opa(ui_lblMosquitto, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_width(ui_lblMosquitto, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_pad(ui_lblMosquitto, 2, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_lblWifi = lv_label_create(ui_pnlStatus);
lv_obj_set_width( ui_lblWifi, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lblWifi, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_lblWifi, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_lblWifi,"WiFi");
lv_obj_set_style_text_font(ui_lblWifi, &lv_font_montserrat_10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(ui_lblWifi, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_outline_opa(ui_lblWifi, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_width(ui_lblWifi, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_pad(ui_lblWifi, 2, LV_PART_MAIN| LV_STATE_DEFAULT);

}
