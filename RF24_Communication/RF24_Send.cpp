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

Package dataSend;
Package dataReceived;


void SetupRF24_Send()
{
	const char* titleStr = TITLE_STR;
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
#endif // (_OLD_SEND_VERSION_)

	radio.printDetails();
	delay(1000);
	Serial.print(titleStr);
	Serial.println(" SetupRF24_Send:");
	digitalWrite(LED_BUILTIN, HIGH);
	//memset(&dataSend, 0, sizeof(dataSend));
	InitData(dataSend);

	String t(titleStr);

	strncpy(dataSend.titleStr, t.c_str(), t.length());
	for (int i = 0; i < sizeof(dataSend.dataStr) - 1; ++i) {
		dataSend.dataStr[i] = i % 10 + '0';
		dataSend.dataStr[i + 1] = 0;
	}
}

#if defined (_OLD_SEND_VERSION_)
#else
#endif //(_OLD_SEND_VERSION_)

void LoopRF24_Send()
{
	// Ensure we have stopped listening (even if we're not) or we won't be able to transmit
	radio.stopListening();
#if defined (_OLD_SEND_VERSION_)
	radio.write(&dataSend, sizeof(dataSend));
#else
	if (!radio.write(&dataSend, sizeof(dataSend)))
		Serial.println("TX: No ACK");
	else
		Serial.println("TX: ACK");
#endif //(_OLD_SEND_VERSION_)

	snprintf(printBuffer, sizeof(printBuffer), "\nSent:%d. %02.2f, %s, %s\n", dataSend.id, dataSend.temperature, dataSend.titleStr, dataSend.dataStr);
	Serial.print(printBuffer);

	dataSend.id = dataSend.id + 1;

	dataSend.temperature = dataSend.temperature + 0.1;

#if defined (_OLD_SEND_VERSION_)
#else
	// Now listen for a response
	radio.startListening();

	// But we won't listen for long
	unsigned long started_waiting_at = millis();

	// Loop here until we get indication that some data is ready for us to read (or we time out)
	while (!radio.available()) {
		// Oh dear, no response received within our timescale
		if (millis() - started_waiting_at > 250) {
			Serial.print("TX: Got no reply");
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

	snprintf(printBuffer, sizeof(printBuffer), "\nReceived(%d):%d. %02.2f, %s, %s\n", packetReceived, dataReceived.id, dataReceived.temperature, dataReceived.titleStr, dataReceived.dataStr);
	Serial.print(printBuffer);

	BlinkLed(50, 200 - 100);

#endif // (_OLD_SEND_VERSION_)

}

#endif  //(_RF24_SEND_)
