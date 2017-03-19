#include "DHTSensor.h"

DHTSensor::DHTSensor() {}
DHTSensor::DHTSensor(Conf* conf, int id, int analogPin, int type) :
		Sensor(conf, id, analogPin) {
	_dht = new DHT(analogPin, DHT11);
	_type = type;

	_dht->begin();
}

float DHTSensor::read(int pin) {
	switch (_type) {
	case TEMPERATURE:
		return _dht->readTemperature();
	case HUMIDITY:
		return _dht->readHumidity();
	}

	return -1;
}