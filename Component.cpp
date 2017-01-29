#include "Component.h"
#include "MemoryFree.h"
#include "Context.h"

/*
    This class defines the functionality of a component. A 
	component is any physical item attatched to the arduino.
*/
Component::Component() {};

Component::Component(Conf* conf, int id, int registr)
{
	m_conf = conf;
	m_id = id;
	m_register = registr;
	m_state = 0;
	m_lastUpdate = 0;
	m_overriding = false;
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
    Set the state of the component, either on or off. 
	Ignore the request if an override is in progress.
*/
void Component::setState(int state)
{
	if (!m_overriding) {
		m_state = state;
		m_lastUpdate = millis();
	}
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


void Component::override(unsigned long now) {

	// If there is an override, then override
	switch (m_conf->m_override) {
	case Conf::Override::ON:
		m_overriding = true;
		m_state = 1;
		if (m_conf->m_overrideUntil < now) {
			m_overriding = false;
			m_conf->m_override = Conf::Override::NOT_CHANGED;
		}
		break;
	case Conf::Override::OFF:
		m_overriding = true;
		m_state = 0;
		if (m_conf->m_overrideUntil < now) {
			m_overriding = false;
			m_conf->m_override = Conf::Override::NOT_CHANGED;
		}
		break;
	case Conf::Override::NOT_CHANGED:
		m_overriding = false;
		break;
	}
}

void Component::notifyState() {
	Serial.print(m_id);
	Serial.print(":");
	Serial.print(Context::ON_OFF);
	Serial.print(":");
	Serial.println(m_state);
}

void Component::setup(unsigned long now) {}
void Component::teardown(unsigned long now) {}
void Component::execute(unsigned long now) {}