#include "TimedComponent.h"

TimedComponent::TimedComponent() {}
TimedComponent::TimedComponent(Conf* conf, int id, int registr) :
	Component(conf, id, registr) {

	m_running = false;
	m_start = 0;
	m_delay = 0;
	m_duration = 0;
}

void TimedComponent::turnOn(unsigned long now, 
	unsigned long duration, unsigned long delay) {

	if (!m_running) {
		m_running = true;
		m_start = now;
		m_delay = delay;
		m_duration = duration;
	}
}

void TimedComponent::execute(unsigned long now) {

	// Return if the user is overriding
	Component::override(now);
	if (m_overriding) {
		return;
	}

	// If the component isn't running, it has no business
	// being on. This can happen in an override
	if (!m_running && getState() == 1) {
		setState(0);
	}

	if (m_running) {

		// Turn on once the delay has passed
		if (m_start + m_delay <= now) {
			setState(1);
		}

		// Turn off once the delay and duration have passed
		if (m_start + m_delay + m_duration <= now) {
			m_running = false;
			setState(0);
			clear();
		}
	}
}

void TimedComponent::clear() {
	m_start = 0;
	m_delay = 0;
	m_duration = 0;
}