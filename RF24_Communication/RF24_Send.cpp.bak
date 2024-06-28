// RF24_Send.cpp

#include "Arduino.h"
#include <SPI.h>
//#include <printf.h>
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>

#include "RF24_Definitions.h"
#include "RF24_Init.h"
#include "RF24Data.h"

#include "RF24_Send.h"

#if defined (_RF24_SEND_)

Package dataSend;

char printBuffer[50];

void SetupRF24_Send()
{
	const char* titleStr = TITLE_STR;
	Serial.println();
	Serial.print(titleStr);
	Serial.println(" 1.0.002. SetupRF24_Send:");

	SetupRF24();
	radio.begin();
	radio.setChannel(115);
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.openWritingPipe(addresses[0]);
	delay(1000);
	Serial.print(titleStr);
	Serial.println(" SetupRF24_Send:");
	digitalWrite(LED_BUILTIN, HIGH);
	//memset(&dataSend, 0, sizeof(dataSend));
	InitData(dataSend);

	String t(titleStr);

	strncpy(dataSend.titleStr, t.c_str (), t.length());
	for (int i = 0; i < sizeof(dataSend.dataStr) - 1; ++i) {
		dataSend.dataStr[i] = i % 10 + '0';
		dataSend.dataStr[i + 1] = 0;
	}

	RF24_PrintState();

}

void LoopRF24_Send()
{
	radio.write(&dataSend, sizeof(dataSend));

	snprintf(printBuffer, sizeof(printBuffer), "\nSend:%d. %02.2f, %s, %s\n", dataSend.id, dataSend.temperature, dataSend.titleStr, dataSend.dataStr);
	Serial.print(printBuffer);
	dataSend.id = dataSend.id + 1;
	dataSend.temperature = dataSend.temperature + 0.1;
	digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
	delay(20);                      // wait for a second
	digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
	delay(80);

}

#endif
