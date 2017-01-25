#include "ScheduledComponent.h"

ScheduledComponent::ScheduledComponent() {
	m_baseTime = 0;
	m_delay = 0;
}

ScheduledComponent::ScheduledComponent(ScheduledConf* schedule, 
	int id, int registr, unsigned long now, unsigned long delay) :
	Component(schedule, id, registr)
{
	m_schedule = schedule;
	m_baseTime = now;
	m_delay = delay;
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
	if (m_baseTime + m_delay + m_schedule->onFor <= now) {
		setState(0);
	}

	// Been off long enough, restart
	if (m_baseTime + m_delay + m_schedule->onFor + m_schedule->offFor <= now) {
		m_baseTime = now;
	}
}