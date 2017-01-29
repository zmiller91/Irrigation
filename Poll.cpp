
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
		output(Context::MOISTURE_SENSOR_ID, m_moisture->getAverage());
		output(Context::TEMP_SENSOR_ID, m_temperature->getAverage());
		output(Context::PHOTORESISTOR_ID, m_light->getAverage());
		output(Context::HUMIDITY_SENSOR_ID, m_humidity->getAverage());
	}

	// Been on for long enough, reset the base time
	if (m_baseTime + m_schedule->onFor + m_schedule->offFor <= now) {
		m_baseTime = now;
	}
}

void Poll::output(int sensor, int value) {

	Serial.print(sensor);
	Serial.print(":");
	Serial.print(Context::POLL_ID);
	Serial.print(":");
	Serial.println(value);
}