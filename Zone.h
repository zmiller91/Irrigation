#ifndef _ZONE_h
#define _ZONE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Component.h"
#include "Sensor.h"
#include "BaseZone.h"
#include "Conf.h"


class Zone : public BaseZone
{
 private:
	 Conf* m_conf;
	 
	 Component m_light;
	 Component m_valve;
	 Component m_periPump;
	 Component m_mixer;
	 Component m_waterPump;
	 Component m_phUp;
	 Component m_phDown;
	 Component m_fan;

	 Sensor m_moistureSensor;
	 Sensor m_photoresistor;
	 Sensor m_tempSensor;

	 int m_moisutreAve;
	 int m_photoAve;
	 int m_tempAve;

	 bool m_polling;
	 unsigned long m_nextPoll;
	 unsigned long m_lastRTP; //RTP = real time poll

	 bool m_isDay;
	 unsigned long m_nextDay;

	 bool isIrrigating();
	 void irrigate(unsigned long);
	 void controlTemp(unsigned long);
	 void monitor(unsigned long);
	 void illuminate(unsigned long);
	 void handleComponents(unsigned long);

	 void displayMoistureLEDs(int);
	 void displayTempLEDs(int);

	 void mapRegister();

 protected:
	 String m_name;

 public:

	 Zone();

	 Zone(Conf*, String, int, int, int, int, int, int, int);

	 void execute();
	 void clearRegister();
};

#endif

