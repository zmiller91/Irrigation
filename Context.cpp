//TODO: Are setters and getters really the best choice? Should 
// we use non-private variables instead?
#include "Context.h"

Context::Context() {
	light = new ScheduledConf();
}