// RFM8_TXR.cpp

#include <Arduino.h>

#include "ProgramDefinitions.h"

#if defined (_RFM8X_TXR_)

#include <pico/stdlib.h>
#include <pico/sync.h>

#include <string>

#include "PicoSemaphore.h"
#include "RPi_Pico_TimerInterrupt.h"

#include "RFM8_TXR.h"

const int ledPin = 25;
const int txPin = 4;
const int rxPin = 16;

//RPI_PICO_Timer ITimer0(0);

// Timer interrupt handler
volatile bool txState = false;

// Pin where the digital input is connected



// Flag to indicate a new interrupt has occurred
volatile bool newChangeDetected = false;

#define RX_TIME_ARRAY_SIZE 32
volatile unsigned long rxTimeArray[RX_TIME_ARRAY_SIZE];
volatile unsigned long rxTimeArrayIndex = 0;

#define RX_DIFF_ARRAY_SIZE 32

unsigned long rxTimeArrayIndexPrev = 0;

unsigned long rxDiffArray[RX_DIFF_ARRAY_SIZE];
unsigned long rxDiffArrayIndex = 0;

pico_arduino::Semaphore semaphoreRxTimeArrayIndex (1);


#define TIMER0_INTERVAL_US        200
//#define TIMER0_DURATION_MS        5000

#define TIMER1_INTERVAL_US        1000000
//#define TIMER1_DURATION_MS        15000

// Init RPI_PICO_Timer, can use any from 0-15 pseudo-hardware timers
RPI_PICO_Timer ITimer0(0);
RPI_PICO_Timer ITimer1(1);

std::string transmitBuffer;
uint32_t transmitBufferIndex = 0;
uint8_t transmitByte = 0xAA;
uint32_t transmitBytePhase = 0;
bool oneState = true;
bool oneStateSecond = false;
bool secondHalf = false;


// Interrupt service routine
void HandleExternalInterrupt() {
	unsigned long nowTime = micros();
	//semaphoreRxTimeArrayIndex.wait();
	rxTimeArray[rxTimeArrayIndex] = nowTime;
	if (rxTimeArrayIndex < RX_TIME_ARRAY_SIZE - 1)
		rxTimeArrayIndex++;
	else
		rxTimeArrayIndex = 0;
	//semaphoreRxTimeArrayIndex.release();
}

void SetupRXPin() {
	pinMode(ledPin, OUTPUT);
	pinMode(rxPin, INPUT);

	// Attach interrupt to the input pin
	attachInterrupt(digitalPinToInterrupt(rxPin), HandleExternalInterrupt, CHANGE);
	for (uint32_t i = 0; i < RX_TIME_ARRAY_SIZE; ++i) {
		rxTimeArray[i] = 0;
	}
	for (uint32_t i = 0; i < RX_DIFF_ARRAY_SIZE; ++i) {
		rxDiffArray[i] = 0;
	}
	Serial.println("RX setup done!");

	rp2040.wdt_begin(200); // watchdog 100 milli  sec
}

