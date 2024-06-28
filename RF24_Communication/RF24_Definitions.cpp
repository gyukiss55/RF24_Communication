// RF24_Definitions.cpp
#include <Arduino.h>
#include <SPI.h>
#include <printf.h>
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>

#include "RF24_Definitions.h"

#if defined (_RF24_INIT_)

// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

byte addresses[][6] = { "0" };

#endif //(_RF24_INIT_)
