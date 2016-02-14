// 
// 
// 

#include "Component.h"
#include "MemoryFree.h"

ComponentClass::ComponentClass() {
	m_scheduledOn = 100;
	m_scheduledOff = 10000;
};
ComponentClass::ComponentClass(String name, unsigned long timeOn)
{
	Serial.begin(9600);
	Serial.println(freeMemory());

	m_name = name;
	m_timeOn = timeOn;
	m_scheduledOn = 0;
	m_scheduledOff = 0;
	m_state = 0;
	m_lastUpdate = 0;
}

void ComponentClass::schedule(unsigned long delay, unsigned long now)
{
	m_scheduledOn = (now + delay);
	m_scheduledOff = (m_scheduledOn + m_timeOn);
	m_lastUpdate = millis();
}

unsigned long ComponentClass::getScheduledOff()
{
	return m_scheduledOff;
}

unsigned long ComponentClass::getScheduledOn()
{
	return m_scheduledOn;
}

int ComponentClass::getState()
{
	return m_state;
}

void ComponentClass::setState(int state)
{
	m_state = state;
	m_lastUpdate = millis();
}

unsigned long ComponentClass::getLastUpdate()
{
	return m_lastUpdate;
}

String ComponentClass::getName()
{
	return m_name;
}



void ComponentClass::handle(unsigned long now)
{
	// If the component is scheduled to be on, then turn it on

	if (getScheduledOn() <= now && now < getScheduledOff())
	{
		setState(1);
	}

	else if (getState() == 1)
	{
		setState(0);
	}
}