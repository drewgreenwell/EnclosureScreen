# Elecrow 7 Inch HMI Display Example Project - 3D Printer Enclosure

Example project for Arduino IDE Squareline Studio using the Elecrow 7 Inch ESP32 HMI Display

## Description

The [Elecrow 7" ESP HMI display](https://www.elecrow.com/esp32-display-7-inch-hmi-display-rgb-tft-lcd-touch-screen-support-lvgl.html) is an inexpensive yet surprisingly solid display. This is an example project I am working on for a 3D printer enclosure. The documentation for this board is still a moving target it seems but the company is fairly responsive. I will consolidate some of my findings here in hopes to help.

![loading screen](https://raw.githubusercontent.com/drewgreenwell/EnclosureScreen/main/docs/LoadingScreen.png)
![main screen](https://raw.githubusercontent.com/drewgreenwell/EnclosureScreen/main/docs/MainScreen.png)

## Getting Started

### Dependencies

* LovyanGFX
* lvgl - I am using the latest available (8.3.11 with this project). It is a good idea to stay close to squareline
* ESP32S3 Dev Board - Currently using latest version available (2.0.14)

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


