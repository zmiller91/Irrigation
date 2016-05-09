// Root.h

#ifndef _ROOT_h
#define _ROOT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Root
{
public:
	Root();
	~Root();
	static void notifySerial(int, int, int);

private:

};

#endif

