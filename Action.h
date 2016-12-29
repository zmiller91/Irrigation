// Action.h

#ifndef _ACTION_h
#define _ACTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Conf.h"

class Action 
{

protected:
	virtual void setup(unsigned long);
	virtual void execute(unsigned long);
	virtual void teardown(unsigned long);
	Conf* m_conf;

public:
	Action();
	Action(Conf*);
	void run(unsigned long);
};
	


#endif