/*!
 * \class ControlOut
 * \file controlout
 * \brief Bridge between motor control and UI
 * \authors Steve Silber
 * \date 2018-11
 */



#pragma once

#include "bridgeout.h"

class VelocityOut : public BridgeOut<double, double>
{
public:

	VelocityOut(double yaw_value, double pitch_value)
		: BridgeOut(yaw_value, pitch_value)
	{ }


	void update()
	{
		printf("-- VELOCITY OUTPUT ---------------------------\n");

		auto[yaw, pitch] = vs;
		printf("yaw/pitch output, '%lf/%lf'\n", yaw, pitch);

		w->set_yaw_output(yaw);
		w->set_pitch_output(pitch);
	}
};

