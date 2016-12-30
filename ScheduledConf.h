// ScheduledConf.h

#ifndef _SCHEDULEDCONF_h
#define _SCHEDULEDCONF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MutableConf.h"

class ScheduledConf : public MutableConf {
public:
	unsigned long onFor;
	unsigned long offFor;

	ScheduledConf();
};

#endif

