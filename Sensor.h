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
	 int m_numPolls;
	 float m_sumPolls;
	 float m_average;
	 bool m_running;
	 bool m_hasAverage;
	 unsigned long m_start;
	 unsigned long m_duration;
	 virtual void execute(unsigned long);
	 virtual float read(int pin);

 public:
	 Sensor();
	 Sensor(Conf* conf, int id, int analogPin);
	 bool hasAverage();
	 float getAverage();
	 virtual void setup(unsigned long);
};

#endif

