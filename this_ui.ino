/*
  Helper methods for updating the enclosure screen ui. Most of these are just calls to ui files in src or lvlg.h
*/
#include <lvgl.h>


void thisui_init() {

}

void loadingScreenIsReady( lv_event_t * e){
  Serial.println("Loading screen is ready");
}

void changeToMainScreen( ) {
    _ui_screen_change( &ui_screenMain, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_screenMain_screen_init);
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

void setChartSeriesPoint(lv_chart_series_t * series, int index, int value){
  series->y_points[index] = value;
}

void setChartSeriesPoints(lv_chart_series_t * series, lv_coord_t* values, int count) {
  for(int i = 0; i < count - 1; i++){
    setChartSeriesPoint(series, i, values[i]);
  }
}

lv_chart_series_t* getCharSeries1(){
  lv_chart_series_t* series1  = lv_chart_get_series_next(chart, NULL);
  return series1;
}

lv_chart_series_t* getCharSeries2(){
  lv_chart_series_t* series1  = lv_chart_get_series_next(chart, NULL);
  lv_chart_series_t* series2  = lv_chart_get_series_next(chart, ser);
  return series2;
}

void setChartSeries1Data(lv_obj_t* chart, boolean toggle){

  lv_chart_series_t* ser  = getChartSeries1();
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