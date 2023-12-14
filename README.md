# Elecrow 7 Inch HMI Display Example Project - 3D Printer Enclosure

Example project for Arduino IDE Squareline Studio using the Elecrow 7 Inch ESP32 HMI Display

## Description

The [Elecrow 7" ESP HMI display](https://www.elecrow.com/esp32-display-7-inch-hmi-display-rgb-tft-lcd-touch-screen-support-lvgl.html) is an inexpensive yet surprisingly solid display. This is an example project I am working on for a 3D printer enclosure. The documentation for this board is still a moving target it seems but the company is fairly responsive. I will consolidate some of my findings here in hopes to help.

This repository contains a basic scaffolding to run a UI designed in SquareLine studio on the Elecrow HMI display. The squareline UI is exported to the src/squareline folder and referenced from there in the project. 

## In Progress

This is early in dev but I plan to iterate on UI and will be incorporating more of the available components of the dispplay; e.g. SD functionality to store values from the MQTT broker for charting and the bluetooth sensor for presence detection to disable a screensaver view.

![loading screen](https://raw.githubusercontent.com/drewgreenwell/EnclosureScreen/main/docs/LoadingScreen.png)
![main screen](https://raw.githubusercontent.com/drewgreenwell/EnclosureScreen/main/docs/MainScreen.png)

## Getting Started

### Dependencies

* LovyanGFX
* lvgl - I am using the latest available (8.3.11 with this project). It is a good idea to stay close to squareline
* ESP32S3 Dev Board - Currently using latest version available (2.0.14)
* These dependencies can be disabled by adjusting the #define statements at the top of the sketch
    * PubSubClient, ESP32Ping - For MQTT
    * NTPClient, WiFiUdp - For Time
    * Adafruit_NeoPixel - for led strip functionality

### Installing

I've found these settings work best with this display in Arduino IDE

* USB CDC On Boot: Disabled
* CPU Frequency: 240MHz (WiFi)
* Core Debug Level: None
* USB DFU On Boot: Disabled
* Events Run On: Core 1
* Flash mode: QIO 80MHz
* Arduino Runs on: Core 1
* USB firmware MSC On Boot: Disabled
* Partition Scheme: Hude APP (3MB No OTA/1MB SPIFFS)
* PSRAM: OPI PSRAM
* Upload Mode: UART0 / Hardware CDC
* Upload Speed 460800
* USB Mode: Hardware CDC and JTAG


### Helpful References

#### GPIO Ref
![GPIO-D](https://raw.githubusercontent.com/drewgreenwell/EnclosureScreen/main/docs/gpio.png)
https://forum.elecrow.com/discussion/524/elecrow-5-inch-esp32-board-external-buttons-via-gpio-and-uart0-ports

#### Outer Dimemnsions
![CAD](https://raw.githubusercontent.com/drewgreenwell/EnclosureScreen/main/docs/7inch-hmi-dimensions.png)
https://www.elecrow.com/download/product/ESP32_Display/7.0inch/7.0inch_HMI_Outline_Dimensions.pdf

#### Links
Wiki - https://www.elecrow.com/wiki/index.php?title=ESP32_Display_7.0-inch_HMI_Arduino_Tutorial
Elecrow Squareline Tutorial - https://www.elecrow.com/blog/create-a-stunning-ui-with-squareline-studio-for-esp32-display-lvgl-tutorial.html

