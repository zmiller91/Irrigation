// TimedConf.h

#ifndef _TIMEDCONF_h
#define _TIMEDCONF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Conf.h"

class TimedConf : public Conf {
public:
	unsigned long onFor;
	TimedConf();
};

#endif

