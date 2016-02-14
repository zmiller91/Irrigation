// 
// 
// 

#include "Zone.h"

ZoneClass::ZoneClass(){};
ZoneClass::ZoneClass(String name, int data, int latch, int clock, int moisture, int photo, int temp, int humidity, 
	unsigned long lightOn, unsigned long lightOff,
	unsigned long pollOn, unsigned long pollOff,
	unsigned long valveOn, unsigned long periPumpOn) :

	// Construct member objects
	BaseZoneClass(name, data, latch, clock, moisture, photo, temp, humidity),
	m_light("light", lightOn), // start now and turn off after a day
	m_valve("valve", valveOn), // start off and turn on after a duration
	m_periPump("peri_pump", periPumpOn), // start off and turn on after a duration
	m_moistureSensor("moisture_sensor", pollOn, moisture) // start now and turn off after a poll
{
	m_moisutreAve = 1000;
	m_watering = false;

	m_polling = false;
	m_pollOff = pollOff;
	m_nextPoll = millis();

	m_isDay = false;
	m_lightOff = lightOff;
	m_nextDay = millis();
}

void ZoneClass::clearRegister()
{
	for (int i = 0; i < NUM_BITS; i++)
	{
		m_bitmask[i] = 1;
	}

	putToRegister();
}

// Main function. This gets executed in loop()
void ZoneClass::execute()
{
	unsigned long now = millis();
	handlePollTest(now);
	handleLightTest(now); 
	handleWTest(now);
	mapRegister();
	putToRegister();
}

/*
	This method takes all outputs and maps them to the
	registers. 
*/
void ZoneClass::mapRegister()
{
	m_bitmask[LIGHT_PWR] = m_light.getState();
	m_bitmask[MOISTURE_SENSOR] = m_moistureSensor.getState();
	m_bitmask[SOLENOID_PWR] = m_valve.getState();
	m_bitmask[PERI_PUMP] = m_periPump.getState();
}


/**
	This method is responsible for scheduling the light. If
	it sees that there has been no update, it will schedule
	the light to turn on immediately and finish when the day
	is over.  From there, the normal schedule is executed.
*/
void ZoneClass::handleLight(unsigned long now)
{
	if (m_light.getScheduledOn() <= now && now < m_light.getScheduledOff())
	{
		m_light.setState(1);
	}

	else if (m_light.getState() == 1)
	{
		m_light.setState(0);
	}

}

void ZoneClass::handlePoll(unsigned long now)
{
	if (m_moistureSensor.getScheduledOn() <= now && now < m_moistureSensor.getScheduledOff())
	{
		m_moistureSensor.setState(1);
		m_moistureSensor.poll();
	}

	else if (m_moistureSensor.getState() == 1)
	{
		m_moistureSensor.setState(0);
	}
}

void ZoneClass::handleWater(unsigned long now)
{
	if (m_valve.getScheduledOn() <= now && now < m_valve.getScheduledOff())
	{
		m_valve.setState(1);
		Serial.println("Valve opening.");
	}

	else if (m_valve.getState() == 1)
	{
		m_valve.setState(0);
	}
}

void ZoneClass::handlePeriPump(unsigned long now)
{
	if (m_periPump.getScheduledOn() <= now && now < m_periPump.getScheduledOff())
	{
		m_periPump.setState(1);
		Serial.println("Peri pump On.");
	}

	else if (m_periPump.getState() == 1)
	{
		m_periPump.setState(0);
	}
}

void ZoneClass::handleWTest(unsigned long now)
{

	// If there is too much moisture in the soil, then there
	// is no need to water.  However, we should start watering
	// if there is not enough moisture in the soil and we should
	// stop watering if all of our components have finished their 
	// actions

	if (!m_watering && m_moisutreAve < 300){	
		
		m_periPump.schedule(0, now);
		m_valve.schedule(m_periPump.getScheduledOff() - now, now);
		m_watering = true;
	}

	else if (m_watering && m_periPump.getState() == 0 && m_valve.getState() == 0)
	{
		m_watering = false;
	}

	handlePeriPump(now);
	handleWater(now);
}

void ZoneClass::handlePollTest(unsigned long now)
{

	if (!m_polling && m_nextPoll < now) {

		m_moistureSensor.clearAverage();
		m_moistureSensor.schedule(0, now);
		m_polling = true;
	}

	else if (m_polling && m_moistureSensor.getState() == 0)
	{
		m_moisutreAve = m_moistureSensor.getAverage();
		m_nextPoll = now + m_pollOff;
		m_polling = false;
	}

	handlePoll(now);
}

void ZoneClass::handleLightTest(unsigned long now)
{

	if (!m_isDay && m_nextDay < now) {

		m_light.schedule(0, now);
		m_isDay = true;
	}

	else if (m_polling && m_light.getState() == 0)
	{
		m_nextDay = now + m_lightOff;
		m_isDay = false;
	}

	handleLight(now);
}