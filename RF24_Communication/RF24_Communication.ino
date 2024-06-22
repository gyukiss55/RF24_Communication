//RF24_Communication.ino

#include "Arduino.h"
#include "RF24_Definitions.h"

//#define _RF24_STREAMING_
//#define _RF24_SEND_
#define _RF24_RECEIVE_
//#define _RF24_SCANNER_

#if defined _RF24_STREAMING_
 #include "RF24_Streaming.h"
#elif defined _RF24_SEND_
 #include "RF24_Send.h"
#elif defined _RF24_RECEIVE_
 #include "RF24_Receive.h"
#elif defined _RF24_SCANNER_
 #include "RF24_Scanner.h"
#else
#endif

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.begin(115200);
    delay(3000);
    Serial.println(TITLE_STR);
    Serial.print("MOSI: ");
    Serial.println(MOSI);
    Serial.print("MISO: ");
    Serial.println(MISO);
    Serial.print(" SCK: ");
    Serial.println(SCK);
    Serial.print("  SS: ");
    Serial.println(SS);
    Serial.println();
    delay(5000);
#if defined _RF24_STREAMING_
    SetupRF24Streaming();
#elif defined _RF24_SEND_
    SetupRF24_Send ();
#elif defined _RF24_RECEIVE_
    SetupRF24_Receive ();
#elif defined _RF24_SCANNER_
    SetupRF24Scanner();
#else
#endif

}

void loop()
{
#if defined (_RF24_STREAMING_)
    LoopRF24Streaming();
#elif defined (_RF24_SEND_)
    LoopRF24_Send ();
#elif defined (_RF24_RECEIVE_)
    LoopRF24_Receive ();
#elif defined _RF24_SCANNER_
    LoopRF24Scanner();
#else
#endif

}