#ifndef _BASEZONE_h
#define _BASEZONE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class BaseZone
{
protected:
	int NUM_BITS = 24;
	int m_bitmask[24];
	void putToRegister();
	void ledOneByOne(int);
	int NUM_REGISTERS = 3;
	String m_name;

	// Each zone contains 3 daisy chained 8-bit shift registers
	// and 15 LED status lights.  The LEDs can be mapped to bits 9-23 
	// in the chained register. Bits 0-8 in the register  are available 
	// for use. These first 24 entries in the zone represent it's register. 
	// To use, set the bit value of each of these register entries 
	// to either turn on or off an action in the zone.

	int REG_01 = 0;
	int REG_02 = 1;
	int REG_03 = 2;
	int REG_04 = 3;
	int REG_05 = 4;
	int REG_06 = 5;
	int REG_07 = 6;
	int REG_08 = 7;
	int REG_09 = 8;
	int REG_10 = 9;
	int REG_11 = 10;
	int REG_12 = 11;
	int REG_13 = 12;
	int REG_14 = 13;
	int REG_15 = 14;
	int REG_16 = 15;
	int REG_17 = 16;
	int REG_18 = 17;
	int REG_19 = 18;
	int REG_20 = 10;
	int REG_21 = 20;
	int REG_22 = 21;
	int REG_23 = 22;
	int REG_24 = 23;

	// Map zone sensors to register
	int MOISTURE_SENSOR;
	int PHOTORESISTOR;
	int TEMP_SENSOR;
	int HUMIDITY_SENSOR;
	int DATA_PIN;
	int LATCH_PIN;
	int CLOCK_PIN;

public:
	BaseZone();
	BaseZone(String name, int data, int latch, int clock, int moisture, int photo, int temp, int humidity);
	void test();
	void allOn();
	void allOff();
	void ledBlink(int);
};

#endif

