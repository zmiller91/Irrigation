// Conf.h

#ifndef _CONF_h
#define _CONF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// Arduino Id
const int ARDUINO_ID = 2;

// Serial types
const int ON_OFF = 1;
const int POLL_RESULTS = 2;
const int ADMIN = 3;

// Component IDs. All component IDs start with 1000
const int PUMP_ID = 1000;
const int PERI_PUMP_ID = 1001;
const int MIXER_ID = 1002;
const int PHDOWN_ID = 1003;
const int PHUP_ID = 1004;
const int SOLENOID_ID = 1005;
const int LIGHT_ID = 1006;
const int FAN_ID = 1007;

// Action IDs. All action IDs start with 2000
const int POLL_ID = 2000;
const int IRRIGATE_ID = 2001;
const int ILLUMINATE_ID = 2002;

// Sensor IDs. All sensor IDs start with 3000
const int MOISTURE_SENSOR_ID = 3000;
const int PHOTORESISTOR_ID = 3001;
const int TEMP_SENSOR_ID = 3002;

// Admin/Debug/Other IDs.  All these IDs start with 4000
const int MEM_USAGE_ID = 4000;

class Conf
{

private:
	unsigned long valveOpen;
	unsigned long periPumpOn;
	unsigned long waterPumpOn;
	unsigned long mixerOn;
	unsigned long lightOn;
	unsigned long lightOff;
	unsigned long pollOn;
	unsigned long pollOff;
	int minWater;
	int maxTemp;
	int minTemp;

public:

	Conf();
	~Conf();

	enum Constants
	{
		// Arduino Id
		ARDUINO_ID = 2,

		// Serial types
		ON_OFF = 1,
		POLL_RESULTS = 2,
		ADMIN = 3,

		// Component IDs. All component IDs start with 1000
		PUMP_ID = 1000,
		PERI_PUMP_ID = 1001,
		MIXER_ID = 1002,
		PHDOWN_ID = 1003,
		PHUP_ID = 1004,
		SOLENOID_ID = 1005,
		LIGHT_ID = 1006,
		FAN_ID = 1007,

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
		CONF_ON_OFF = 5000,
		CONF_MIN = 5001,
		CONF_MAX = 5002,
		CONF_TIME_ON = 5003,
		CONF_TIME_OFF = 5004
	};

	void setValveOpen(unsigned long);
	void setPeriPumpOn(unsigned long);
	void setWaterPumpOn(unsigned long);
	void setMixerOn(unsigned long);
	void setLightOn(unsigned long);
	void setLightOff(unsigned long);
	void setPollOn(unsigned long);
	void setPollOff(unsigned long);
	void setMinWater(int);
	void setMinTemp(int);
	void setMaxTemp(int);

	unsigned long getValveOpen();
	unsigned long getPeriPumpOn();
	unsigned long getWaterPumpOn();
	unsigned long getMixerOn();
	unsigned long getLightOn();
	unsigned long getLightOff();
	unsigned long getPollOn();
	unsigned long getPollOff();
	int getMinWater();
	int getMinTemp();
	int getMaxTemp();

private:

};

#endif
