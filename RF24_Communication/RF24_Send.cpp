// RF24_Send.cpp

#include "Arduino.h"
#include <SPI.h>
//#include <printf.h>
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>

#include "RF24_Definitions.h"
#include "RF24_Init.h"
#include "RF24Data.h"
#include "BlinkLed.h"

#include "RF24_Send.h"

#if defined (_RF24_SEND_)

Package dataReceived;

const char* titleStr = TITLE_STR;

void SetupRF24_Send()
{
	Serial.println();
	Serial.print(titleStr);
	Serial.println(" 1.0.002. SetupRF24_Send:");

	SetupRF24();
	radio.begin();
	radio.setChannel(115);
#if defined (_OLD_SEND_VERSION_)
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.openWritingPipe(addresses[0]);
#else
	radio.setPALevel(RF24_PA_LOW);
	radio.setDataRate(RF24_2MBPS);
	radio.setRetries(200, 50);
	radio.openReadingPipe(1, ADDRESS_RECEIVER1);
	radio.openWritingPipe(ADDRESS_SENDER);
#if defined (_RF24_SEND_RECEIVE_NOECHO_)

#else
	radio.setAutoAck(true);
#endif // (_RF24_SEND_RECEIVE_NOECHO_)

#endif // (_OLD_SEND_VERSION_)

	radio.printDetails();
	delay(1000);
	Serial.print(titleStr);
	Serial.println(" SetupRF24_Send:");
	digitalWrite(LED_BUILTIN, HIGH);
	InitPackage(dataSend);

	String t(titleStr);

	dataSend.packetId = 1;
}

#if defined (_OLD_SEND_VERSION_)
#else
#endif //(_OLD_SEND_VERSION_)

void LoopRF24_Send()
{
	bool printEnable = false;
	static uint32_t lastTimeTick = 0;
	uint32_t currentTimeTick = millis();
	if (currentTimeTick - lastTimeTick > 2000) {
		printEnable = true;
		lastTimeTick = currentTimeTick;
	}
// Ensure we have stopped listening (even if we're not) or we won't be able to transmit
	radio.stopListening();
#if defined (_OLD_SEND_VERSION_)
	radio.write(&dataSend, sizeof(dataSend));
#else
	bool echoStatus = radio.write(&dataSend, sizeof(dataSend));
	if (printEnable) {
		if (echoStatus)
			Serial.println("TX: ACK");
		else
			Serial.println("TX: No ACK");
	}
#endif //(_OLD_SEND_VERSION_)

	if (printEnable) {
		snprintf(printBuffer, sizeof(printBuffer), "\nSent:%d. %d %d %d %d\n", dataSend.packetId, dataSend.dccCommand[0].webId, dataSend.dccCommand[1].webId, dataSend.dccCommand[2].webId, dataSend.dccCommand[3].webId);
		Serial.print(printBuffer);
	}

	dataSend.packetId = dataSend.packetId + 1;

#if defined (_OLD_SEND_VERSION_)

#else

#if defined (_RF24_SEND_RECEIVE_NOECHO_)

#else

	// Now listen for a response
	radio.startListening();

	// But we won't listen for long
	unsigned long started_waiting_at = millis();

	// Loop here until we get indication that some data is ready for us to read (or we time out)
	while (!radio.available()) {
		// Oh dear, no response received within our timescale
		if (millis() - started_waiting_at > 250) {
			if (printEnable) {
				Serial.print("TX: Got no reply");
			}
			BlinkLed(100, 2000 - 100);
			return;
		}
	}
	// Now read the data that is waiting for us in the nRF24L01's buffer
	uint32_t packetReceived = 0;
	//while (radio.available())
	{
		radio.read(&dataReceived, sizeof(dataReceived));
		packetReceived++;
	}

	if (printEnable) {
		snprintf(printBuffer, sizeof(printBuffer), "\nReceived(%d):%d. \n", packetReceived, dataReceived.packetId);
		Serial.print(printBuffer);
	}
#endif // (_RF24_SEND_RECEIVE_NOECHO_)

	BlinkLed(50, 200 - 100);

#endif // (_OLD_SEND_VERSION_)

}

#endif  //(_RF24_SEND_)
