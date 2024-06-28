// RF24Data.cpp

#include "RF24Data.h"

#if defined (_RF24_INIT_)

void InitData(Package& package)
{
	//memset(&package, 0, sizeof(package));
	package.id = 0;
	package.temperature = 0.0;
	package.titleStr[0] = 0;
	package.dataStr[0] = 0;
}

#endif // (_RF24_INIT_)