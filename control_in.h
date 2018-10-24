#pragma once

#include <QDoubleSpinBox>

#include "raspberrypiutility.h"


class ControlIn
{
public:
	double const yaw;
	double const pitch;

	ControlIn(RaspberryPiUtility w) : 
		yaw{ w.get_yaw_input()->value() },
		pitch{ w.get_pitch_input()->value() }
	{ }

};

