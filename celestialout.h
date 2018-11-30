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

