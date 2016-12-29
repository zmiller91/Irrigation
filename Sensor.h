#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"

class Sensor: public Component
{
 protected:
	 int m_analogPin;
	 float m_numPolls;
	 float m_sumPolls;
	 float m_average;
	 bool m_running;
	 bool m_hasAverage;
	 unsigned long m_start;
	 unsigned long m_duration;
	 virtual void execute(unsigned long);

 public:
	 Sensor();
	 Sensor(Conf*, int, int);
	 bool hasAverage();
	 float getAverage();
	 virtual void setup(unsigned long);
};

#endif

