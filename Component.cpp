// 
// 
// 
#include "Component.h"
#include "MemoryFree.h"
#include "Root.h"
#include "Conf.h"

Component::Component() {
	m_scheduledOn = 100;
	m_scheduledOff = 10000;
};
Component::Component(int id)
{
	//int fm = freeMemory();
	//Root::notifySerial(1, 1, 1);

	m_id = id;
	m_scheduledOn = 0;
	m_scheduledOff = 0;
	m_state = 0;
	m_lastUpdate = 0;
}

void Component::schedule(unsigned long delay, unsigned long timeOn, unsigned long now)
{
	m_scheduledOn = (now + delay);
	m_scheduledOff = (m_scheduledOn + timeOn);
	m_lastUpdate = millis();
}

unsigned long Component::getScheduledOff()
{
	return m_scheduledOff;
}

unsigned long Component::getScheduledOn()
{
	return m_scheduledOn;
}

int Component::getState()
{
	return m_state;
}

void Component::setState(int state)
{
	m_state = state;
	m_lastUpdate = millis();
}

unsigned long Component::getLastUpdate()
{
	return m_lastUpdate;
}

int Component::getId()
{
	return m_id;
}

void Component::handle(unsigned long now)
{
	// If the component is scheduled to be on, then turn it on

	if (getScheduledOn() <= now && now < getScheduledOff())
	{

		// If the current state is off, then notify serial
		// of a state change
		if (getState() == 0)
		{
			Root::notifySerial(m_id, Conf::ON_OFF, 1);
		}

		setState(1);
	}

	else if (getState() == 1)
	{
		Root::notifySerial(m_id, Conf::ON_OFF, 0);
		setState(0);
	}
}