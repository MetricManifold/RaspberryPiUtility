#include "control.h"

std::pair<Degree, Degree> tmc::get_coords()
{
	return motor_driver().read_pos();
}

