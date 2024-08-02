// RF24Data.h

#pragma once

#include <Arduino.h>
#include <string>

#include "ProgramDefinitions.h"

#if defined (_RF24_INIT_)

#define MAX_CHANNEL 4
#define DCC_COMMAND_SIZE 4


struct DccCommandType
{
	uint16_t		webId;
	uint8_t			command[DCC_COMMAND_SIZE];
};


struct package
{
	uint32_t			packetId;
	uint8_t				channelOffset;
	uint8_t				unused[3];
	DccCommandType		dccCommand[MAX_CHANNEL];
};

typedef struct package Package;

void InitPackage(Package& package);
void FillPacketData(const std::string& command);

extern Package dataSend;

extern char printBuffer[100];

#endif //  (_RF24_INIT_)
