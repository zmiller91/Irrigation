// Poll.h

#ifndef _POLL_h
#define _POLL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Action.h"
#include "Sensor.h"

class Poll : public Action {

private:
	ScheduledConf* m_schedule;
	unsigned long m_baseTime;
	Sensor* m_moisture;
	Sensor* m_temperature;
	Sensor* m_light;
	Sensor* m_humidity;
	void output(int sensor, int value);


public:
	Poll();
	Poll(Context* ctx, Sensor* moisture, 
		Sensor* temp, Sensor* light, Sensor* humidity);

	virtual void execute(unsigned long now);
};

#endif

