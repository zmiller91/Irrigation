// Serial.h

#ifndef _SERIAL_h
#define _SERIAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class CustomSerial
{
protected:

public:
	CustomSerial();
	static void out(int, int);
};

#endif

