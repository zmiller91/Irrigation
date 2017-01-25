#ifndef _COMPONENT_h
#define _COMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Context.h"

class Component
{
private:
	int m_state;

 protected:
	 Conf* m_conf;
	 bool m_overriding;
	 unsigned long m_lastUpdate;
	 int m_id;
	 virtual void setup(unsigned long);
	 virtual void execute(unsigned long);
	 virtual void teardown(unsigned long);

 public:
	Component();
	Component(Conf* conf, int, int);
	int m_register;
	bool isOn();
	int getState();
	void setState(int);
	unsigned long getLastUpdate();
	int getId();
	void run(unsigned long);
	void override(unsigned long);
};


#endif

