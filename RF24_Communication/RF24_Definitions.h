// RF24_Definitions.h

#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>       // RC transceiver module libraries

#include "ProgramDefinitions.h"

#if defined (_RF24_INIT_)


/*
 * NRF24L01     Arduino_ Uno  Blue_Pill(stm32f01C)
 * ___________________________________________________
 * VCC  2 RED    |    3.3v   |      3.3v
 * GND  1 BROWN  |    GND    |      GND
 * CSN  4 YELOW  |   Pin10   | A4 NSS1   (PA4)	\
 * CE   3 ORANGE |   Pin9    | B0 digital(PB0)    |	    NB
 * SCK  5 GREEN  |   Pin13   | A5 SCK1   (PA5)	|- All these pins
 * MOSI 6 BLUE   |   Pin11   | A7 MOSI1  (PA7)	|  are 3.3v tolerant
 * MISO 7 PURPLE |   Pin12   | A6 MISO1  (PA6) 	/
 *
 *    Always use the adapter plate for 5v!
 */

#if defined(ESP8266)
	assert defined ESP8266 !
#elif defined(ESP32) 

	#define CE_PIN 4
	#define CSN_PIN 5
	#define RX_PIN 19
	#define SCK_PIN 18
	#define TX_PIN 23

	#define TITLE_STR "ESP32 "


#elif defined(RASPI) || defined (ARDUINO_PICO_MAJOR)

	#define RX_PIN 16
	#define CSN_PIN 17
	#define SCK_PIN 18
	#define TX_PIN 19
	#define CE_PIN 22

	//#define CE_PIN 14
	//#define CSN_PIN 15
	//#define TX_PIN 4
	//#define SCK_PIN 6
	//#define RX_PIN 7

	#define TITLE_STR "Pico "

	// assert defined RASPI !

#elif defined(STM32F1xx)

	#define CE_PIN PB0
	#define CSN_PIN PA4
	#define SCK_PIN PA5
	#define RX_PIN PA6
	#define TX_PIN PA7

	#define TITLE_STR "STM32F1"

	// assert defined STM32F1xx !

#elif defined(STM32F4xx)

	#define CE_PIN PB10
  
	#define CSN_PIN PB12
	#define SCK_PIN PB13
	#define RX_PIN PB14
	#define TX_PIN PB15

	#define TITLE_STR "STM32F4"

	// assert defined STM32F4xx !

#else

	assert defined else !!!!!

	//#define TITLE_STR "Undefined "

#endif

extern RF24 radio;
extern byte addresses[][6];

#endif
