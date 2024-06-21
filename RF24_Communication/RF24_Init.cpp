// RF24_Init.cpp

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>

#include "RF24_Definitions.h"

#include "RF24_Init.h"

#if defined ARDUINO_PICO_VERSION_MAJOR
//SPISettings spisettings(10000000, MSBFIRST, SPI_MODE0);
	SPISettings spisettings(10000000, MSBFIRST, SPI_MODE0);
#elif defined(STM32F4xx)
	SPIClass * spi2 = nullptr;
#elif defined(ESP32)
	SPIClass* vspi = NULL;
#else
#endif

void SetupRF24(int channel)
{

#if defined(ESP32) 
	Serial.println("Setup ESP32 SPI:");
	vspi = new SPIClass(VSPI);
	vspi->begin();
	radio.begin(vspi);
#elif defined (ARDUINO_ARCH_RP2040)
	Serial.println("Setup RP2040 SPI:");
	SPI.setRX(RX_PIN);
	SPI.setCS(CSN_PIN);
	SPI.setSCK(SCK_PIN);
	SPI.setTX(TX_PIN);
	SPI.begin(true);
	radio.begin(&SPI);
#elif defined (STM32F4xx)
	Serial.println("Setup STM32F4 SPI:");
	spi2->begin();
	spi2->setClockDivider(SPI_CLOCK_DIV8); // Adjust as necessary
	spi2->setBitOrder(MSBFIRST);           // Most significant bit first
	spi2->setDataMode(SPI_MODE0);          // SPI mode 0
	radio.begin(spi2);
#else
	Serial.println("Setup \'Pico like\' SPI:");
	spi2 = new SPIClass(TX_PIN, RX_PIN, SCK_PIN);
	SPI.setRX(RX_PIN);
	SPI.setCS(CSN_PIN);
	SPI.setSCK(SCK_PIN);
	SPI.setTX(TX_PIN);
	SPI.begin(true);
	radio.begin(&SPI);
#endif

	radio.setChannel(channel);
}
