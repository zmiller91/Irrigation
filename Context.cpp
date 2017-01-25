//TODO: Are setters and getters really the best choice? Should 
// we use non-private variables instead?
#include "Context.h"

Context::Context() {
	light = new ScheduledConf();
	reseviorPump = new TimedConf();
	waterPump = new TimedConf();
	PP_1 = new TimedConf();
	PP_2 = new TimedConf();
	PP_3 = new TimedConf();
	PP_4 = new TimedConf();
	mixer = new TimedConf();
	heater = new Conf();
	fan = new Conf();
	hvac = new SensorConf();
	irrigation = new SensorConf();
	illumination = new Conf();
}