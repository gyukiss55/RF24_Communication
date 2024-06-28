// RF24_Receive.cpp

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>

#include "RF24_Definitions.h"
#include "RF24_Init.h"
#include "RF24Data.h"

#include "RF24_Receive.h"

#if defined (_RF24_RECEIVE_)

Package dataRec;
uint32_t lastId = 0;
uint32_t receivedNr = 0;
uint32_t lostNr = 0;
uint32_t lostMax = 0;


void SetupRF24_Receive()
{
	InitData(dataRec);

	Serial.println();
	Serial.print(TITLE_STR);
	Serial.println(" 1.0.002. SetupRF24_Receive:");

	SetupRF24();

	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.openReadingPipe(1, addresses[0]);
	radio.startListening();

	Serial.print("MOSI: ");
	Serial.println(MOSI);
	Serial.print("MISO: ");
	Serial.println(MISO);
	Serial.print(" SCK: ");
	Serial.println(SCK);
	Serial.print("  SS: ");
	Serial.println(SS);
	Serial.println();
	digitalWrite(LED_BUILTIN, HIGH);

	RF24_PrintState();

}

void LoopRF24_Receive()
{

	if (radio.available())
	{

		while (radio.available())
		{

			Serial.print(TITLE_STR);
			Serial.println("LoopRF24_Receive: start read");

			radio.read(&dataRec, sizeof(dataRec));
		}
		Serial.print("\nPackage:");
		Serial.print(dataRec.id);
		Serial.print(", ");
		Serial.print(dataRec.temperature);
		Serial.print(", ");
		Serial.print(dataRec.titleStr);
		Serial.print(", ");
		Serial.println(dataRec.dataStr);

		uint32_t lost = 0;
		if (lastId > 0 && dataRec.id > lastId) {
			lost = dataRec.id - lastId - 1;
			lostNr += lost;
		}
		lastId = dataRec.id;
		if (lost > lostMax)
			lostMax = lost;
		receivedNr++;
		Serial.print("\nRecNr:");
		Serial.print(receivedNr, DEC);
		Serial.print(", lostNr:");
		Serial.print(lostNr, DEC);
		Serial.print(", lostMax:");
		Serial.print(lostMax, DEC);
		if (lost > 0) {
			Serial.print(", lostNow:");
			Serial.print(lost, DEC);
		}
		Serial.println();

		digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
		delay(10);                      // wait for a second
		digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off by making the voltage LOW
	}

}

#endif

