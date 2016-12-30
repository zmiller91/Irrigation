#include "Component.h"
#include "MemoryFree.h"
#include "Context.h"

/*
    This class defines the functionality of a component. A 
	component is any physical item attatched to the arduino.
*/
Component::Component() {};

Component::Component(int id, int registr)
{
	m_id = id;
	m_register = registr;
	m_state = 0;
	m_lastUpdate = 0;
}

bool Component::isOn() {
	return m_state == 1;
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
	Initialize the lifecycle

	@param now - current time in millis
*/
void Component::run(unsigned long now) {
	setup(now);
	execute(now);
	teardown(now);
}

void Component::setup(unsigned long now) {}
void Component::execute(unsigned long now) {}
void Component::teardown(unsigned long now) {}