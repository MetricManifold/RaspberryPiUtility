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
#include "control.h"
#include "controlout.h"

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

	/*
	 * given the name of the planet, it creates the temporary object
	 * in order to read from online, and outputs the coordinates to user
	 */
	bool find_planet(char *name);

	/*
	 * given the name of the star, it creates the temporary object
	 * in order to read from online, and outputs the coordinates to user
	 */
	bool find_star(char *name);

	/*
	 * Given the right ascension and declination, it will
	 * output the corresponding degree measure to the user
	 */
	void output_body_details(char *name, Angle rightasc, Angle declination);

	void output_coords(Angle altitude, Angle azimuth);
	void write_coordinate_data(Angle altitude, Angle azimuth);

	bool turn_to_coordinates(Angle altitude, Angle azimuth);
	bool turn_with_velocity(Angle altitude, Angle azimuth);
};
