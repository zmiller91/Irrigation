// 
// 
// 

#include "Root.h"

Root::Root(){
	Serial.begin(9600);
}
Root::~Root(){}


void Root::notifySerial(int component_id, int output_type, int output) {
	Serial.print(ARDUINO_ID);
	Serial.print(":");
	Serial.print(component_id);
	Serial.print(":");
	Serial.print(output_type);
	Serial.print(":");
	Serial.println(output);
}