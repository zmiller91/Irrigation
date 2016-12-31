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
	int NUM_REGISTERS = 2;
	int NUM_BITS = 16;
	int m_bitmask[16];

	// Create register variables for easy
	// access

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

	// Map zone sensors to register
	int MOISTURE_SENSOR;
	int PHOTORESISTOR;
	int TEMP_SENSOR;
	int HUMIDITY_SENSOR;
	int DATA_PIN;
	int LATCH_PIN;
	int CLOCK_PIN;

	String m_name;
	void putToRegister();
	void ledOneByOne(int);

public:
	BaseZone();
	BaseZone(String name, int data, int latch, int clock, int moisture, int photo, int temp, int humidity);
	void test();
	void allOn();
	void allOff();
	void ledBlink(int);
};

#endif

