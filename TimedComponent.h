// TimedComponent.h

#ifndef _TIMEDCOMPONENT_h
#define _TIMEDCOMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"

class TimedComponent : public Component
{

protected:
	bool m_running;
	unsigned long m_start;
	unsigned long m_delay;
	unsigned long m_duration;
	void clear();
	virtual void execute(unsigned long);

public:
	TimedComponent();
	TimedComponent(Conf*, int, int);
	void turnOn(unsigned long now, unsigned long duration, 
		unsigned long delay);
};

#endif

