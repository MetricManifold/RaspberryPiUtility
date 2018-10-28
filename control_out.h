#pragma once

#include "bridgeout.h"

class ControlOut : BridgeOut<double, double>
{
public:

	ControlOut(double yaw_value, double pitch_value)
		: BridgeOut(yaw_value, pitch_value)
	{ }

	void update(RaspberryPiUtility * const w)
	{
		auto[yaw, pitch] = vs;

		w->set_yaw_output(yaw);
		w->set_pitch_output(pitch);
	}
};

