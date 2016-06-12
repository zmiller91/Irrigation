
#include "MemoryFree.h"
#include "Root.h"
#include "Component.h"
#include "Sensor.h"
#include "BaseZone.h"
#include "Zone.h"

unsigned long AI_00 = 0;
unsigned long AI_01 = 1;
unsigned long AI_02 = 2;
unsigned long AI_03 = 3;
unsigned long AI_04 = 4;
unsigned long AI_05 = 5;

// Digitial Pens
unsigned long DP2 = 2;
unsigned long DP3 = 3;
unsigned long DP4 = 4;
unsigned long DP5 = 5;
unsigned long DP6 = 6;
unsigned long DP7 = 7;
unsigned long DP8 = 8;
unsigned long DP9 = 9;
unsigned long DP10 = 10;
unsigned long DP11 = 11;
unsigned long DP12 = 12;
unsigned long DP13 = 13;

Zone ZONE;
Conf* m_conf;
bool m_confReceived;
char m_serialLine[16];

void setup() {

	Serial.setTimeout(250);

	m_confReceived = false;
	m_conf = new Conf();
	m_conf->setLightOn(43200000);
	m_conf->setLightOff(43200000);
	m_conf->setPollOn(500);
	m_conf->setPollOff(500);
	m_conf->setValveOpen(1000);
	m_conf->setPeriPumpOn(1000);
	m_conf->setWaterPumpOn(0);
	m_conf->setMixerOn(0);
	m_conf->setMinTemp(0);
	m_conf->setMaxTemp(10000);
	m_conf->setMinWater(10000);

	ZONE = Zone(m_conf, "Zone 1", DP12, DP11, DP10, AI_00, AI_02, AI_01, AI_03);

	Serial.begin(9600);
	Serial.println("test");
	ZONE.allOff();
	//ZONE.test();
}

void loop() {
	//ZONE.allOn(); 
	//ZONE.allOff();
	//ZONE.ledBlink(3000);
	//ZONE.test();
	update();
	//if (m_confReceived)
	if (true)
	{
		ZONE.execute();
	}
}

void update() {
//	Serial.println("updating");
	String incomming = Serial.readString();
	if (incomming.length() > 0)
	{
		char charArray[16];//as 1 char space for null is also required
		strcpy(charArray, incomming.c_str());

		char* val1 = strtok(charArray, ":");
		char* val2 = strtok(NULL, ":"); // off = 0, on = 1, min = 2, max = 3
		char* val3 = strtok(NULL, ":");
		if (val1 && val2 && val3)
		{
			int arduinoConstant = atoi(val1);
			int action = atoi(val2);
			Serial.println(val1);
			Serial.println(val2);
			unsigned long newVal = strtoul(val3, NULL, 0);

			switch (arduinoConstant)
			{
			case Conf::LIGHT_ID:

				if (action == Conf::CONF_TIME_OFF)
				{
					m_conf->setLightOff(newVal);
				}
				else if (action == Conf::CONF_TIME_ON)
				{
					m_conf->setLightOn(newVal);
				}

				break;

			case Conf::POLL_ID:
				if (action == Conf::CONF_TIME_OFF)
				{
					m_conf->setPollOff(newVal);
				}
				else if (action == Conf::CONF_TIME_ON)
				{
					m_conf->setPollOn(newVal);
				}

				break;

			case Conf::SOLENOID_ID:

				if (action == Conf::CONF_TIME_ON)
				{
					m_conf->setValveOpen(newVal);
				}

				break;

			case Conf::PERI_PUMP_ID:

				if (action == Conf::CONF_TIME_ON)
				{
					m_conf->setPeriPumpOn(newVal);
				}

				break;

			case Conf::PUMP_ID:

				if (action == Conf::CONF_TIME_ON)
				{
					m_conf->setWaterPumpOn(newVal);
				}

				break;

			case Conf::MIXER_ID:

				if (action == Conf::CONF_TIME_ON)
				{
					m_conf->setMixerOn(newVal);
				}

				break;
			}
		}
		else if (val1 && atoi(val1) == -1)
		{
			m_confReceived = true;
		}

		//delete val1, val2, val3;
	}
//	Serial.println("done updating");
}