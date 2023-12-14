
#ifndef APP_UI_H
#define APP_UI_H
#include <lvgl.h>

extern bool loadComplete;

void appui_init();
void loadingScreenIsReady( lv_event_t * e);
void changeToMainScreen( );
void setLoadingPercent( int value );
void setLoadingText(const char *val);
void setTimeText(const char *val);
void setIpText(const char *val);
void setMosquittoIcon(bool connected);
void setChartSeriesPoint(lv_chart_series_t * series, int index, int value);
void setChartSeriesPoints(lv_chart_series_t * series, lv_coord_t* values, int count);
lv_chart_series_t* getChartSeries1(lv_obj_t* chart);
lv_chart_series_t* getChartSeries2(lv_obj_t* chart);
lv_chart_series_t* getChartSeries2(lv_obj_t* chart, lv_chart_series_t* series1);
void setChartSeries1Data(lv_obj_t* chart, bool toggle);

#endif