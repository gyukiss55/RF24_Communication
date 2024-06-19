// RF24_Receive.cpp

#include <Arduino.h>
#include <SPI.h>
//#include <printf.h>
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>

#include "RF24_Definitions.h"

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
	radio.begin();
	radio.setChannel(115);
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.openReadingPipe(1, addresses[0]);
	radio.startListening();
}

void LoopRF24_Receive()
{

	if (radio.available())
	{
		while (radio.available())
		{
			radio.read(&dataRec, sizeof(dataRec));
		}
		Serial.print("\nPackage:");
		Serial.print(dataRec.id);
		Serial.print("\n");
		Serial.println(dataRec.temperature);
		Serial.println(dataRec.text);
	}

}
