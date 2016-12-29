#include "ScheduledComponent.h"

ScheduledComponent::ScheduledComponent() {
	m_baseTime = 0;
	m_delay = 0;
	m_scheduledOn = 0;
	m_scheduledOff = 0;
}

ScheduledComponent::ScheduledComponent(Conf* conf, int id, int registr, 
	unsigned long now, unsigned long delay) :
	Component(conf, id, registr)
{
	m_baseTime = now;
	m_delay = delay;
	reschedule();
}

/*
Schedule a component to turn on.

@param timeOn - how many milliseconds the component is on
@param timeOff - how many milliseconds the component is off
*/
void ScheduledComponent::reschedule()
{
	m_scheduledOn = m_conf->lightOn;
	m_scheduledOff = m_conf->lightOff;
}

/*
Handle the component.  Turn it on if it needs to be on,
turn it off if it needs to be off
*/
void ScheduledComponent::execute(unsigned long now)
{
	// delay has passed, turn  on
	if (m_baseTime + m_delay <= now) {
		m_delay = 0;
		setState(1);
	}

	// Been on long enough, turn it off
	if (m_baseTime + m_delay + m_scheduledOn <= now) {
		setState(0);
	}

	// Been off long enough, restart
	if (m_baseTime + m_delay + m_scheduledOn + m_scheduledOff <= now) {
		m_baseTime = now;
		reschedule();
	}
}