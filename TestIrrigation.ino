
#include "DHTSensor.h"
#include "dht.h"
#include "limits.h"

#include "Poll.h"
#include "Illumination.h"
#include "UserInteraction.h"
#include "SensorConf.h"
#include "TimedConf.h"

#include "ScheduledConf.h"
#include "Conf.h"
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
	m_ctx->light->onFor = 0;
	m_ctx->light->offFor = 0;
	m_ctx->hvac->minimum = 0;
	m_ctx->hvac->maximum = 1025;

	m_ctx->irrigation->minimum = 1025;	
	m_ctx->reseviorPump->onFor = 0;
	m_ctx->waterPump->onFor = 0;
	m_ctx->PP_1->onFor = 0;
	m_ctx->PP_2->onFor = 0;
	m_ctx->PP_3->onFor = 0;
	m_ctx->PP_4->onFor = 0;
	m_ctx->mixer->onFor = 0;

	m_ctx->poll->onFor = 0;
	m_ctx->poll->offFor = 360000;

	Serial.begin(9600);
	ZONE = Zone(m_ctx, "Zone 1", DP12, DP11, DP10, AI_00, AI_02, DP2, DP2);

	Serial.println("Finshed setup");
	ZONE.allOff();
	//ZONE.test();
}

void loop() {
	//ZONE.allOn(); 
	//ZONE.allOff();
	//ZONE.ledBlink(3000);
	 //ZONE.test();

	unsigned long now = millis();
	update(now);
	//if (m_confReceived)
	if (true)
	{
		ZONE.execute(now);
	}
}

void update(unsigned long now) {
	String incomming = Serial.readString();
	if (incomming.length() > 0) {

		char charArray[20];//as 1 char space for null is also required
		strcpy(charArray, incomming.c_str());

		char* val1 = strtok(charArray, ":");
		char* val2 = strtok(NULL, ":");
		char* val3 = strtok(NULL, ":");
		if (val1 && val2 && val3) {
			int arduinoConstant = atoi(val1);
			int action = atoi(val2);
			unsigned long newVal = strtoul(val3, NULL, 0);

			switch (arduinoConstant) {

			case Context::HVAC_ID:
				UserInteraction::overrideOnOff(m_ctx->hvac, now, action, newVal);
				UserInteraction::configureSensor(m_ctx->hvac, action, newVal);
				break;

			case Context::ILLUMINATE_ID:
				UserInteraction::overrideOnOff(m_ctx->illumination, now, action, newVal);
				UserInteraction::configureSchedule(m_ctx->light, action, newVal);
				break;

			case Context::LIGHT_ID:
				UserInteraction::overrideOnOff(m_ctx->light, now, action, newVal);
				break;

			case Context::POLL_ID:
				UserInteraction::configureSchedule(m_ctx->poll, action, newVal);
				break;

			case Context::IRRIGATE_ID:

				if (action == Context::CONF_TOUCH) {
					UserInteraction::touch(m_ctx->irrigation);
					break;
				}

				UserInteraction::overrideOnOff(m_ctx->irrigation, now, action, newVal);
				UserInteraction::configureSensor(m_ctx->irrigation, action, newVal);
				break;

			case Context::RESEVIOR_PUMP_ID:
				UserInteraction::configureTimer(m_ctx->reseviorPump, action, newVal);
				UserInteraction::overrideOnOff(m_ctx->reseviorPump, now, action, newVal);
				break;

			case Context::WATER_PUMP_ID:
				UserInteraction::configureTimer(m_ctx->waterPump, action, newVal);
				UserInteraction::overrideOnOff(m_ctx->waterPump, now, action, newVal);
				break;

			case Context::PP1_ID:
				UserInteraction::configureTimer(m_ctx->PP_1, action, newVal);
				UserInteraction::overrideOnOff(m_ctx->PP_1, now, action, newVal);
				break;

			case Context::PP2_ID:
				UserInteraction::configureTimer(m_ctx->PP_2, action, newVal);
				UserInteraction::overrideOnOff(m_ctx->PP_2, now, action, newVal);
				break;

			case Context::PP3_ID:
				UserInteraction::configureTimer(m_ctx->PP_3, action, newVal);
				UserInteraction::overrideOnOff(m_ctx->PP_3, now, action, newVal);
				break;

			case Context::PP4_ID:
				UserInteraction::configureTimer(m_ctx->PP_4, action, newVal);
				UserInteraction::overrideOnOff(m_ctx->PP_4, now, action, newVal);
				break;

			case Context::MIXER_ID:
				UserInteraction::configureTimer(m_ctx->mixer, action, newVal);
				UserInteraction::overrideOnOff(m_ctx->mixer, now, action, newVal);
				break;

			case Context::FAN_ID:
				UserInteraction::overrideOnOff(m_ctx->fan, now, action, newVal);
				break;

			case Context::HEATER_ID:

				UserInteraction::overrideOnOff(m_ctx->heater, now, action, newVal);
				break;
				
			}
		}
		else if (val1 && atoi(val1) == -1) {
			m_confReceived = true;
		}

		Serial.print("Received: ");
		Serial.println(incomming);

		//delete val1, val2, val3;
	}
//	Serial.println("done updating");
}