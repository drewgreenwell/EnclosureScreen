/*
  Helper methods for updating the enclosure screen ui. Most of these are just calls to ui files in src or lvlg.h
*/
#include "app_settings.h"
#include "app_ui.h"
#include <Arduino.h>
#include "src/squareline/ui.h"
#include "src/squareline/ui_helpers.h"


bool loadComplete = false;

long screenSaverDelay = SCREENSAVER_TIMEOUT;
long lastScreenSaverTick = 0;
bool screenSaverActive = false;

lv_chart_series_t* enderSeries1;
lv_chart_series_t* enderSeries2;
// testing dynamic chart updating
long chartUpdateInterval = 5000;
long lastChartTick = 0;
bool swapChartData = false;



void appui_setup() {
  enderSeries1 = getChartSeries1(ui_chartEnder);
  enderSeries2 = getChartSeries2(ui_chartEnder, enderSeries1);
}

void appui_loop() {
 long now = millis();
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

void changeToMainScreen( ) {
   _ui_screen_change( &ui_screenMain, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_screenMain_screen_init);
   // getFreeMemory();
}

void changeToScreenSaverScreen() {
  _ui_screen_change( &ui_screenScreenSaver, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_screenScreenSaver_screen_init);
  // getFreeMemory();
}

void dismissScreenSaver() {
  // reset the screensaver idle time
  lastScreenSaverTick = millis();
  // if the screensaver is visible swap back to main screen
  // todo pop from a stack or prev_screen variable
  if(screenSaverActive) {
    screenSaverActive = false;
    changeToMainScreen();
  }
}

uint32_t getFreeMemory() {
  uint32_t mem = esp_get_free_heap_size();
  Serial.print("Free Memory ");
  Serial.print(mem);
  Serial.println(" bytes");
  return mem;
}

void setLoadingPercent( int value ) {
  lv_bar_set_value(ui_barLoading,value,LV_ANIM_ON);
  if(value == 100 && !loadComplete) {
    loadComplete = true;
    changeToMainScreen();
  }
}

void setLoadingText(const char *val) {
   lv_label_set_text(ui_lblLoading, val);
}

void setTimeText(const char *val) {
   lv_label_set_text(ui_lblTime, val);
}

void setIpText(const char *val) {
   lv_label_set_text(ui_lblIpAddress, val);
}

void setMosquittoState(bool connected) {
  _ui_state_modify(ui_imgMosquitto, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
}

void setWifiState(bool connected) {
  _ui_state_modify(ui_imgWifi, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
}

void setChartSeriesPoint(lv_chart_series_t * series, int index, int value){
  series->y_points[index] = value;
}

void setChartSeriesPoints(lv_chart_series_t * series, lv_coord_t* values, int count) {
  for(int i = 0; i < count - 1; i++){
    setChartSeriesPoint(series, i, values[i]);
  }
}

lv_chart_series_t* getChartSeries1(lv_obj_t* chart){
  lv_chart_series_t* series1  = lv_chart_get_series_next(chart, NULL);
  return series1;
}

lv_chart_series_t* getChartSeries2(lv_obj_t* chart){
  return getChartSeries2(chart, NULL);
}

lv_chart_series_t* getChartSeries2(lv_obj_t* chart, lv_chart_series_t* series1){
  if(series1 == NULL) {
    series1 = lv_chart_get_series_next(chart, NULL);
  }
  lv_chart_series_t* series2  = lv_chart_get_series_next(chart, series1);
  return series2;
}

void setChartSeries1Data(lv_obj_t* chart, bool toggle){

  lv_chart_series_t* ser  = getChartSeries1(chart);
  lv_coord_t value_array1[] = { 80,90,70,66,50,65,79,80,100,95 };
  lv_coord_t value_array2[] = { 70,60,45,25,80,100,70,50,80,110 };
  for(int i = 0; i < 10; i++){
    if(toggle) {
      setChartSeriesPoint(ser, i, value_array1[i]);
    } else {
      setChartSeriesPoint(ser, i, value_array2[i]);
    }
  }
  lv_chart_refresh(chart);
}

/*void setChartSeries2Data(lv_obj_t * chart, lv_coord_t[] series){
    // lv_chart_set_ext_y_array(chart, ui_chartEnder_series_2, series);
    lv_chart_set_points(chart, ui_chartEnder_series_2, series).
    lv_chart_refresh(chart);
}*/
