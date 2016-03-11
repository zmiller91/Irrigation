// Root.h

#ifndef _ROOT_h
#define _ROOT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// Arduino Id
static int ARDUINO_ID = 2;

// Serial types
static int ON_OFF = 1;
static int POLL_RESULTS = 2;
static int ADMIN = 3;

// Component IDs. All component IDs start with 1000
static int PUMP_ID = 1000;
static int PERI_PUMP_ID = 1001;
static int MIXER_ID = 1002;
static int PHDOWN_ID = 1003;
static int PHUP_ID = 1004;
static int SOLENOID_ID = 1005;
static int LIGHT_ID = 1006;
static int FAN_ID = 1007;

// Action IDs. All action IDs start with 2000
static int POLL_ID = 2000;
static int IRRIGATE_ID = 2001;
static int ILLUMINATE_ID = 2002;

// Sensor IDs. All sensor IDs start with 3000
static int MOISTURE_SENSOR_ID = 3000;
static int PHOTORESISTOR_ID = 3001;
static int TEMP_SENSOR_ID = 3002;

// Admin/Debug/Other IDs.  All these IDs start with 4000
static int MEM_USAGE_ID = 4000;

class Root
{
public:
	Root();
	~Root();
	static void notifySerial(int, int, int);

private:

};

#endif

