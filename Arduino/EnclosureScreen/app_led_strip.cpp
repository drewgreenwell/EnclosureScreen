
#include "app_settings.h"
#include "app_led_strip.h"
#include <Adafruit_NeoPixel.h>

// led strips
#define LED_PIN 38
#define LED_LEN 20

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED_LEN,LED_PIN, NEO_GRB + NEO_KHZ800);

int r = 255;
int g = 0;
int b = 0;
long ledDelayInterval = 100;
long ledLastTick = 0;
int ledIndex = 0;

void loop_led_strip () {
  led_animation_loop();
}

void led_animation_loop() {
  long now = millis();
  if(ledLastTick = 0 || now - ledLastTick > ledDelayInterval) {
      pixels.setPixelColor(ledIndex, pixels.Color(r,b,g));
      pixels.show();
      ledIndex += 1;
      ledLastTick = now;
      if(ledIndex > LED_LEN - 1){
        ledIndex = 0;
        if(r == 255){
          r = 0;
          g = 255;
        } else {
          r = 255;
          g = 0;
        }
      }
  }
}