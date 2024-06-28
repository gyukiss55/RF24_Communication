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

	radio.printDetails();

	BlinkLed(50, 100);
}

#if defined (_OLD_SEND_VERSION_)
#else
#endif //(_OLD_SEND_VERSION_)

void LoopRF24_Receive()
{

	if (radio.available())
	{
#if defined (_OLD_SEND_VERSION_)
		Serial.print(TITLE_STR);
		Serial.println("LoopRF24_Receive: start read");
		while (radio.available())
		{
			radio.read(&dataRec, sizeof(dataRec));
		}
#else
		radio.read(&dataRec, sizeof(dataRec));
#endif // (_OLD_SEND_VERSION_)

		Serial.print("\Received:");
		Serial.print(dataRec.id);
		Serial.print(", ");
		Serial.println(dataRec.temperature);
		Serial.print(", ");
		Serial.println(dataRec.titleStr);

#if defined (_OLD_SEND_VERSION_)
#else
		delay(100);
		radio.stopListening();

		//String t(titleStr);
		String t(TITLE_STR);
		dataSend.id = dataRec.id;
		dataSend.temperature = dataRec.temperature;
		strncpy(dataSend.titleStr, t.c_str(), t.length());

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

