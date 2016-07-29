//TODO: Are setters and getters really the best choice? Should 
// we use non-private variables instead?
#include "Conf.h"

Conf::Conf() {}
Conf::~Conf() {}

void Conf::setValveOpen(unsigned long value)
{
	valveOpen = value;
}

void Conf::setPeriPumpOn(unsigned long value)
{
	periPumpOn = value;
}

void Conf::setWaterPumpOn(unsigned long value)
{
	waterPumpOn = value;
}

void Conf::setMixerOn(unsigned long value)
{
	mixerOn = value;
}

void Conf::setLightOn(unsigned long value)
{
	lightOn = value;
}

void Conf::setLightOff(unsigned long value)
{
	lightOff = value;
}
void Conf::setPollOn(unsigned long value)
{
	pollOn = value;
}

void Conf::setPollOff(unsigned long value)
{
	pollOff = value;
}

void Conf::setMinWater(int value)
{
	minWater = value;
}

void Conf::setMinTemp(int value)
{
	minTemp = value;
}
void Conf::setMaxTemp(int value)
{
	maxTemp = value;
}

unsigned long Conf::getValveOpen()
{
	return valveOpen;
}

unsigned long Conf::getPeriPumpOn()
{
	return periPumpOn;
}

unsigned long Conf::getWaterPumpOn()
{
	return waterPumpOn;
}

unsigned long Conf::getMixerOn()
{
	return mixerOn;
}

unsigned long Conf::getLightOn()
{
	return lightOn;
}

unsigned long Conf::getLightOff()
{
	return lightOff;
}

unsigned long Conf::getPollOn()
{
	return pollOn;
}

unsigned long Conf::getPollOff()
{
	return pollOff;
}

int Conf::getMinWater()
{
	return minWater;
}

int Conf::getMinTemp()
{
	return minTemp;
}

int Conf::getMaxTemp()
{
	return maxTemp;
}