#include "Action.h"

Action::Action() {} 
Action::Action(Context* ctx) {
	m_ctx = ctx;
}

void Action::run(unsigned long now) {
	setup(now);
	execute(now);
	teardown(now);
}

void Action::setup(unsigned long now) {}
void Action::execute(unsigned long now) {}
void Action::teardown(unsigned long now){}
void Action::turnOff() {}
void Action::touch(unsigned long now) {}