// 
// 
// 

#include "Sensor.h"

SensorClass::SensorClass() {};
SensorClass::SensorClass(String name, unsigned long scheduledOn, int analogPin):

	// Construct super class
	ComponentClass(name, scheduledOn)
{
	m_analogPin = analogPin;
	m_numPolls = 0;
	m_sumPolls = 0;
	m_polling = false;
}

int SensorClass::poll()
{
	int read = analogRead(m_analogPin);
	m_sumPolls += read;
	m_numPolls += 1;
	return read;
}

float SensorClass::getAverage()
{
	return m_sumPolls / m_numPolls;
}

void SensorClass::clearAverage()
{
	m_sumPolls = 0;
	m_numPolls = 0;
}

void SensorClass::setPolling(bool polling)
{
	m_polling = polling;
}

bool SensorClass::isPolling()
{
	return m_polling;
}