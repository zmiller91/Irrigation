// Zone.h

#ifndef _ZONE_h
#define _ZONE_h
#include "Component.h"
#include "BaseZone.h"
#include "Sensor.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Zone : public BaseZone
{
 private:
	 Component m_light;
	 Component m_valve;
	 Component m_periPump;
	 Component m_mixer;
	 Component m_waterPump;
	 Component m_phUp;
	 Component m_phDown;

	 Sensor m_moistureSensor;

	 int m_moisutreAve;
	 bool m_watering;
	 unsigned long m_pauseWatering;

	 bool m_polling;
	 unsigned long m_pollOn;
	 unsigned long m_pollOff;
	 unsigned long m_nextPoll;

	 bool m_isDay;
	 unsigned long m_lightOff;
	 unsigned long m_nextDay;

	 void irrigate(unsigned long);
	 void monitor(unsigned long);
	 void illuminate(unsigned long);

	 void displayMoistureLEDs(int);

	 void mapRegister();

 protected:
	 String m_name;

 public:

	 Zone();

	 Zone(String, int, int, int, int, int, int, int, 
		 unsigned long, unsigned long, unsigned long, unsigned long,
		 unsigned long, unsigned long, unsigned long, unsigned long, 
		 unsigned long, unsigned long);

	 void execute();
	 void clearRegister();
};

#endif

