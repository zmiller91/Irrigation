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

class ZoneClass : public BaseZoneClass
{
 private:
	 ComponentClass m_light;
	 ComponentClass m_valve;
	 ComponentClass m_periPump;
	 ComponentClass m_mixer;
	 ComponentClass m_waterPump;
	 ComponentClass m_phUp;
	 ComponentClass m_phDown;

	 SensorClass m_moistureSensor;

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

	 ZoneClass();

	 ZoneClass(String, int, int, int, int, int, int, int, 
		 unsigned long, unsigned long, unsigned long, unsigned long,
		 unsigned long, unsigned long, unsigned long, unsigned long, 
		 unsigned long, unsigned long);

	 void execute();
	 void clearRegister();
};

extern ZoneClass Zone;

#endif

