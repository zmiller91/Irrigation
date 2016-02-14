// Sensor.h

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"

class SensorClass: public ComponentClass
{
 protected:
	 int m_analogPin;
	 float m_numPolls;
	 float m_sumPolls;
	 bool m_polling;

 public:
	 SensorClass();
	 SensorClass(String, unsigned long, int);
	 int poll(); // returns the result of the poll
	 float getAverage();
	 void clearAverage(); // make sure we clear everything before we start polling, we only need to do this for poll periods not watering periods
	 bool isPolling();
	 void setPolling(bool);
};

extern SensorClass Sensor;

#endif

