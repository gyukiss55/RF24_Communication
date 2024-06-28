// RF24_Init.h

#pragma once

#include "ProgramDefinitions.h"

#define ADDRESS_RECEIVER1 0xB3B4B5B601
#define ADDRESS_RECEIVER2 0xB3B4B5B602
#define ADDRESS_RECEIVER3 0xB3B4B5B603
#define ADDRESS_RECEIVER4 0xB3B4B5B604
#define ADDRESS_RECEIVER5 0xB3B4B5B605
#define ADDRESS_SENDER 0xB3B4B5B609

#if defined (_RF24_INIT_)

void SetupRF24(int channel = 115);
void RF24_PrintState();

#endif
