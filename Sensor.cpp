// 
// 
// 

#include "Sensor.h"

Sensor::Sensor() {};
Sensor::Sensor(int id, unsigned long scheduledOn, int analogPin):

	// Construct super class
	Component(id, scheduledOn)
{
	m_analogPin = analogPin;
	m_numPolls = 0;
	m_sumPolls = 0;
	m_polling = false;
}

int Sensor::poll()
{
	int read = analogRead(m_analogPin);
	m_sumPolls += read;
	m_numPolls += 1;
	return read;
}

float Sensor::getAverage()
{
	return m_sumPolls / m_numPolls;
}

void Sensor::clearAverage()
{
	m_sumPolls = 0;
	m_numPolls = 0;
}

void Sensor::handle(unsigned long now)

	// If the sensor is scheduled to be on, then turn
	// it on and poll it's reading. When the sensor is
	// no longer scheduled, turn it off
{
	if (getScheduledOn() <= now && now < getScheduledOff())
	{

		if (getState() == 0)
		{
			Serial.print(m_id);
			Serial.print(":");
			Serial.println(1);
		}

		setState(1);
		poll();
	}

	else if (getState() == 1)
	{
		Serial.print(m_id);
		Serial.print(":");
		Serial.println(0);

		setState(0);
	}
}