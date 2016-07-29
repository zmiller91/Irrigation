//TODO: Rename class to 'Serial'
#include "Root.h"
#include "Conf.h"

Root::Root(){
	Serial.begin(9600);
}

void Root::notifySerial(int component_id, int output_type, int output) {
	Serial.print(Conf::ARDUINO_ID);
	Serial.print(":");
	Serial.print(component_id);
	Serial.print(":");
	Serial.print(output_type);
	Serial.print(":");
	Serial.println(output);
}