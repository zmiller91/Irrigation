// 
// 
// 

#include "Component.h"
#include "Sensor.h"
#include "Root.h"

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

int Sensor::poll(bool skip)
{
	int read = analogRead(m_analogPin);
	if (!skip)
	{
		m_sumPolls += read;
		m_numPolls += 1;
	}
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
		// http://forum.arduino.cc/index.php?topic=256921.0
		// The arduino uses a multiplexer for its inputs which means
		// sensors can influence the next sensors readings if the electrical
		// impedence is great enough. Therefore, ignore the first poll

		if (getState() == 0)
		{
			Root::notifySerial(m_id, ON_OFF, 1);
			poll(true);
		}
		else 
		{
			poll(false);
		}

		setState(1);
	}

	else if (getState() == 1)
	{
		Root::notifySerial(m_id, ON_OFF, 0);
		setState(0);
	}
}