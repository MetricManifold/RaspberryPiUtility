#pragma once


class ControlOut
{
public:
	double const yaw_value;
	double const pitch_value;

	ControlOut(double yaw_value, double pitch_value) :
		yaw_value{ yaw_value },
		pitch_value{ pitch_value }
	{ }
};