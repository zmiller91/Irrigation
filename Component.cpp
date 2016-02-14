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
	setScheduledOn(now + delay);
	setScheduledOff(getScheduledOn() + m_timeOn);
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

void ComponentClass::setScheduledOff(unsigned long schedule)
{
	m_scheduledOff = schedule;
	m_lastUpdate = millis();
}

void ComponentClass::setScheduledOn(unsigned long schedule)
{
	m_scheduledOn = schedule;
	m_lastUpdate = millis();
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

void ComponentClass::use(int userid)
{
	if (m_users[userid] == false)
	{
		m_users[userid] = true;
		m_numUsers += 1;
	}
}

void ComponentClass::stopUsing(int userid)
{
	if (m_users[userid] == true)
	{
		m_users[userid] = false;
		m_numUsers -= 1;
	}
}

bool ComponentClass::isUsing(int userid)
{
	return m_users[userid] && m_users[userid] != NULL;
}

int ComponentClass::getNumUsers()
{
	return m_numUsers;
}

String ComponentClass::getName()
{
	return m_name;
}