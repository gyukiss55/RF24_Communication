// RF24_Receive.cpp

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>

#include "RF24_Definitions.h"
#include "RF24_Init.h"

#include "RF24_Receive.h"



struct package
{
	int id = 0;
	float temperature = 0.0;
	char  text[100] = "empty";
};


typedef struct package Package;
Package dataRec;


void SetupRF24_Receive()
{
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
		Serial.print("\n");
		Serial.println(dataRec.temperature);
		Serial.println(dataRec.text);
		digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
		delay(100);                      // wait for a second
		digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
	}

}
