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
	m_light = new ScheduledComponent(m_ctx->light, Context::LIGHT_ID, REG_02, millis(), 0);

	// HVAC
	m_heater = new Component(m_ctx->heater, Context::HEATER_ID, REG_10);
	m_fan = new Component(m_ctx->fan, Context::FAN_ID, REG_11);
	m_temp = new Sensor(new Conf(), Context::TEMP_SENSOR_ID, TEMP_SENSOR);

	// Irrigation
	m_moisture = new Sensor(new Conf(), Context::MOISTURE_SENSOR_ID, MOISTURE_SENSOR);
	m_reseviorPump = new TimedComponent(m_ctx->reseviorPump, Context::RESEVIOR_PUMP_ID, REG_03);
	m_PP_1 = new TimedComponent(m_ctx->PP_1, Context::PP1_ID, REG_04);
	m_PP_2 = new TimedComponent(m_ctx->PP_2, Context::PP2_ID, REG_05);
	m_PP_3 = new TimedComponent(m_ctx->PP_3, Context::PP3_ID, REG_06);
	m_PP_4 = new TimedComponent(m_ctx->PP_4, Context::PP4_ID, REG_07);
	m_mixer = new TimedComponent(m_ctx->mixer, Context::MIXER_ID, REG_08);
	m_waterPump = new TimedComponent(m_ctx->waterPump, Context::WATER_PUMP_ID, REG_01);

	// Actions
	m_photoresistor = new Sensor(new Conf(), Context::PHOTORESISTOR_ID, PHOTORESISTOR);
	m_humidity = new Sensor(new Conf(), Context::HUMIDITY_SENSOR_ID, HUMIDITY_SENSOR);
	m_poll = new Poll(m_ctx, m_moisture, m_temp, m_photoresistor, m_humidity);
	m_hvac = new HVAC(m_ctx, m_temp, m_fan, m_heater);
	m_illumination = new Illumination(m_ctx, m_light);
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

	Action* actions[] =  {m_irrigation, m_hvac, m_illumination, m_poll};
	Conf* actionConf[] = { m_ctx->irrigation, m_ctx->hvac, m_ctx->illumination, m_ctx->poll };

	// Run the actions if they're not overridden
	int i = 0;
	for (Action* act : actions) {
		if (actionConf[i]->m_override != Conf::Override::OFF) {
			act->run(now);
		}

		i++;
	}

	// Run the components
	for (Component* c : components) {
		c->run(now);
	}

	i = 0;
	for (Action* act : actions) {

		// Touched
		if (actionConf[i]->touched) {
			act->touch(now);
			actionConf[i]->touched = false;
		}

		// Overridden
		else if (actionConf[i]->m_override == Conf::Override::OFF) {
			act->turnOff();
		}

		i++;
	}

	// Override any components and update the bitmask
	for (Component* c : components) {
		c->override(now);
		m_bitmask[c->m_register] = c->getState();
	}
	
	// Update the register
	putToRegister();
}