// ScheduledConf.h

#ifndef _SCHEDULEDCONF_h
#define _SCHEDULEDCONF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Conf.h"

class ScheduledConf : public Conf {
public:
	unsigned long onFor;
	unsigned long offFor;

	ScheduledConf();
};

#endif

