#include "Action.h"

Action::Action() {} 
Action::Action(Conf* conf) {
	m_conf = conf;
}

void Action::run(unsigned long now) {
	setup(now);
	execute(now);
	teardown(now);
}

void Action::setup(unsigned long now) {}
void Action::execute(unsigned long now) {}
void Action::teardown(unsigned long now){}