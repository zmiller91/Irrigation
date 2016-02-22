// Sensor.h

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
	 bool m_polling;

 public:
	 Sensor();
	 Sensor(int, unsigned long, int);
	 int poll(); // returns the result of the poll
	 float getAverage();
	 void clearAverage(); 
	 void handle(unsigned long now);
};

#endif

