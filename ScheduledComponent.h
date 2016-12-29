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
	unsigned long m_scheduledOn;
	unsigned long m_scheduledOff;
	unsigned long m_delay;
	unsigned long m_baseTime;
	virtual void execute(unsigned long);

public:
	ScheduledComponent();
	ScheduledComponent(Conf*, int, int, unsigned long, unsigned long);
	void reschedule();
};

#endif

