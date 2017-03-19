
#include "Poll.h"
Poll::Poll() {};
Poll::Poll( Context* ctx, Sensor* moisture,
	Sensor* temp, Sensor* light, Sensor* humidity) :
	Action(ctx) {
	m_moisture = moisture;
	m_temperature = temp;
	m_light = light;
	m_humidity = humidity;
	m_baseTime = 0;
	m_schedule = m_ctx->poll;
}

void Poll::execute(unsigned long now) {

	// Been off for long enough, poll
	if (m_baseTime + m_ctx->poll->offFor <= now) {
		output(m_moisture);
		output(m_temperature);
		output(m_light);
		output(m_humidity);
	}

	// Been on for long enough, reset the base time
	if (m_baseTime + m_schedule->onFor + m_schedule->offFor <= now) {
		m_baseTime = now;
	}
}

void Poll::output(Sensor* sensor) {
	if (sensor->hasAverage()) {
		Serial.print(sensor->getId());
		Serial.print(":");
		Serial.print(Context::POLL_ID);
		Serial.print(":");
		Serial.println(sensor->getAverage());
	}
}