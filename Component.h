// Component.h

#ifndef _COMPONENT_h
#define _COMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class ComponentClass
{
 protected:
	 int m_state;
	 int m_numUsers;
	 unsigned long m_timeOn;
	 unsigned long m_scheduledOn;
	 unsigned long m_scheduledOff;
	 unsigned long m_lastUpdate;
	 String m_name;

 public:
	ComponentClass();
	ComponentClass(String, unsigned long);
	void schedule(unsigned long, unsigned long);
	int getState();
	void setState(int);
	unsigned long getLastUpdate();
	unsigned long getScheduledOn();
	unsigned long getScheduledOff();
	void handle(unsigned long);
	String getName();
};

extern ComponentClass Component;

#endif

