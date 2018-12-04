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

#ifdef _WIN64
		auto[yaw, pitch] = vs;
#else
                double yaw = std::get<0>(vs);
                double pitch = std::get<1>(vs);
#endif
		printf("yaw/pitch output, '%lf/%lf'\n", yaw, pitch);

		w->set_yaw_output(yaw);
		w->set_pitch_output(pitch);
	}
};

