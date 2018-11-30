/*!
 * \class CelestialOut
 * \file celestialin.h
 * \brief Bridge between celestialdb class and UI
 * \authors Steve Silber, Alex Yan
 * \date 2018-11
 */

#pragma once

#include "bridgeout.h"
#include "coordinates.h"

class CelestialOut : public BridgeOut<rightasc, declination>
{
public:

	CelestialOut(rightasc ra, declination d)
		: BridgeOut(ra, d)
	{ }


	void update()
	{
		auto[ra, d] = vs;
		//printf("yaw/pitch output, '%lf/%lf'\n", yaw, pitch);

	}
};

