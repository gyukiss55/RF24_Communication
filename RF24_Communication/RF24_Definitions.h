// RF24_Definitions.h

#pragma once

#if defined ESP_ARDUINO_VERSION_MAJOR
#define CE_PIN 4
#define CSN_PIN 5
#define TITLE_STR "ESP32"
#endif

#if defined ARDUINO_PICO_VERSION_MAJOR
#define CE_PIN 22
#define CSN_PIN 17
#define TITLE_STR "Pico"
#else
  //#define CE_PIN 7
  //#define CSN_PIN 8 
#define CE_PIN 4
#define CSN_PIN 5 
#define TITLE_STR "ESP32 like"
#endif

extern RF24 radio;
extern byte addresses[][6];
