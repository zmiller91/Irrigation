// BaseZone.h

#ifndef _BASEZONE_h
#define _BASEZONE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class BaseZoneClass
{
protected:
	int NUM_BITS = 24;
	int m_bitmask[24];
	void putToRegister();
	void ledOneByOne(int);
	void ledBlink(int);
	int NUM_REGISTERS;
	String m_name;

	// Each zone contains 3 daisy chained 8-bit shift registers
	// and 15 LED status lights.  The LEDs can be mapped to bits 9-23 
	// in the chained register. Bits 0-8 in the register  are available 
	// for use. These first 24 entries in the zone represent it's register. 
	// To use, set the bit value of each of these register entries 
	// to either turn on or off an action in the zone.

	unsigned long REG_01 = 0;
	unsigned long REG_02 = 1;
	unsigned long REG_03 = 2;
	unsigned long REG_04 = 3;
	unsigned long REG_05 = 4;
	unsigned long REG_06 = 5;
	unsigned long REG_07 = 6;
	unsigned long REG_08 = 7;
	unsigned long REG_09 = 8;

	unsigned long LED_01 = 9;
	unsigned long LED_02 = 10;
	unsigned long LED_03 = 11;
	unsigned long LED_04 = 12;
	unsigned long LED_05 = 13;
	unsigned long LED_06 = 14;
	unsigned long LED_07 = 15;
	unsigned long LED_08 = 16;
	unsigned long LED_09 = 17;
	unsigned long LED_10 = 18;
	unsigned long LED_11 = 10;
	unsigned long LED_12 = 20;
	unsigned long LED_13 = 21;
	unsigned long LED_14 = 22;
	unsigned long LED_15 = 23;

	// Variables below here are not required for basic integration.  These
	// are now application variables and are used solely for the application
	// of this irrigation system

	// Map moisture sensor leds to register
	unsigned long MOISTURE_LED_LOW = LED_01;
	unsigned long MOISTURE_LED_LMED = LED_02;
	unsigned long MOISTURE_LED_GOOD = LED_03;
	unsigned long MOISTURE_LED_HMED = LED_04;
	unsigned long MOISTURE_LED_HIGH = LED_05;

	// Map temp sensor leds to register
	long TEMP_LED_LOW = LED_06;
	long TEMP_LED_LMED = LED_07;
	long TEMP_LED_GOOD = LED_08;
	long TEMP_LED_HMED = LED_09;
	long TEMP_LED_HIGH = LED_10;

	// Map pH sensor leds to register
	unsigned long PH_LED_LOW = LED_11;
	unsigned long PH_LED_LMED = LED_12;
	unsigned long PH_LED_GOOD = LED_13;
	unsigned long PH_LED_HMED = LED_14;
	unsigned long PH_LED_HIGH = LED_15;

	// Map zone functions to register
	unsigned long MOISTURE_SENSOR_PWR = REG_01;
	unsigned long PERI_PUMP = REG_02;
	unsigned long SOLENOID_PWR = REG_03;
	unsigned long LIGHT_PWR = REG_04;

	// Map zone sensors to register
	int MOISTURE_SENSOR;
	int PHOTORESISTOR;
	int TEMP_SENSOR;
	int HUMIDITY_SENSOR;
	int DATA_PIN;
	int LATCH_PIN;
	int CLOCK_PIN;

public:
	BaseZoneClass();
	BaseZoneClass(String name, int data, int latch, int clock, int moisture, int photo, int temp, int humidity);
	void test();
};

extern BaseZoneClass BaseZone;

#endif

