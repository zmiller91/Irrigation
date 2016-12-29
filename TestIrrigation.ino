#include "Zone.h"

unsigned long AI_00 = 0;
unsigned long AI_01 = 1;
unsigned long AI_02 = 2;
unsigned long AI_03 = 3;
unsigned long AI_04 = 4;

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

	// This is blocking, keep it as small
	// as possible
	Serial.setTimeout(100);

	m_confReceived = false;
	m_conf = new Conf();
	m_conf->lightOn = 3000;
	m_conf->lightOff = 1000;
	m_conf->minTemp = 300;
	m_conf->maxTemp = 700;

	m_conf->minWater = 500;
	m_conf->reseviorPumpOpen = 3000;
	m_conf->waterPumpOpen = 3000;
	m_conf->PP1Open = 100;
	m_conf->PP2Open = 100;
	m_conf->PP3Open = 100;
	m_conf->PP4Open = 100;
	m_conf->mixerOn = 500;

	m_conf->pollOn = 500;
	m_conf->pollOff = 500;

	Serial.begin(9600);
	ZONE = Zone(m_conf, "Zone 1", DP12, DP11, DP10, AI_00, AI_01, AI_02, AI_03);

	Serial.println("test");
	ZONE.allOff();
	//ZONE.test();
}

void loop() {
	//ZONE.allOn(); 
	//ZONE.allOff();
	//ZONE.ledBlink(3000);
	// ZONE.test();
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
	if (incomming.length() > 0) {
		Serial.print("Received: ");
		Serial.println(incomming); 

		char charArray[16];//as 1 char space for null is also required
		strcpy(charArray, incomming.c_str());

		char* val1 = strtok(charArray, ":");
		char* val2 = strtok(NULL, ":");
		char* val3 = strtok(NULL, ":");
		if (val1 && val2 && val3) {
			int arduinoConstant = atoi(val1);
			int action = atoi(val2);
			unsigned long newVal = strtoul(val3, NULL, 0);

			switch (arduinoConstant) {

			case Conf::TEMP_SENSOR_ID:

				if (action == Conf::CONF_MAX) {
					m_conf->maxTemp = newVal;
				}
				else if (action == Conf::CONF_MIN) {
					m_conf->minTemp = newVal;
				}
			case Conf::LIGHT_ID:

				if (action == Conf::CONF_TIME_OFF) {
					m_conf->lightOn = newVal;
				}
				else if (action == Conf::CONF_TIME_ON) {
					m_conf->lightOff = newVal;
				}

				break;

			case Conf::POLL_ID:
				if (action == Conf::CONF_TIME_OFF) {
					m_conf->pollOff = newVal;
				}
				else if (action == Conf::CONF_TIME_ON) {
					m_conf->pollOn = newVal;
				}

				break;

			case Conf::MOISTURE_SENSOR_ID:

				if (action == Conf::CONF_MIN) {
					m_conf->minWater = newVal;
				}

			case Conf::RESEVIOR_PUMP_ID:

				if (action == Conf::CONF_TIME_ON) {
					m_conf->reseviorPumpOpen = newVal;
				}

				break;

			case Conf::WATER_PUMP_ID:

				if (action == Conf::CONF_TIME_ON) {
					m_conf->waterPumpOpen = newVal;
				}

				break;

			case Conf::PP1_ID:

				if (action == Conf::CONF_TIME_ON) {
					m_conf->PP1Open = newVal;
				}

				break;

			case Conf::PP2_ID:

				if (action == Conf::CONF_TIME_ON) {
					m_conf->PP2Open = newVal;
				}

				break;

			case Conf::PP3_ID:

				if (action == Conf::CONF_TIME_ON) {
					m_conf->PP3Open = newVal;
				}

				break;

			case Conf::PP4_ID:

				if (action == Conf::CONF_TIME_ON) {
					m_conf->PP4Open = newVal;
				}

				break;

			case Conf::MIXER_ID:

				if (action == Conf::CONF_TIME_ON) {
					m_conf->mixerOn = newVal;
				}

				break;
			}
		}
		else if (val1 && atoi(val1) == -1) {
			m_confReceived = true;
		}

		//delete val1, val2, val3;
	}
//	Serial.println("done updating");
}