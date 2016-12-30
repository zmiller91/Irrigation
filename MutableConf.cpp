#include "MutableConf.h"



MutableConf::MutableConf() {
	state = States::NOT_CHANGED;
	holdStateFor = 0;
}