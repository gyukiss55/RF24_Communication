// RF24_Send.cpp

#include <Arduino.h>
#include <SPI.h>
//#include <printf.h>
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>

#include "RF24_Definitions.h"

#include "RF24_Send.h"


struct package
{
	int id = 0;
	float temperature = 0.0;
	char  text[100] = "empty";
};


typedef struct package Package;
Package dataSend;

void SetupRF24_Send()
{
	radio.begin();
	radio.setChannel(115);
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.openWritingPipe(addresses[0]);
	delay(1000);
}

void LoopRF24_Send()
{
	radio.write(&dataSend, sizeof(dataSend));

	Serial.print("\nPackage:");
	Serial.print(dataSend.id);
	Serial.print("\n");
	Serial.println(dataSend.temperature);
	Serial.println(dataSend.text);
	dataSend.id = dataSend.id + 1;
	dataSend.temperature = dataSend.temperature + 0.1;
	delay(1000);

}