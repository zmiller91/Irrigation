// Irrigation.h

#ifndef _IRRIGATION_h
#define _IRRIGATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Action.h"
#include "Context.h"
#include "TimedComponent.h"
#include "Sensor.h"
#include "SensorConf.h"

class Irrigation : public Action {

protected:
	Sensor* m_moistureSensor;
	TimedComponent* m_reseviorPump;
	TimedComponent* m_waterPump;
	TimedComponent* m_PP_1;
	TimedComponent* m_PP_2;
	TimedComponent* m_PP_3;
	TimedComponent* m_PP_4;
	TimedComponent* m_mixer;
	unsigned long m_pauseDuration;
	unsigned long m_pauseUntil;

	void execute(unsigned long);
	bool running(TimedComponent* components[], int size);

public:
	Irrigation();
	Irrigation(Context* ctx, Sensor* moistureSensor, TimedComponent* reseviorPump,
		TimedComponent* waterPump, TimedComponent* PP_1, TimedComponent* PP_2,
		TimedComponent* PP_3, TimedComponent* PP_4, TimedComponent* mixer);
	virtual void turnOff();
};

#endif