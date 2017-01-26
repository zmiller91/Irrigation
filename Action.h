// Action.h

#ifndef _ACTION_h
#define _ACTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Context.h"

class Action 
{

protected:
	virtual void setup(unsigned long);
	virtual void execute(unsigned long);
	virtual void teardown(unsigned long);
	Context* m_ctx;

public:
	Action();
	Action(Context*);
	void run(unsigned long);
	virtual void turnOff();
	virtual void touch(unsigned long now);
};
	


#endif