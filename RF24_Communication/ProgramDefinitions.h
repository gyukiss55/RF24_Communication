// ProgramDefinitions.h

#pragma once

#if defined(ESP8266)
	assert defined ESP8266 !
#elif defined(ESP32) 
#define LED_BUILTIN 2
#elif defined(RASPI) || defined(ARDUINO_PICO_MAJOR)
	//#define LED_BUILTIN 25
#elif defined(STM32F1xx)
	//#define LED_BUILTIN 13
#elif defined(STM32F4xx)
	//#define LED_BUILTIN 13
#else
	assert defined !!!! RASPI not defined
	//#define LED_BUILTIN 25
#endif
//
#define _RF24_SEND_RECEIVE_NOECHO_
//#define _RF24_STREAMING_
//#define _RF24_SEND_
#define _RF24_RECEIVE_
//#define _RF24_SCANNER_

#if defined(_RF24_STREAMING_) || \
	defined(_RF24_SEND_) || \
	defined(_RF24_RECEIVE_) || \
	defined(_RF24_SCANNER_)
#define _RF24_INIT_
#endif

//#define _MUTEX_TEST_
//#define _SEMAPHORE_TEST_
//#define _RFM8X_TXR_
