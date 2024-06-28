// RF24_Definitions.h

#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>       // RC transceiver module libraries

#include "ProgramDefinitions.h"

#if defined (_RF24_INIT_)

#ifndef _ESP_ARDUINO_VERSION_MAJOR
#define _ESP_ARDUINO_VERSION_MAJOR
#endif

#if defined(ESP8266)
	assert defined ESP8266 !
#elif defined(ESP32) 
	#define LED_BUILTIN 2
	#define CE_PIN 4
	#define CSN_PIN 5
	#define RX_PIN 19
	#define SCK_PIN 18
	#define TX_PIN 23
	#define TITLE_STR "ESP32 "
	//assert defined ESP32 !

#elif defined(RASPI)
	#define CE_PIN 22
	#define CSN_PIN 17
	#define RX_PIN 16
	#define SCK_PIN 18
	#define TX_PIN 19
	#define TITLE_STR "Pico "
#elif defined(STM32F1xx)
	//assert defined STM32F1xx !
	#define CE_PIN PA8
  
	#define CSN_PIN PB12
	#define SCK_PIN PB13
	#define RX_PIN PB14
	#define TX_PIN PB15
	#define TITLE_STR "STM32F1"
#elif defined(STM32F4xx)
	//assert defined STM32F4xx !
	#define CE_PIN PA8
  
	#define CSN_PIN PB12
	#define SCK_PIN PB13
	#define RX_PIN PB14
	#define TX_PIN PB15
	//#define CSN_PIN PA4
	//#define SCK_PIN PA5
	//#define RX_PIN PA6
	//#define TX_PIN PA7

	#define TITLE_STR "STM32F4"
//SPIClass SPI2(TX_PIN, RX_PIN, SCK_PIN); // MOSI, MISO, SCK
// // Chip Select pin
//const int CS_PIN = PB12;
//	// Begin SPI2
//SPI2.begin();

// Define SPI2 instance
// 
//#define SPI2_MOSI PA7
//#define SPI2_MISO PA6
//#define SPI2_SCK  PA5
//#define SPI2_CS   PA4

//SPIClass SPI_2(2); // Create an SPI instance for SPI2
//SPI_2.begin(SPI2_SCK, SPI2_MISO, SPI2_MOSI, SPI2_CS);
// // Optional: Set SPI2 settings
//SPI_2.setClockDivider(SPI_CLOCK_DIV8); // Adjust as necessary
//SPI_2.setBitOrder(MSBFIRST);           // Most significant bit first
//SPI_2.setDataMode(SPI_MODE0);          // SPI mode 0

// //Define SPI3 instance
//SPIClass SPI3(PB5, PB4, PB3); // MOSI, MISO, SCK
// // Chip Select pin
//const int CS_PIN = PA4;
//	// Begin SPI3
//SPI3.begin();
#else
	#define CE_PIN 22
	#define CSN_PIN 17
	#define RX_PIN 16
	#define SCK_PIN 18
	#define TX_PIN 19
	#define TITLE_STR "Pico like "
	//assert defined RASPI !
#endif

extern RF24 radio;
extern byte addresses[][6];

#endif
