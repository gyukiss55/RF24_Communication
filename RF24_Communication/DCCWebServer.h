
/*
* DCCWebServer.h
*/

#pragma once

#include <Arduino.h>
#include <string>

#include "ProgramDefinitions.h"

#if (defined(ESP32) || defined(RASPI) || defined (ARDUINO_PICO_MAJOR)) && defined(_RF24_SEND_)
void SetupDCCWebServer();
void LoopDCCWebServer(std::string& command);
#endif