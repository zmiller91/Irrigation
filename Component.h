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
 protected:
	 Context* m_ctx;
	 int m_state;
	 unsigned long m_lastUpdate;
	 int m_id;
	 virtual void setup(unsigned long);
	 virtual void execute(unsigned long);
	 virtual void teardown(unsigned long);

 public:
	Component();
	Component(Context*, int, int);
	int m_register;
	bool isOn();
	int getState();
	void setState(int);
	unsigned long getLastUpdate();
	int getId();
	void run(unsigned long);
};


#endif

