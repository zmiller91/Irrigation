#include "HVAC.h"
#include "Sensor.h"
#include "Component.h"

HVAC::HVAC() {}
HVAC::HVAC(Conf* conf, Sensor* tempSensor, 
	Component* fan, Component* heater) :
	Action(conf) {

	m_temperatureSensor = tempSensor;
	m_fan = fan;
	m_heater = heater;
}

void HVAC::execute(unsigned long now) {

	// Get the average temperature
	int sumTemps = 0;
	int countTemps = 0;
	int averageTemp = 0;
	if (m_temperatureSensor->hasAverage()) {
		sumTemps += m_temperatureSensor->getAverage();
		countTemps++;
		averageTemp = sumTemps / countTemps;
	}

	// No data, abort
	if (countTemps == 0) {
		return;
	}

	int minTemp = m_conf->minTemp;
	int maxTemp = m_conf->maxTemp;

	// In a good spot, turn stuf off if the average is
	// in the middle of the range
	if (minTemp < averageTemp  &&
		averageTemp < maxTemp) {

		int halfway = minTemp + ((maxTemp - minTemp) / 2);
		if (m_fan->isOn() && 
			averageTemp < halfway) {
			m_fan->setState(0);
		}

		if (m_heater->isOn() &&
			averageTemp > halfway) {
			m_heater->setState(0);
		}
	}
	
	// Too hot, either turn the heater off or the fans on
	if (averageTemp > maxTemp) {
		if (m_heater->getState() == 1) {
			m_heater->setState(0);
		}
		else {
			m_fan->setState(1);
		}
	}

	// Too cold, ether turn the fan off or the heater on
	if (averageTemp < minTemp) {
		if (m_fan->getState() == 1) {
			m_fan->setState(0);
		}
		else {
			m_heater->setState(1);
		}
	}
}