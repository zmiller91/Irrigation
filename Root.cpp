#include "Root.h"
#include "Conf.h"

/*
    This is a utility class that coordinates communication
	with the serial output/input.  

	TODO: Move more login into here. Rename to 'Serial'
*/
Root::Root(){
	Serial.begin(9600);
}

/*
    Print to serial.  Output will look like
	"component_id:output_type:output"
*/
void Root::notifySerial(int component_id, int output_type, int output) {
	Serial.print(Conf::ARDUINO_ID);
	Serial.print(":");
	Serial.print(component_id);
	Serial.print(":");
	Serial.print(output_type);
	Serial.print(":");
	Serial.println(output);
}