// MutableConf.h

#ifndef _MUTABLECONF_h
#define _MUTABLECONF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Conf {
public:
	enum States { ON, OFF, NOT_CHANGED };
	States state;
	unsigned long holdStateFor;

	Conf();
};

#endif

