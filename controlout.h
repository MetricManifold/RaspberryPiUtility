#pragma once

#include "bridgeout.h"

class ControlOut : public BridgeOut<double, double>
{
public:

	ControlOut(double yaw_value, double pitch_value)
		: BridgeOut(yaw_value, pitch_value)
	{ }


	void update()
	{
		auto[yaw, pitch] = vs;

		//BridgeOut::w->set_yaw_output(yaw);
		//BridgeOut::w->set_pitch_output(pitch);
	}
};
