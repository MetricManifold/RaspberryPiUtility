/*!
 * \class CelestialOut
 * \file celestialin.h
 * \brief Bridge between celestialdb class and UI
 * \authors Steve Silber, Alex Yan
 * \date 2018-11
 */

#pragma once

#include <string>

#include "bridgeout.h"
#include "coordinates.h"
#include "Angle.h"

class CelestialOut : public BridgeOut<char *, Angle, Angle>
{
public:

	CelestialOut(char *name, Angle ra, Angle d)
		: BridgeOut(name, ra, d)
	{ }


	void update()
	{
		auto[name, ra, d] = vs;
		printf("RA/D output, '%lf/%lf'\n", ra.get_degrees(), d.get_degrees());

		w->set_name_dis(name);
		w->set_rasc_dis(std::to_string(ra.get_degrees()));
		w->set_dec_dis(std::to_string(d.get_degrees()));
	}
};

