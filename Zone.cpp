// 
// 
// 

#include "Zone.h"

ZoneClass::ZoneClass(){};
ZoneClass::ZoneClass(String name, int data, int latch, int clock, int moisture, int photo, int temp, int humidity, 
	unsigned long lightOn, unsigned long lightOff,
	unsigned long pollOn, unsigned long pollOff,
	unsigned long valveOn, unsigned long periPumpOn,
	unsigned long mixerOn, unsigned long pumpOn,
	unsigned long phUpOn, unsigned long phDownOn) :

	// Construct member objects
	BaseZoneClass(name, data, latch, clock, moisture, photo, temp, humidity),
	m_light("light", lightOn), // start now and turn off after a day
	m_valve("valve", valveOn), // start off and turn on after a duration
	m_periPump("peri_pump", periPumpOn), // start off and turn on after a duration
	m_moistureSensor("moisture_sensor", pollOn, moisture), // start now and turn off after a poll
	m_mixer("m_mixer", mixerOn),
	m_waterPump("m_waterPump", pumpOn),
	m_phUp("m_phUp", phUpOn),
	m_phDown("m_phDown", phDownOn)
{
	m_moisutreAve = 1000;
	m_watering = false;
	m_pauseWatering = 0;

	m_polling = false;
	m_pollOn = pollOn;
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
	m_bitmask[MIXER_PWR] = m_mixer.getState();
	m_bitmask[PUMP_PWR] = m_waterPump.getState();
	m_bitmask[PHUP_PWR] = m_phUp.getState();
	m_bitmask[PHDOWN_PWR] = m_phDown.getState();

}

void ZoneClass::irrigate(unsigned long now)
{

	// If there is too much moisture in the soil, then there
	// is no need to water.  However, we should start watering
	// if there is not enough moisture in the soil and we should
	// stop watering if all of our components have finished their 
	// actions
	if (m_pauseWatering < now)
	{
		//if (!m_watering) {  // uncomment this line when testing
		if (!m_watering && m_moisutreAve < 300) {         // comment this line when testing

			Serial.println("Turning irrigation on.");

			// Open the valve and turn on the pump in order to get water from
			// the resovior to the preperation container
			m_waterPump.schedule(0, now);

			// Turn the peri pump on to feed the plants
			m_periPump.schedule(m_waterPump.getScheduledOff() - now, now);

			// Turn on the mixers to mix nutrients
			m_mixer.schedule(m_periPump.getScheduledOff() - now, now);

			// Adjust the ph

			// Below is where the logic for choosing if the ph needs to go up or down. This
			// is set to be "random" when testing

			unsigned long phDelay = 0;
			if (now % 2 == 0)
			{
				m_phUp.schedule(m_mixer.getScheduledOff() - now, now);
				phDelay = m_phUp.getScheduledOff();
			}
			else
			{
				m_phDown.schedule(m_mixer.getScheduledOff() - now, now);
				phDelay = m_phDown.getScheduledOff();
			}

			// TODO: Schedule mixer. Will require having a queue of schedules. 

			// Open the valve to water the plants
			m_valve.schedule(phDelay - now, now);

			m_watering = true;
		}

		// maybe find a better way to do this
		else if (m_watering && m_periPump.getState() == 0 && m_valve.getState() == 0 && m_mixer.getState() == 0
			&& m_waterPump.getState() == 0 && m_phDown.getState() == 0 && m_phUp.getState() == 0)
		{
			// Becacuse sensors have an off period there is a lag between readings.  If
			// a watering happens then the moisture level of the soil will not update
			// until the sensors poll again. Because the irrigation service is triggered
			// based on the value off the average moisture of the most recent sensor poll, it will 
			// continue to trigger until the sensors polls again.  Therefore, after a watering, 
			// the irrigate service must wait until it knows the sensors have polled again

			m_pauseWatering = now + m_pollOff + m_pollOn + 1000; // 1000 for error margin
			m_watering = false;

			Serial.println("Turning irrigation off.");
		}

		m_periPump.handle(now);
		m_valve.handle(now);
		m_mixer.handle(now);
		m_waterPump.handle(now);
		m_phDown.handle(now);
		m_phUp.handle(now);
	}
}

void ZoneClass::monitor(unsigned long now)
{

	if (!m_polling && m_nextPoll < now) {

		Serial.println("Turning poll on.");

		m_moistureSensor.clearAverage();
		m_moistureSensor.schedule(0, now);
		m_polling = true;
	}

	else if (m_polling && m_moistureSensor.getState() == 0)
	{
		Serial.println("Turning poll off.");

		m_moisutreAve = m_moistureSensor.getAverage();

		Serial.print("Moisture reading: ");
		Serial.println(m_moisutreAve);

		displayMoistureLEDs(m_moisutreAve);
		m_nextPoll = now + m_pollOff;
		m_polling = false;
	}

	m_moistureSensor.handle(now);
}

void ZoneClass::illuminate(unsigned long now)
{

	if (!m_isDay && m_nextDay < now) {
		Serial.println("Turning light on.");
		m_light.schedule(0, now);
		m_isDay = true;
	}

	else if (m_isDay && m_light.getState() == 0)
	{
		Serial.println("Turning light off.");
		m_nextDay = now + m_lightOff;
		m_isDay = false;
	}

	m_light.handle(now);
}

void ZoneClass::displayMoistureLEDs(int level)
{

	// 0 is the minimum reading and 550 is the maximum reading. 
	// Dry watering should start when moisture level is 300. These
	// are all arbitrary at the moment.

	m_bitmask[MOISTURE_LED_LOW] = (0 <= level && level < 200);
	m_bitmask[MOISTURE_LED_LMED] = (200 <= level && level < 300);
	m_bitmask[MOISTURE_LED_GOOD] = (300 <= level && level < 400);
	m_bitmask[MOISTURE_LED_HMED] = (400 <= level && level < 500);
	m_bitmask[MOISTURE_LED_HIGH] = (500 <= level);
}