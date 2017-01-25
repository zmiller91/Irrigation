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

class Zone : public BaseZone
{
 private:

	 Context* m_ctx;

	 // Light
	 ScheduledComponent* m_light;

	 // HVAC
	 Sensor* m_temp;
	 Component* m_heater;
	 Component* m_fan;

	 // Irrigation
	 Sensor* m_moisture;
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

 protected:
	 String m_name;

 public:

	 Zone();
	 Zone(Context*, String, int, int, int, int, int, int, int);
	 void execute(unsigned long now);
	 void clearRegister();
};

#endif

