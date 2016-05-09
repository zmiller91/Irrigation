// Component.h

#ifndef _COMPONENT_h
#define _COMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class Component
{
 protected:
	 int m_state;
	 unsigned long m_scheduledOn;
	 unsigned long m_scheduledOff;
	 unsigned long m_lastUpdate;
	 int m_id;

 public:
	Component();
	Component(int);
	void schedule(unsigned long, unsigned long, unsigned long);
	int getState();
	void setState(int);
	unsigned long getLastUpdate();
	unsigned long getScheduledOn();
	unsigned long getScheduledOff();
	void handle(unsigned long);
	int getId();
};


#endif

