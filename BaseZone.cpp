// 
// 
// 
#include "BaseZone.h"

BaseZone::BaseZone(){}

BaseZone::BaseZone(String name, int data, int latch, int clock, int moisture, int photo, int temp, int humidity)
{
	m_name = name;
	// initialize data pins and analogin inputs
	DATA_PIN = data;
	LATCH_PIN = latch;
	CLOCK_PIN = clock;
	MOISTURE_SENSOR = moisture;
	PHOTORESISTOR = photo;
	TEMP_SENSOR = temp;
	HUMIDITY_SENSOR = humidity;

	NUM_REGISTERS = 3;

	pinMode(data, OUTPUT);
	pinMode(clock, OUTPUT);
	pinMode(latch, OUTPUT);
	pinMode(moisture, INPUT);
	pinMode(photo, INPUT);
	pinMode(temp, INPUT);
	pinMode(humidity, INPUT);
}

void BaseZone::test()
{
	ledOneByOne(250);
	for (int i = 0; i < 3; i++) {
		ledBlink(250);
	}
}

void BaseZone::ledOneByOne(int wait) {
	int numBits = NUM_REGISTERS * 8;
	int prevBit = 0;
	for (int bit = 0; bit < numBits; bit++) {
		m_bitmask[prevBit] = 0;
		m_bitmask[bit] = 1;
		prevBit = bit;
		putToRegister();
		delay(wait);
	}
	m_bitmask[prevBit] = 0;
	putToRegister();
}

void BaseZone::allOn() {
	int numBits = NUM_REGISTERS * 8;
	for (int bit = 0; bit < numBits; bit++) {
		m_bitmask[bit] = 1;
	}
	putToRegister();
}

void BaseZone::allOff() {
	int numBits = NUM_REGISTERS * 8;
	for (int bit = 0; bit < numBits; bit++) {
		m_bitmask[bit] = 0;
	}
	putToRegister();
}

void BaseZone::ledBlink(int wait) {
	int numBits = NUM_REGISTERS * 8;
	for (int bit = 0; bit < numBits; bit++) {
		m_bitmask[bit] = 1;
	}
	putToRegister();
	delay(wait);
	for (int bit = 0; bit < numBits; bit++) {
		m_bitmask[bit] = 0;
	}
	putToRegister();
	delay(wait);
}

void BaseZone::putToRegister() {

	// Begin to write to the registers
	digitalWrite(LATCH_PIN, 0);

	// There are three registers, since we are
	// shifting out the right most register needs
	// to be shifted first and the left most register
	// needs to be shifted last
	for (int reg = (NUM_REGISTERS - 1); reg >= 0; reg--) {

		// An 8-bit register can be represented as an 
		// 8-bit character. To construct the bit mask, simply
		// loop through register entries in the zone array and 
		// set all corresponding character bits

		// Construct bitmask
		unsigned char bitmask = 0;
		for (int b = 0; b < 8; b++) {
			bitWrite(bitmask, b, m_bitmask[reg * 8 + b]);
		}

		// Put bitmask to register
		shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, bitmask);
	}

	// End write to registers. Display changes.
	digitalWrite(LATCH_PIN, 1);
}
