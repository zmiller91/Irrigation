#include "Root.h"
#include "BaseZone.h"
#include "Zone.h"

Zone::Zone(){};
Zone::Zone(Conf* conf, String name, int data, int latch, int clock, int moisture, int photo, int temp, int humidity) :

	// Construct member objects
	BaseZone(name, data, latch, clock, moisture, photo, temp, humidity),
	m_light(Conf::LIGHT_ID), 
	m_valve(Conf::SOLENOID_ID),
	m_periPump(Conf::PERI_PUMP_ID),
	m_moistureSensor(Conf::MOISTURE_SENSOR_ID, moisture),
	m_photoresistor(Conf::PHOTORESISTOR_ID, photo),
	m_tempSensor(Conf::TEMP_SENSOR_ID, temp),
	m_mixer(Conf::MIXER_ID),
	m_waterPump(Conf::PUMP_ID),
	m_phUp(Conf::PHUP_ID),
	m_phDown(Conf::PHDOWN_ID),
	m_fan(Conf::FAN_ID)
{
	m_conf = conf;

	m_moisutreAve = 1000;
	m_photoAve = 1000;
	m_tempAve = 1000;

	m_polling = false;
	m_nextPoll = 0;
	m_lastRTP = 0;

	m_isDay = false;
	m_nextDay = 0;
}

void Zone::clearRegister()
{
	for (int i = 0; i < NUM_BITS; i++)
	{
		m_bitmask[i] = 1;
	}

	putToRegister();
}

// Main function. This gets executed in loop()
void Zone::execute()
{
	unsigned long now = millis();

	// Lifecycle
	monitor(now);
	illuminate(now); 

	// Handle
	handleComponents(now);

	// Display
	mapRegister();
	putToRegister();
}

/*
	This method takes all outputs and maps them to the
	registers. 
*/
void Zone::mapRegister()
{
	m_bitmask[LIGHT_PWR] = m_light.getState();
	m_bitmask[MOISTURE_SENSOR] = m_moistureSensor.getState();
	m_bitmask[SOLENOID_PWR] = m_valve.getState();
	m_bitmask[PERI_PUMP] = m_periPump.getState();
	m_bitmask[MIXER_PWR] = m_mixer.getState();
	m_bitmask[PUMP_PWR] = m_waterPump.getState();
	m_bitmask[PHUP_PWR] = m_phUp.getState();
	m_bitmask[PHDOWN_PWR] = m_phDown.getState();
	m_bitmask[FAN_PWR] = m_fan.getState();

}

/*
    This method 'touches' each component. Basically, it
	tell's every component they should update. 

	TODO: Since every physical item inherts Component, maybe
	these should go in an array of Components, so we don't have
	to explicitly handle each component.
*/
void Zone::handleComponents(unsigned long now)
{
	m_waterPump.handle(now);
	m_periPump.handle(now);
	m_mixer.handle(now);
	m_phDown.handle(now);
	m_phUp.handle(now);
	m_mixer.handle(now);
	m_valve.handle(now);
	m_moistureSensor.handle(now);
	m_photoresistor.handle(now);
	m_tempSensor.handle(now);
	m_light.handle(now);
}

void Zone::irrigate(unsigned long now)
{
	//if (!m_watering) {  // uncomment this line when testing
	if (!isIrrigating() && m_moisutreAve < m_conf->getMinWater()) {         // comment this line when testing

		// Notify serial that irrigation is starting
		Root::notifySerial(Conf::IRRIGATE_ID, Conf::ON_OFF, 1);

		// Open the valve and turn on the pump in order to get water from
		// the resovior to the preperation container
		m_waterPump.schedule(0, m_conf->getWaterPumpOn(),now);

		// Turn the peri pump on to feed the plants
		m_periPump.schedule(m_waterPump.getScheduledOff() - now, m_conf->getPeriPumpOn(), now);

		// Turn on the mixers to mix nutrients
		m_mixer.schedule(m_periPump.getScheduledOff() - now, m_conf->getMixerOn(), now);

		// TODO: Adjust the ph
		// TODO: Schedule mixer. Will require having a queue of schedules. 

		// Open the valve to water the plants
		m_valve.schedule(m_mixer.getScheduledOff() - now, m_conf->getValveOpen(), now);
	}
}

