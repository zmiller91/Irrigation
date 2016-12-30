// HVAC.h

#ifndef _HVAC_h
#define _HVAC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Action.h"
#include "Sensor.h"
#include "Component.h"

class HVAC : public Action {
protected:
	Sensor* m_temperatureSensor;
	Component* m_fan;
	Component* m_heater;
	virtual void execute(unsigned long);

public:
	HVAC();
	HVAC(Context* m_ctx, Sensor* tempSensor, Component* fan, Component* heater);
};

#endif

