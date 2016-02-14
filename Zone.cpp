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

	// Lifecycle
	monitor(now);
	illuminate(now); 
	irrigate(now);

	// Display
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

void ZoneClass::irrigate(unsigned long now)
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

	m_periPump.handle(now);
	m_valve.handle(now);
}

void ZoneClass::monitor(unsigned long now)
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

	m_moistureSensor.handle(now);
}

void ZoneClass::illuminate(unsigned long now)
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

	m_light.handle(now);
}