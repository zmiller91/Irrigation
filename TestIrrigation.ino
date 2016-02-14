
// Analog In
#include "MemoryFree.h"
#include "Sensor.h"
#include "BaseZone.h"
#include "Component.h"
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


// This arduino supports 3 zones. A zone represents a set of actions
// and sensors to monitor, water, feed, and illuminate a sections of 
// plants. Here, zones are just arrays that contain certain pieces of
// information that are required to controll the actions of a zone.

unsigned long ZONE_01[64];
unsigned long ZONE_02[64];
unsigned long ZONE_03[64];

ZoneClass ZONE("Zone 1", DP12, DP11, DP10, AI_00, AI_01, AI_02, AI_03, 
	64800000, 21600000, /* Light on, Light off */
	300, 3000, /* Poll on, Poll off */
	15000, 150); /* Valve on, Peri on */

void setup() {
	Serial.begin(9600);
	Serial.println("Setting up");
	//ZONE.test();
	Serial.println("Setup complete");
}

void loop() {

	ZONE.execute();
}