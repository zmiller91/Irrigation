#include "Component.h"
#include "Sensor.h"
#include "Context.h"

Sensor::Sensor() {}

/*
    A sensor is a component with added functionality. It has
	the ability to take readings from physical components.
*/
Sensor::Sensor(int id, int analogPin):
	Component(id, -1)
{
	m_analogPin = analogPin;
	m_duration = 1000;
	m_hasAverage = false;
	m_running = false;
	m_start = 0;
	m_average = 0;
	m_numPolls = 0;
	m_sumPolls = 0;
}

bool Sensor::hasAverage() {
	return m_hasAverage;
}

/*
    Return the average reading for the most recent poll

    @return float
*/
float Sensor::getAverage()
{
	return m_average;
}

void Sensor::setup(unsigned long now) {

	// Serial.print(m_id); Serial.print(" running? "); Serial.println(m_running);

	if (!m_running) {
		m_start = now;
		m_running = true;
	}
}

void Sensor::execute(unsigned long now)
{

	if (m_running)
	{
		// http://forum.arduino.cc/index.php?topic=256921.0
		// The arduino uses a multiplexer for its inputs which means
		// sensors can influence the next sensors readings if the electrical
		// impedence is great enough. Therefore, read it twice, ignoring the first

		analogRead(m_analogPin);
		int read = analogRead(m_analogPin);
		m_sumPolls += read;
		m_numPolls += 1;
	}

	if (m_running && m_start + m_duration <= now)
	{
		m_start = now;
		m_running = false;

		m_average = m_sumPolls / m_numPolls;

		// Serial.print("ID: "); Serial.print(m_id); 
		// Serial.print(" Analog Pin: "); Serial.print(m_analogPin);
		// Serial.print(" Average: "); Serial.print(m_average);
		// Serial.print(" Reading: "); Serial.println(analogRead(m_analogPin));

		m_hasAverage = true;

		m_sumPolls = 0;
		m_numPolls = 0;

	}
}