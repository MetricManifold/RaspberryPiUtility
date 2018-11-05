#pragma once

#include <QDoubleSpinBox>

#include "bridgein.h"
#include "raspberrypiutility.h"

class ControlIn : public BridgeIn<double, double>
{
	using BridgeIn<double, double>::BridgeIn;

public:
	ControlIn(RaspberryPiUtility * const w) :
		BridgeIn(w->get_yaw_input(), w->get_pitch_input())
	{
		/*
		 * further modify/transform the pulled values from the ui...
		 */
	}

	
	/*
	 * the function that actually bridges front end and backend by
	 * acting as the slot for the button press
	 */
	void slot()
	{
		auto[yaw, pitch] = vs;

		//b->get_control()->set_parameters(yaw, pitch);
		printf("yaw = %lf, pitch = %lf\n", yaw, pitch);
	}

};
