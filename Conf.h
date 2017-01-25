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
	enum Override { ON, OFF, NOT_CHANGED };
	Override m_override;
	unsigned long m_overrideUntil;
	bool touched;

	Conf();
};

#endif