bool Zone::isIrrigating() 
{
	return m_waterPump.getState() || m_periPump.getState() || m_mixer.getState() || m_phDown.getState() || m_phUp.getState() || m_valve.getState();
}

void Zone::monitor(unsigned long now)
{
	// start polling if a poll has taken place
	if (m_lastRTP > 0) {
		m_tempSensor.poll();
	}

	// Clear the average and control the temp if 
	// we're not polling and the last real time poll
	// was 30 seconds ago
	if (!m_polling && (now - m_lastRTP) > 3000) {
		m_tempAve = m_tempSensor.getAverage();
		controlTemp(now);
		m_tempSensor.clearAverage();
		m_lastRTP = now;
	}

	if (!m_polling && m_nextPoll < now) {

		// Nofiy serial that poll is turning on
		Root::notifySerial(Conf::POLL_ID, Conf::ON_OFF, 1);

		// Clear all average and set a schedule
		m_moistureSensor.clearAverage();
		m_photoresistor.clearAverage();
		m_tempSensor.clearAverage();

		m_moistureSensor.schedule(0, m_conf->getPollOn(), now);
		m_photoresistor.schedule(0, m_conf->getPollOn(), now);
		m_tempSensor.schedule(0, m_conf->getPollOn(), now);

		m_polling = true;

		// Only do this the first time
		if (m_lastRTP == 0) {
			m_lastRTP = now;
		}
	}

	else if (m_polling && m_moistureSensor.getState() == 0 && m_photoresistor.getState() == 0 && m_tempSensor.getState() == 0)
	{
		// Nofiy serial that poll is turning off
		Root::notifySerial(Conf::POLL_ID, Conf::ON_OFF, 0);

		m_moisutreAve = m_moistureSensor.getAverage();
		m_photoAve = m_photoresistor.getAverage();
		m_tempAve = m_tempSensor.getAverage();

		// Nofiy serial of the sensor readings
		Root::notifySerial(m_moistureSensor.getId(), Conf::POLL_RESULTS, m_moisutreAve);
		Root::notifySerial(m_photoresistor.getId(), Conf::POLL_RESULTS, m_photoAve);
		Root::notifySerial(m_tempSensor.getId(), Conf::POLL_RESULTS, m_tempAve);

		displayMoistureLEDs(m_moisutreAve);
		displayTempLEDs(m_tempAve);

		m_nextPoll = now + m_conf->getPollOff();
		m_polling = false;

		// Notify data driven function that new data is available
		irrigate(now);
		controlTemp(now);
	}
}

void Zone::illuminate(unsigned long now)
{
	if (!m_isDay && m_nextDay < now) 
	{
		// Notify serial that light is turning on
		Root::notifySerial(Conf::ILLUMINATE_ID, ON_OFF, 1);
		m_light.schedule(0, m_conf->getLightOn(), now);
		m_isDay = true;
	}

	else if (m_isDay && m_light.getState() == 0)
	{
		// Nofiy serial light is turning off
		Root::notifySerial(Conf::ILLUMINATE_ID, ON_OFF, 0);
		m_nextDay = now + m_conf->getLightOff();
		m_isDay = false;
	}
}

void Zone::controlTemp(unsigned long now)
{
	int maxTemp = m_conf->getMaxTemp();
	int minTemp = m_conf->getMinTemp();
	int curTemp = m_tempSensor.poll();

	// If the average temp, or the current temp, are greater
	// then the maximum allowed temp, then turn the fans on
	if (m_fan.getState() == 0 && (m_tempAve > maxTemp || curTemp > maxTemp)) 
	{
		m_fan.setState(1);
		Root::notifySerial(Conf::FAN_ID, Conf::ON_OFF, 1);
	}

	// If the average temp, or the current temp, are less
	// than the maximum allowed temp, then turn the fans off
	else if(m_tempAve <= minTemp || curTemp <= minTemp)
	{
		if (m_fan.getState() == 1)
		{
			Root::notifySerial(Conf::FAN_ID, Conf::ON_OFF, 0);
		}
		m_fan.setState(0);
	}
}