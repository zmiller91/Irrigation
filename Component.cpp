#include "Component.h"
#include "MemoryFree.h"
#include "Root.h"
#include "Conf.h"

/*
    This class defines the functionality of a component. A 
	component is any physical item attatched to the arduino.
*/
Component::Component() {
	m_scheduledOn = 100;
	m_scheduledOff = 10000;
};

Component::Component(int id)
{
	m_id = id;
	m_scheduledOn = 0;
	m_scheduledOff = 0;
	m_state = 0;
	m_lastUpdate = 0;
}

/*
    Schedule a component to turn on.

	@param delay - how many milliseconds until the component turns on
	@param timeOn - how many milliseconds the component is on
	@param now - the current time, in milliseconds
*/
void Component::schedule(unsigned long delay, unsigned long timeOn, unsigned long now)
{
	m_scheduledOn = (now + delay);
	m_scheduledOff = (m_scheduledOn + timeOn);
	m_lastUpdate = millis();
}

/*
    Get the next time a component is schedule to be off

    @return long
*/
unsigned long Component::getScheduledOff()
{
	return m_scheduledOff;
}

/*
    Get the next time a component is scheduled to be on

	@return long
*/
unsigned long Component::getScheduledOn()
{
	return m_scheduledOn;
}

/*
    Get the current state of the component, either on or
	off

    @return int
*/
int Component::getState()
{
	return m_state;
}

/*
    Set the state of the component, either on or off
*/
void Component::setState(int state)
{
	m_state = state;
	m_lastUpdate = millis();
}

/*
    Get the last time this component was updated. 

    @return unsigned long
*/
unsigned long Component::getLastUpdate()
{
	return m_lastUpdate;
}

/*
    Get the id of the component

     @return int
*/
int Component::getId()
{
	return m_id;
}

/*
    Handle the component.  Turn it on if it needs to be on, 
	turn it off if it needs to be off
*/
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

	// If the component on and it's not scheduled, turn it off
	else if (getState() == 1)
	{
		Root::notifySerial(m_id, Conf::ON_OFF, 0);
		setState(0);
	}
}