//BlinkLed.cpp

#include "Arduino.h"

#include "ProgramDefinitions.h"

#include "BlinkLed.h"


void BlinkLed(int t1, int t2)
{
	digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
	delay(t1);                      // wait for a second
	digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
	delay(t2);
}
