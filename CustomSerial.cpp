// 
// 
// 

#include "CustomSerial.h"

CustomSerial::CustomSerial() {}

void CustomSerial::out(int id, int output)
{
	Serial.begin(9600);
	Serial.print(id);
	Serial.print("-");
	Serial.print(output);
}
