#include "limits.h"

#include "UserInteraction.h"
#include "Context.h"

void UserInteraction::touch(Conf* conf) {
	conf->touched = true;
}

void UserInteraction::overrideOnOff(Conf* conf, unsigned long now, int action, 
	unsigned long newVal) {

	switch(action) {
	case Context::OVERRIDE_ON_OFF:

		// Must be -1, 0, or 1
		if (!(-1 <= newVal <= 1)) {
			break;
		}

		// Reset
		if (newVal == -1) {
			conf->m_override = Conf::Override::NOT_CHANGED;
			break;
		}

		// Turn on or off
		conf->m_override = newVal == 1 ?
			Conf::Override::ON : Conf::Override::OFF;
		conf->m_overrideUntil = ULONG_MAX;
		break;

	case Context::OVERRIDE_ON_FOR:
		conf->m_override = Conf::Override::ON;
		conf->m_overrideUntil = now + newVal;
		break;

	case Context::OVERRIDE_OFF_FOR:
		conf->m_override = Conf::Override::OFF;
		conf->m_overrideUntil = now + newVal;
		break;
	}
}

void UserInteraction::configureSchedule(ScheduledConf* conf, int action,
	unsigned long newVal) {

	switch (action) {
	case Context::CONF_TIME_ON:
		conf->onFor = newVal;
		break;
	case Context::CONF_TIME_OFF:
		conf->offFor = newVal;
		break;
	}
}

void UserInteraction::configureTimer(TimedConf* conf, int action,
	unsigned long newVal) {

	if (action == Context::CONF_TIME_ON) {
		conf->onFor = newVal;
	}

}

void UserInteraction::configureSensor(SensorConf* conf, int action, unsigned long newVal) {

	switch (action) {
	case Context::CONF_MIN:
		conf->minimum = newVal;
		break;
	case Context::CONF_MAX:
		conf->maximum = newVal;
		break;
	}
}