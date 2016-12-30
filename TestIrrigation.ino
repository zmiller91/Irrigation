#include "ScheduledConf.h"
#include "MutableConf.h"
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
Context* m_ctx;
bool m_confReceived;
char m_serialLine[16];

void setup() {

	// This is blocking, keep it as small
	// as possible
	Serial.setTimeout(100);

	m_confReceived = false;
	m_ctx = new Context();
	m_ctx->light->onFor = 3000;
	m_ctx->light->offFor = 1000;
	m_ctx->minTemp = 300;
	m_ctx->maxTemp = 700;

	m_ctx->minWater = 500;
	m_ctx->reseviorPumpOpen = 3000;
	m_ctx->waterPumpOpen = 3000;
	m_ctx->PP1Open = 100;
	m_ctx->PP2Open = 100;
	m_ctx->PP3Open = 100;
	m_ctx->PP4Open = 100;
	m_ctx->mixerOn = 500;

	m_ctx->pollOn = 500;
	m_ctx->pollOff = 500;

	Serial.begin(9600);
	ZONE = Zone(m_ctx, "Zone 1", DP12, DP11, DP10, AI_00, AI_01, AI_02, AI_03);

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

			case Context::TEMP_SENSOR_ID:

				if (action == Context::CONF_MAX) {
					m_ctx->maxTemp = newVal;
				}
				else if (action == Context::CONF_MIN) {
					m_ctx->minTemp = newVal;
				}
			case Context::LIGHT_ID:

				if (action == Context::CONF_TIME_OFF) {
					m_ctx->light->onFor = newVal;
				}
				else if (action == Context::CONF_TIME_ON) {
					m_ctx->light->offFor = newVal;
				}

				break;

			case Context::POLL_ID:
				if (action == Context::CONF_TIME_OFF) {
					m_ctx->pollOff = newVal;
				}
				else if (action == Context::CONF_TIME_ON) {
					m_ctx->pollOn = newVal;
				}

				break;

			case Context::MOISTURE_SENSOR_ID:

				if (action == Context::CONF_MIN) {
					m_ctx->minWater = newVal;
				}

			case Context::RESEVIOR_PUMP_ID:

				if (action == Context::CONF_TIME_ON) {
					m_ctx->reseviorPumpOpen = newVal;
				}

				break;

			case Context::WATER_PUMP_ID:

				if (action == Context::CONF_TIME_ON) {
					m_ctx->waterPumpOpen = newVal;
				}

				break;

			case Context::PP1_ID:

				if (action == Context::CONF_TIME_ON) {
					m_ctx->PP1Open = newVal;
				}

				break;

			case Context::PP2_ID:

				if (action == Context::CONF_TIME_ON) {
					m_ctx->PP2Open = newVal;
				}

				break;

			case Context::PP3_ID:

				if (action == Context::CONF_TIME_ON) {
					m_ctx->PP3Open = newVal;
				}

				break;

			case Context::PP4_ID:

				if (action == Context::CONF_TIME_ON) {
					m_ctx->PP4Open = newVal;
				}

				break;

			case Context::MIXER_ID:

				if (action == Context::CONF_TIME_ON) {
					m_ctx->mixerOn = newVal;
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