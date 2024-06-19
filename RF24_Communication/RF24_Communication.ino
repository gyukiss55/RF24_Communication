//RF24_Communication.ino

#include <Arduino.h>

//#define _RF24_STREAMING_
#define _RF24_SEND_
//#define _RF24_RECEIVE_

#if defined _RF24_STREAMING_
 #include "RF24_Streaming.h"
#else
#if defined _RF24_SEND_
 #include "RF24_Send.h"
#else
#if defined _RF24_RECEIVE_
 #include "RF24_Receive.h"
#else
#endif
#endif
#endif




void setup()
{
    Serial.begin(115200);
    delay(3000);

#if defined _RF24_STREAMING_
    SetupRF24Streaming();
#else
#if defined _RF24_SEND_
    SetupRF24_Send ();
#else
#if defined _RF24_RECEIVE_
    SetupRF24_Receive ();
#else
#endif
#endif
#endif

}

void loop()
{
#if defined _RF24_STREAMING_
    LoopRF24Streaming();
#else
#if defined _RF24_SEND_
    LoopRF24_Send ();
#else
#if defined _RF24_RECEIVE_
    LoopRF24_Receive ();
#else
#endif
#endif
#endif

}