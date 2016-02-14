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
private:
	bool m_users[5];

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
	unsigned long getScheduledOn();
	unsigned long getScheduledOff();
	void setScheduledOn(unsigned long);
	void setScheduledOff(unsigned long);
	int getState();
	void setState(int);
	unsigned long getLastUpdate();
	void use(int);
	void stopUsing(int);
	bool isUsing(int);
	int getNumUsers();
	String getName();
};

extern ComponentClass Component;

#endif

