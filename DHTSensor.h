// DHTSensor.h

#ifndef _DHTSENSOR_h
#define _DHTSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "Sensor.h"
#include "dht.h"


// Define types of readings.
#define TEMPERATURE 1
#define HUMIDITY 2

class DHTSensor : public Sensor
{
protected:
	virtual float read(int);
	DHT* _dht;
	int _type;

public:
	DHTSensor();
	DHTSensor(Conf* conf, int id, int analogPin, int type);
};

#endif

