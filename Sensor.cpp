#include "Component.h"
#include "Sensor.h"
#include "Root.h"
#include "Conf.h"

Sensor::Sensor() {}

/*
    A sensor is a component with added functionality. It has
	the ability to take readings from physical components.
*/
Sensor::Sensor(int id, int analogPin):

	// Construct super class
	Component(id)
{
	m_analogPin = analogPin;
	m_numPolls = 0;
	m_sumPolls = 0;
	m_polling = false;
}

/*
    Read and return the value of the sensor

	@return int
*/
int Sensor::poll()
{
	// http://forum.arduino.cc/index.php?topic=256921.0
	// The arduino uses a multiplexer for its inputs which means
	// sensors can influence the next sensors readings if the electrical
	// impedence is great enough. Therefore, read it twice, ignoring the first

	analogRead(m_analogPin);
	int read = analogRead(m_analogPin);
	m_sumPolls += read;
	m_numPolls += 1;
	return read;
}

/*
    Return the average reading for the most recent poll

    @return float
*/
float Sensor::getAverage()
{
	return m_sumPolls / m_numPolls;
}

/*
    Set the aberage back to 0
*/
void Sensor::clearAverage()
{
	m_sumPolls = 0;
	m_numPolls = 0;
}

/*
    Turn the sensor on or off, if it needs to be either. If
	the sensor is on, then read the sensor.
*/
void Sensor::handle(unsigned long now)

	// If the sensor is scheduled to be on, then turn
	// it on and poll it's reading. When the sensor is
	// no longer scheduled, turn it off
{
	if (getScheduledOn() <= now && now < getScheduledOff())
	{

		if (getState() == 0)
		{
			Root::notifySerial(m_id, Conf::ON_OFF, 1);
		}
		else 
		{
			poll();
		}

		setState(1);
	}

	else if (getState() == 1)
	{
		Root::notifySerial(m_id, Conf::ON_OFF, 0);
		setState(0);
	}
}