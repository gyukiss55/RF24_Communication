// RF24_Receive.cpp

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>

#include "RF24_Definitions.h"
#include "RF24_Init.h"
#include "RF24Data.h"

#include "BlinkLed.h"

#include "RF24_Receive.h"

#if defined (_RF24_RECEIVE_)

Package dataRec;
Package dataSend;


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
	radio.setChannel(115);

#if defined (_OLD_SEND_VERSION_)

	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.openReadingPipe(1, addresses[0]);
	radio.startListening();
#else
	radio.setPALevel(RF24_PA_LOW);
	radio.setDataRate(RF24_2MBPS);
	radio.setRetries(255, 5);
	radio.openReadingPipe(1, ADDRESS_SENDER);
	radio.openWritingPipe(ADDRESS_RECEIVER1);
	radio.startListening();
	radio.setAutoAck(true);
#endif //(_OLD_SEND_VERSION_)

	Serial.print("MOSI: ");
	Serial.println(MOSI);
	Serial.print("MISO: ");
	Serial.println(MISO);
	Serial.print(" SCK: ");
	Serial.println(SCK);
	Serial.print("  SS: ");
	Serial.println(SS);
	Serial.println();
	
	BlinkLed(50, 100);

	RF24_PrintState();

}

#if defined (_OLD_SEND_VERSION_)
#else
#endif //(_OLD_SEND_VERSION_)

void LoopRF24_Receive()
{

	if (radio.available())
	{
#if defined (_OLD_SEND_VERSION_)
		while (radio.available())
		{

			Serial.print(TITLE_STR);
			Serial.println("LoopRF24_Receive: start read");

			radio.read(&dataRec, sizeof(dataRec));
		}
#else
		uint32_t packetReceived = 0;
		//while (radio.available())
		{
			radio.read(&dataRec, sizeof(dataRec));
			packetReceived++;
		}
#endif // (_OLD_SEND_VERSION_)

		snprintf(printBuffer, sizeof(printBuffer), "\nReceived (%d):%d. %02.2f, %s, %s\n", packetReceived, dataRec.id, dataRec.temperature, dataRec.titleStr, dataRec.dataStr);
		Serial.print(printBuffer);

		if (!radio.write(&dataSend, sizeof(dataSend))) {
			Serial.println("RX: No ACK");
		}
		else {
			Serial.println("RX: ACK");
		}
		Serial.println();
		
#if defined (_OLD_SEND_VERSION_)
#else
		delay(100);
		radio.stopListening();

		//String t(titleStr);
		String t(TITLE_STR);
		dataSend.id = dataRec.id;
		dataSend.temperature = dataRec.temperature;
		strncpy(dataSend.titleStr, t.c_str(), t.length());
		String d("ABCDEFGHIJKLMN");
		strncpy(dataSend.dataStr, d.c_str(), d.length());

		if (!radio.write(&dataSend, sizeof(dataSend))) {
			Serial.println("RX: No ACK");
		}
		else {
			Serial.println("RX: ACK");
		}
		radio.startListening();
#endif // (_OLD_SEND_VERSION_)

		BlinkLed(50, 100);
	}

}

#endif // (_RF24_RECEIVE_)

