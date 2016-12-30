// UserInteraction.h

#ifndef _USERINTERACTION_h
#define _USERINTERACTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Conf.h"
#include "ScheduledConf.h"
#include "TimedConf.h"

class UserInteraction {
public:
	static void overrideOnOff(Conf* conf, unsigned long now, int action,
		unsigned long newVal);

	static void configureSchedule(ScheduledConf* conf, int action, unsigned long newVal);

	static void configureTimer(TimedConf* conf, int action, unsigned long newVal);

	static void configureSensor(Conf* conf, unsigned long now, int action,
		unsigned long newVal);
};

#endif

