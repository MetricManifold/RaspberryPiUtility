#pragma once

#include <utility>
#include <ctime>
#include <cmath>

#include "planet.h"
#include "coordinates.h"

static Planet Earth{
	0.0,
	0.0,
	103.147,
	1.0000,
	0.985611,
	0.016679,
	324.5489 };

/*
 * source
 https://www.hackster.io/30506/calculation-of-right-ascension-and-declination-402218
 */
std::pair<Angle, Angle> get_planet_rad(Planet &pl)
{


	auto juliandate = [](
		unsigned int year, 
		unsigned int month, 
		unsigned int day, 
		unsigned int hours, 
		unsigned int minutes) -> double
	{
		// declare variables to be used in converting date
		double julianDate;
		int I;
		int J;
		int K;

		I = year;
		J = month;
		K = day;

		// formula to convert gregorian date to julian date
		julianDate = K - 32075 + 1461 * (I + 4800 + (J - 14) / 12) / 4 + 367 *
			(J - 2 - (J - 14) / 12 * 12) * 2 / 12 - 3 * ((I + 4900 + (J - 14) / 12) / 100) / 4;

		julianDate += (hours + minutes / 60.0) / 24.0;
		return julianDate;
	};


	// get the local time
	time_t tt;
	struct tm *ti;

	// store the local time
	time(&tt);
	ti = localtime(&tt);

	/*
	double d = 
		juliandate(ti->tm_year + 1900, ti->tm_mon, ti->tm_mday, ti->tm_hour, ti->tm_min)
		- juliandate(YEAR, MONTH, DAY, HOUR, MINUTE);
		*/


	double d =
		juliandate(2016, 3, 1, 12, 0)
		- juliandate(2013, 8, 16, 12, 0);


	/*
	 * Mean anomaly:
	 * n is daily motion
	 * d is the number of days since the date of the elements
	 * L is the mean longitude
	 * p is the longitude of perihelion
	 * M should be in range 0 to 360 degrees, add or subtract
	 * multiples of 360 to bring M into this range.
	 */
	double M = pl.n * d + pl.L - pl.p;

	/*
	 * True anomoly
	 * v is true anomaly
     * M is mean anomaly
     * e is eccentricity
	 * using the expanded Taylor series
	 */
	double v = M + (2 * pl.e - 0.25 *pow(pl.e, 3) + 5 / 96 * pow(pl.e, 5)) * sin(M) +
		(1.25 * pow(pl.e, 2) - 11 / 24 * pow(pl.e, 4)) * sin(2 * M) +
		(13 / 12 * pow(pl.e, 3) - 43 / 64 * pow(pl.e, 5)) * sin(3 * M) +
		103 / 96 * pow(pl.e, 4) * sin(4 * M) + 1097 / 960 * pow(pl.e, 5) * sin(5 * M);

	/*
	 * radius vector of the planet
	 */
	double r = pl.a * (1 - pl.e * pl.e) / (1 + pl.e * cos(v));

	/*
	 * Heliocentric coordinates
	 * r is radius vector
	 * v is true anomaly
	 * o is longitude of ascending node
	 * p is longitude of perihelion
	 * i is inclination of plane of orbit
	 * the quantity v + p - o is the angle of the planet measured
	 * in the plane of the orbit from the ascending node
	 */
	double X = r * (cos(pl.o) * cos(v + pl.p - pl.o) - sin(pl.o) * sin(v + pl.p - pl.o) * cos(pl.i));
	double Y = r * (sin(pl.o) * cos(v + pl.p - pl.o) + cos(pl.o) * sin(v + pl.p - pl.o) * cos(pl.i));
	double Z = r * (sin(v + pl.p - pl.o) * sin(pl.i));

	/*
	 * Heliocentric coordinates for Earth
	 * r is radius vector of Earth
	 * v is true anomaly for Earth
	 * p is longitude of perihelion for Earth
	 */
	double Xe = r * cos(v + pl.p);
	double Ye = r * sin(v + pl.p);
	double Ze = 0;

	/*
	 * normalized coordinates, namely the
	 * geocentric ecliptic coodinates
	 */
	double Xp = X - Xe;
	double Yp = Y - Ye;
	double Zp = Z - Ze;

	/*
	 * convert to geocentric equatorial
	 */
	double ec = 23.439292; // obliquity of the elipctic
	double Xq = Xp;
	double Yq = Yp * cos(ec) - Zp * sin(ec);
	double Zq = Yp * sin(ec) + Zp * cos(ec);

	/*
	 * right ascension
	 */
	double alpha = atan2(Yq, Xq);

	/*
	 * declination
	 */
	double delta = atan2(Zq, sqrt(Xq * Xq + Yq * Yq));

	return { alpha / 15, delta };

}

