// ScheduledComponent.h

#ifndef _SCHEDULEDCOMPONENT_h
#define _SCHEDULEDCOMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"

class ScheduledComponent : public Component
{
protected:
	ScheduledConf* m_schedule;
	unsigned long m_delay;
	unsigned long m_baseTime;
	virtual void execute(unsigned long);

public:
	ScheduledComponent();
	ScheduledComponent(ScheduledConf*, 
		int, int, unsigned long, unsigned long);
};

#endif

