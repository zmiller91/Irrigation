#ifndef _ZONE_h
#define _ZONE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"
#include "ScheduledComponent.h"
#include "TimedComponent.h"
#include "Sensor.h"
#include "BaseZone.h"
#include "Context.h"
#include "HVAC.h"
#include "Irrigation.h"
#include "Illumination.h"
#include "Poll.h"
#include "DHTSensor.h"

class Zone : public BaseZone
{
 private:

	 Context* m_ctx;

	 // Light
	 ScheduledComponent* m_light;

	 // HVAC
	 Component* m_heater;
	 Component* m_fan;

	 // Irrigation
	 TimedComponent* m_reseviorPump;
	 TimedComponent* m_waterPump;
	 TimedComponent* m_PP_1;
	 TimedComponent* m_PP_2;
	 TimedComponent* m_PP_3;
	 TimedComponent* m_PP_4;
	 TimedComponent* m_mixer;

	 // Actions
	 HVAC* m_hvac;
	 Irrigation* m_irrigation;
	 Illumination* m_illumination;
	 Poll* m_poll;

	 // Sensors
	 DHTSensor* m_temp;
	 Sensor* m_moisture;
	 Sensor* m_photoresistor;
	 DHTSensor* m_humidity;

 protected:
	 String m_name;

 public:

	 Zone();
	 Zone(Context*, String, int, int, int, int, int, int, int);
	 void execute(unsigned long now);
	 void clearRegister();
};

#endif

