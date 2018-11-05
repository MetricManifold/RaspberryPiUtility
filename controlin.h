#pragma once

#include <QDoubleSpinBox>

#include "bridgein.h"

class ControlIn : BridgeIn<double, double>
{

public:
	ControlIn(Backend * const b, RaspberryPiUtility * const w) :
		BridgeIn(b, w->get_yaw_input(), w->get_pitch_input())
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

