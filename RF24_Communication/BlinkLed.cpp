//BlinkLed.cpp

#include "Arduino.h"

#include "ProgramDefinitions.h"

#include "BlinkLed.h"


void BlinkLed(int t1, int t2)
{
#if defined(STM32F1xx) || defined(STM32F4xx)
	digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
#else
	digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
#endif

	delay(t1);                      // wait for a second

#if defined(STM32F1xx) || defined(STM32F4xx)
	digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
#else
	digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
#endif

	delay(t2);
}
