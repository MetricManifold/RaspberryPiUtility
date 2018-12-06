/*!
 * \class ControlOut
 * \file controlout
 * \brief Bridge between motor control and UI
 * \authors Steve Silber
 * \date 2018-11
 */



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
		printf("-- CONTROL OUTPUT ---------------------------\n");

		auto[yaw, pitch] = vs;
		printf("yaw/pitch output, '%lf/%lf'\n", yaw, pitch);

		w->set_yaw_output(yaw);
		w->set_pitch_output(pitch);
	}
};

