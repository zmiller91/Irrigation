#include "Conf.h"

Conf::Conf() {
	m_override = Override::NOT_CHANGED;
	m_overrideUntil = 0;
	touched = false;
}