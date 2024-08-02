// RF24Data.cpp

#include <Arduino.h>
#include <string>

#include "ProgramDefinitions.h"

#if defined (_RF24_INIT_)

#include "RF24Data.h"

#include "DCCWebCommandParser.h"

char printBuffer[100];

Package dataSend;

void InitPackage(Package& package)
{
	memset(&package, 0, sizeof(Package));
	package.packetId = 0;
}

void FillPacketData(const std::string& commandString) 
{
    static uint16_t webID = 0;
    if (commandString.length() > 0) {
        webID++;
        if (webID == 0)
            webID++;

        Serial.print("WebCommand:");
        Serial.println(commandString.c_str());
        WebCommandParser parser (commandString);
        uint8_t channel = parser.GetChannel();
        uint8_t sizeCommand = parser.GetCommandSize();
        const uint8_t* commandByte = parser.GetCommand();
        Serial.print("ch:");
        Serial.print(channel, DEC);
        Serial.print(", size:");
        Serial.print(sizeCommand, DEC);
        Serial.print(", data:");
        for (int i = 0; i < sizeCommand; i++) {
            if (i > 0)
                Serial.print(',');
            Serial.print(sizeCommand, HEX);
        }
        Serial.println('.');

        if (channel < MAX_CHANNEL && commandByte != nullptr) {
            DccCommandType dcc;
            memset(&dcc, 0, sizeof(DccCommandType));
            dcc.webId = webID;
            for (int i = 0; i < sizeCommand && i < DCC_COMMAND_SIZE; i++)
                dcc.command[i] = commandByte[i];

            dataSend.dccCommand[channel] = dcc;
        }
    }
}

#endif // (_RF24_INIT_)