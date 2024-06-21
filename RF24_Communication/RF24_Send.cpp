// RF24_Send.cpp

#include "Arduino.h"
#include <SPI.h>
//#include <printf.h>
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>

#include "RF24_Definitions.h"
#include "RF24_Init.h"

#include "RF24_Send.h"


struct package
{
	int id = 0;
	float temperature = 0.0;
	char  text[100] = TITLE_STR;
};


typedef struct package Package;
Package dataSend;

void SetupRF24_Send()
{
	Serial.println();
	Serial.print(TITLE_STR);
	Serial.println(" 1.0.002. SetupRF24_Send:");

	SetupRF24();
	radio.begin();
	radio.setChannel(115);
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.openWritingPipe(addresses[0]);
	delay(1000);
	Serial.print(TITLE_STR);
	Serial.println(" SetupRF24_Send:");
	digitalWrite(LED_BUILTIN, HIGH);
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
	digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
	delay(100);                      // wait for a second
	digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
	delay(900);

}