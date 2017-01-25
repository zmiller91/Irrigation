// Illumination.h

#ifndef _ILLUMINATION_h
#define _ILLUMINATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Action.h"
#include "ScheduledComponent.h"
#include "Context.h"

class Illumination : public Action {

private:
	ScheduledComponent* m_light;

public:
	Illumination();
	Illumination(Context* ctx, ScheduledComponent* light);
	virtual void turnOff();
};

#endif

