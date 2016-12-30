#include "BaseZone.h"
#include "Zone.h"
/*
    A zone is controller for the entire application. It's
	responsible for scheduling components and reading sensors. 
*/
Zone::Zone() {}
Zone::Zone(Context* ctx, String name, int data, int latch, int clock, int moisture, int photo, int temp, int humidity) :

	// Construct member objects
	BaseZone(name, data, latch, clock, moisture, photo, temp, humidity)
{
	m_ctx = ctx;

	// Light
	m_light = new ScheduledComponent(m_ctx->light, Context::LIGHT_ID, REG_01, millis(), 0);

	// HVAC
	m_heater = new Component(new Conf(), Context::HEATER_ID, REG_02);
	m_fan = new Component(new Conf(), Context::FAN_ID, REG_03);
	m_temp = new Sensor(new Conf(), Context::TEMP_SENSOR_ID, TEMP_SENSOR);

	// Irrigation
	m_moisture = new Sensor(new Conf(), Context::MOISTURE_SENSOR_ID, MOISTURE_SENSOR);
	m_reseviorPump = new TimedComponent(new Conf(), Context::RESEVIOR_PUMP_ID, REG_04);
	m_PP_1 = new TimedComponent(new Conf(), Context::PP1_ID, REG_05);
	m_PP_2 = new TimedComponent(new Conf(), Context::PP2_ID, REG_06);
	m_PP_3 = new TimedComponent(new Conf(), Context::PP3_ID, REG_07);
	m_PP_4 = new TimedComponent(new Conf(), Context::PP4_ID, REG_08);
	m_mixer = new TimedComponent(new Conf(), Context::MIXER_ID, REG_09);
	m_waterPump = new TimedComponent(new Conf(), Context::WATER_PUMP_ID, REG_10);

	// Actions
	m_hvac = new HVAC(m_ctx, m_temp, m_fan, m_heater);
	m_irrigation =  new Irrigation(m_ctx, m_moisture, m_reseviorPump, 
		m_waterPump, m_PP_1, m_PP_2, m_PP_3, m_PP_4, m_mixer);
}

/*
    Reset the register to off
*/
void Zone::clearRegister()
{
	for (int i = 0; i < NUM_BITS; i++)
	{
		m_bitmask[i] = 0;
	}

	putToRegister();
}

/*
    Main function that gets called in a loop. 
*/
void Zone::execute(unsigned long now)
{
	Component* components[] = { m_light, m_temp, m_fan, m_heater, 
		m_reseviorPump, m_waterPump, m_PP_1, m_PP_2, m_PP_3, 
		m_PP_4, m_mixer, m_moisture };

	Action* actions[] = { m_hvac, m_irrigation };

	// Run the actions
	for (Action* a : actions) {
		a->run(now);
	}

	// Run the components and upate the bitmask
	for (Component* c : components) {
		c->run(now);
		m_bitmask[c->m_register] = c->getState();
	}
	
	// Update the register
	putToRegister();
}