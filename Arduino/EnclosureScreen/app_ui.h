
#ifndef APP_UI_H
#define APP_UI_H
#include <lvgl.h>

extern bool loadComplete;

void appui_setup();
void appui_loop();
void changeToMainScreen();
void changeToScreenSaverScreen();
void dismissScreenSaver();
void setLoadingPercent(int value);
void setLoadingText(const char *val);
void setTimeText(const char *val);
void setIpText(const char *val);
uint32_t getFreeMemory();
void setMosquittoState(bool connected);
void setWifiState(bool connected);
void setChartSeriesPoint(lv_chart_series_t * series, int index, int value);
void setChartSeriesPoints(lv_chart_series_t * series, lv_coord_t* values, int count);
lv_chart_series_t* getChartSeries1(lv_obj_t* chart);
lv_chart_series_t* getChartSeries2(lv_obj_t* chart);
lv_chart_series_t* getChartSeries2(lv_obj_t* chart, lv_chart_series_t* series1);
void setChartSeries1Data(lv_obj_t* chart, bool toggle);

#endif