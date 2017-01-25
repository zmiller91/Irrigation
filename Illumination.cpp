#include "Illumination.h"

Illumination::Illumination() {}
Illumination::Illumination(Context* ctx, ScheduledComponent* light) :
	Action(ctx){
	m_ctx = ctx;
	m_light = light;
}

void Illumination::turnOff() {
	m_light->setState(0);
}