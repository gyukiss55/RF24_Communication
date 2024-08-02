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

uint32_t lastId = 0;
uint32_t receivedNr = 0;
uint32_t lostNr = 0;
uint32_t lostMax = 0;

void SetupRF24_Receive()
{
	InitPackage(dataRec);

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
#if defined (_RF24_SEND_RECEIVE_NOECHO_)

#else
	radio.setAutoAck(true);
#endif // (_RF24_SEND_RECEIVE_NOECHO_)

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

		snprintf(printBuffer, sizeof(printBuffer), "\nReceived (%d):%d. %d %x %x %x %x, %d %x %x %x %x, %d %x %x %x %x, %d %x %x %x %x\n", packetReceived, dataRec.packetId, 
			dataRec.dccCommand[0].webId, dataRec.dccCommand[0].command[0], dataRec.dccCommand[0].command[1], dataRec.dccCommand[0].command[2], dataRec.dccCommand[0].command[3],
			dataRec.dccCommand[1].webId, dataRec.dccCommand[1].command[0], dataRec.dccCommand[1].command[1], dataRec.dccCommand[1].command[2], dataRec.dccCommand[1].command[3],
			dataRec.dccCommand[2].webId, dataRec.dccCommand[2].command[0], dataRec.dccCommand[2].command[1], dataRec.dccCommand[2].command[2], dataRec.dccCommand[2].command[3],
			dataRec.dccCommand[3].webId, dataRec.dccCommand[3].command[0], dataRec.dccCommand[3].command[1], dataRec.dccCommand[3].command[2], dataRec.dccCommand[3].command[3]);
		Serial.print(printBuffer);

#if defined(_RF24_SEND_RECEIVE_NOECHO_)

#else
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
		dataSend.packetId = dataRec.packetId;

		if (!radio.write(&dataSend, sizeof(dataSend))) {
			Serial.println("RX: No ACK");
		}
		else {
			Serial.println("RX: ACK");
		}
		radio.startListening();
#endif // (_OLD_SEND_VERSION_)
#endif // (_RF24_SEND_RECEIVE_NOECHO_)

		BlinkLed(50, 100);
	}

}

#endif // (_RF24_RECEIVE_)