void CheckRxPeriod() {
	static uint32_t timePrev = 0;
	static bool stateLed = false;

	rp2040.wdt_reset();
	//semaphoreRxTimeArrayIndex.wait();
	unsigned long nextIndex = rxTimeArrayIndex;
	//semaphoreRxTimeArrayIndex.release();
	// If a new change is detected, print the time difference
	unsigned long prevIndex = RX_TIME_ARRAY_SIZE - 1;
	if (rxTimeArrayIndexPrev > 0)
		prevIndex = rxTimeArrayIndexPrev - 1;
	unsigned long prevTime = rxTimeArray[prevIndex];
	for (uint8_t i = 0; nextIndex != rxTimeArrayIndexPrev && i < RX_TIME_ARRAY_SIZE - 1; i++) {
		unsigned long nextTime = rxTimeArray[rxTimeArrayIndexPrev];
		rxDiffArray[rxDiffArrayIndex] = nextTime - prevTime;
		rxDiffArrayIndex++;
		if (rxDiffArrayIndex >= RX_DIFF_ARRAY_SIZE)
			rxDiffArrayIndex = 0;
		prevTime = nextTime;
		rxTimeArrayIndexPrev++;
		if (rxTimeArrayIndexPrev >= RX_TIME_ARRAY_SIZE)
			rxTimeArrayIndexPrev = 0;
	}

	uint32_t timeNow = micros ();
	if (timeNow < 5000000 || timeNow - timePrev < 1000000) { // 1 sec
		return;
	}
	digitalWrite(ledPin, stateLed ? HIGH : LOW);
	stateLed = !stateLed;
	timePrev = timeNow;
	Serial.print(rxDiffArrayIndex, DEC);
	Serial.print(":");
	unsigned long j = RX_DIFF_ARRAY_SIZE - 1;
	if (rxDiffArrayIndex > 0)
		j = rxDiffArrayIndex - 1;
	for (uint32_t i = 0; i < RX_DIFF_ARRAY_SIZE; ++i) {
		Serial.print(rxDiffArray[j], DEC);
		if (j == 0)
			j = RX_DIFF_ARRAY_SIZE - 1;
		else
			j--;
		if (i < RX_DIFF_ARRAY_SIZE - 1)
			Serial.print(", ");
	}
	Serial.println();
/*
	j = RX_TIME_ARRAY_SIZE - 1;
	if (nextIndex > 0)
		j = nextIndex - 1;
	for (uint32_t i = 0; i < RX_TIME_ARRAY_SIZE; ++i) {
		Serial.print(rxTimeArray[j], DEC);
		if (j == 0)
			j = RX_TIME_ARRAY_SIZE - 1;
		else
			j--;
		if (i < RX_TIME_ARRAY_SIZE - 1)
			Serial.print(", ");
	}
*/
	Serial.println();
}

/*
std::string transmitBuffer;
uint32_t transmitBufferIndex = 0;
uint8_t transmitByte = 0xAA;
uint32_t transmitBytePhase = 0;
bool oneState = true;
bool oneStateSecond = false;
bool secondHalf = false;

*/
bool TimerHandler0(struct repeating_timer* t)
{
	(void)t;

	if (oneState) {
		if (oneStateSecond) {
			secondHalf = !secondHalf;
		}
		else {
			oneStateSecond = true;
		}
	}
	else {
		secondHalf = !secondHalf;
	}
	txState = secondHalf;;
	digitalWrite(txPin, txState);
	if (oneState && oneStateSecond && secondHalf || (!oneState && secondHalf)) {
		secondHalf = false;
		oneState = false;
		oneState = oneStateSecond;
		transmitBytePhase++;
		if (transmitBytePhase >= 9) {
			transmitBytePhase = 0;
			oneState = true; // start bit
			if (transmitBufferIndex < transmitBuffer.length() - 1)
				transmitBufferIndex++;
			else
				transmitBufferIndex = 0;
			if (transmitBufferIndex < transmitBuffer.length()) {
				transmitByte = transmitBuffer[transmitBufferIndex];
			} 
		}
		else {
			if (transmitBytePhase == 8) // stop bit
				oneState = false;
			else
				oneState = (transmitByte & (0x1 << transmitBytePhase - 1)) != 0;
		}
	}
	return true;
}

bool TimerHandler1(struct repeating_timer* t)
{
	(void)t;
	return true;
}

void SetupRFM8TX() {
	// Initialize the LED pin as an output
	pinMode(txPin, OUTPUT);

	Serial.print(F("\nStarting TimerInterruptTest on "));
	//Serial.println(BOARD_TYPE);
	//Serial.println(TIMER_INTERRUPT_VERSION);
	Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

	// Interval in microsecs
	if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_US, TimerHandler0))
	{
		Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
	}
	else
		Serial.println(F("Can't set ITimer0. Select another freq. or timer"));

	// Interval in microsecs
	//if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_US, TimerHandler1))
	//{
	//	Serial.print(F("Starting ITimer1 OK, millis() = ")); Serial.println(millis());
	//}
	//else
	//	Serial.println(F("Can't set ITimer1. Select another freq. or timer"));

    Serial.println("TX setup done!");
}

void SetupRFM8RX() {
	SetupRXPin();
}

/*
std::string transmitBuffer;
uint32_t transmitBufferIndex = 0;
uint8_t transmitByte = 0xAA;
uint32_t transmitBytePhase = 0;
bool oneState = true;
bool secondHalf = false;

*/
void LoopRFM8TX()
{
    

}

void LoopRFM8RX()
{
	CheckRxPeriod();
}

#endif
