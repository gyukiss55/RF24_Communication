//RF24_Communication.ino

#include "RF24_Streaming.h"

void setup()
{
    Serial.begin(115200);
    delay(3000);
    SetupRF24Streaming();
}

void loop()
{
    LoopRF24Streaming();

}