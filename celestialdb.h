/*!
 * \class CelestialDB
 * \file celestialdb.h
 * \brief Implements Celestial Database
 * \authors Steve Silber
 * \date 2018-11
 */

#pragma once

#include <iostream>

#include "star.h"
#include "planet.h"
#include "celestialout.h"

struct CelestialDB
{
public:
	static CelestialDB& instance()
	{
		static CelestialDB instance;		// Guaranteed to be destroyed.
		return instance;
	}

	CelestialDB(CelestialDB const&) = delete;
	void operator=(CelestialDB const&) = delete;

private:
	CelestialDB() {}

public:

	bool find_planet(char *name)
	{
		Planet p(name);

		auto[rightasc, declination] = get_planet_rad(p);
		output_coords(name, rightasc, declination);

		return true;
	}

	bool find_star(char *name)
	{
		Star s(name);
		output_coords(name, s.get_rightasc(), s.get_declination());

		return true;
	}

	void output_coords(char *name, Angle rightasc, Angle declination)
	{
		CelestialOut(name, rightasc, declination).update();
	}
};
