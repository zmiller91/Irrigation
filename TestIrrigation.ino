
#include "MemoryFree.h"
#include "Root.h"
#include "Component.h"
#include "Sensor.h"
#include "BaseZone.h"
#include "Zone.h"

unsigned long AI_00 = 0;
unsigned long AI_01 = 1;
unsigned long AI_02 = 2;
unsigned long AI_03 = 3;
unsigned long AI_04 = 4;
unsigned long AI_05 = 5;

// Digitial Pens
unsigned long DP2 = 2;
unsigned long DP3 = 3;
unsigned long DP4 = 4;
unsigned long DP5 = 5;
unsigned long DP6 = 6;
unsigned long DP7 = 7;
unsigned long DP8 = 8;
unsigned long DP9 = 9;
unsigned long DP10 = 10;
unsigned long DP11 = 11;
unsigned long DP12 = 12;
unsigned long DP13 = 13;

Zone ZONE("Zone 1", DP12, DP11, DP10, AI_00, AI_02, AI_01, AI_03, 
	43200000, 43200000, /* Light on, Light off */
	30000, 320000, /* Poll on, Poll off -- 30000, 900000 */
	2750, 1000,  0, 0, 0, 0); /* Valve on, Peri on, Mixer on, Pump on, phUp on, phDown on */

void setup() {
	Serial.begin(9600);
	Serial.println("test");
	ZONE.test();
	pinMode(13, OUTPUT);
	digitalWrite(13, 1);
}

void loop() {
	//ZONE.allOn(); 
	//ZONE.allOff();
	//ZONE.ledBlink(3000);
	//ZONE.test();
	ZONE.execute();
}