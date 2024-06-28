// RF24Data.h

#pragma once

#include <Arduino.h>

#include "ProgramDefinitions.h"

#if defined (_RF24_INIT_)

struct package
{
	uint32_t	id;
	float		temperature;
	char		titleStr[8];
	char		dataStr[16];
};


typedef struct package Package;

void InitData(Package& package);

extern char printBuffer[100];

#endif //  (_RF24_INIT_)
