/*!
 * \class Planet
 * \file planet.h
 * \brief Part of Celestial database. Retrieves planet object from webpage.
 * \authors Steve Silber
 * \date 2018-11
 */

 // http://asa.usno.navy.mil/static/files/2013/Osculating_Elements_2013.txt

#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <utility>

#include "downloadpage.h"
#include "coordinates.h"
#include "Angle.h"

#define PLANET_HOST_NAME "en.wikipedia.org"
#define PLANET_URL "wiki/"
#define PLANET_READ_FILE "Osculating_Elements_2013"
#define PLANET_ID "planet"
#define PLANET_FMT PLANET_ID " "

// The date of Epoch J2000
#define WIKI_MINUTE 0
#define WIKI_HOUR 12
#define WIKI_DAY 1
#define WIKI_MONTH 1
#define WIKI_YEAR 2000

class Planet
{
	char *name;
	char *url;

	double
		M,		// mean anomaly
		i,		// inclination
		o,		// longitude of the ascending node
		p,		// longitude of the perihelion
		a,		// mean distance
		n,		// daily motion
		e,		// eccentricy
		L;		// mean longitude

	struct
	{
		int
			minute,
			hour,
			day,
			month,
			year;
	} epoch;
	
	bool state;

public:

	/**
	 * Creates a planet object using the state variables
	 * this constructor always assumes the J2000 epoch
	 */
	Planet(double i, double o, double p, double a, double n, double e, double L);

	/*
	 * creates a planet by reading data from wikipedia
	 * wikipedia uses the j2000 epoch
	 */
	Planet(char *name);

	~Planet();

	/*
	 * perform a calculation using the orbital parameters to return the right ascension
	 * and declination in terms of orbital coordinates
	 * always returns ra/d in terms of the current time
	 *
	 * source
	 * https://www.hackster.io/30506/calculation-of-right-ascension-and-declination-402218
	 */
	std::pair<Angle, Angle> get_equatorial_angle();

private:
	void print_info(FILE *f)
	{

	}

};

