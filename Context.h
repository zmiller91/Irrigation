#ifndef _CONTEXT_h
#define _CONTEXT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ScheduledConf.h"
#include "TimedConf.h"

class Context
{

public:

	// User Overrides


	// TimedComponents
	TimedConf* reseviorPump;
	TimedConf* waterPump;
	TimedConf* PP_1;
	TimedConf* PP_2;
	TimedConf* PP_3;
	TimedConf* PP_4;
	TimedConf* mixer;
	Conf* heater;
	Conf* fan;

	// ScheduledComponents
	ScheduledConf* light;

	// Sensors
	int minWater;
	int maxTemp;
	int minTemp;

	// Actions
	unsigned long pollOn;
	unsigned long pollOff;

	Context();

	enum Constants
	{
		// Arduino Id
		ARDUINO_ID = 2,

		// Serial types
		ON_OFF = 1,
		POLL_RESULTS = 2,
		ADMIN = 3,

		// Component IDs. All component IDs start with 1000
		RESEVIOR_PUMP_ID = 1000,
		WATER_PUMP_ID = 1001,
		PP1_ID = 1002,
		PP2_ID = 1003,
		PP3_ID = 1004,
		PP4_ID = 1005,
		MIXER_ID = 1006,
		LIGHT_ID = 1007,
		FAN_ID = 1008,
		HEATER_ID = 1009,

		// Action IDs. All action IDs start with 2000
		POLL_ID = 2000,
		IRRIGATE_ID = 2001,
		ILLUMINATE_ID = 2002,

		// Sensor IDs. All sensor IDs start with 3000
		MOISTURE_SENSOR_ID = 3000,
		PHOTORESISTOR_ID = 3001,
		TEMP_SENSOR_ID = 3002,

		// Admin/Debug/Other IDs.  All these IDs start with 4000

		MEM_USAGE_ID = 4000,

		// Configuration action types
		CONF_MIN = 5000,
		CONF_MAX = 5001,
		CONF_TIME_ON = 5002,
		CONF_TIME_OFF = 5003,
		OVERRIDE_ON_OFF = 5004,
		OVERRIDE_ON_FOR = 5005,
		OVERRIDE_OFF_FOR = 5006,
		OVERRIDE_SET_ACTION = 5007
	};

};

#endif
