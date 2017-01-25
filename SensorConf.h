// SensorConf.h

#ifndef _SENSORCONF_h
#define _SENSORCONF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Conf.h"

class SensorConf : public Conf {
public:
	int minimum;
	int maximum;
	SensorConf();
};

#endif

