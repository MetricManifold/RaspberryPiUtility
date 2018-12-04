#include "celestialdb.h"

bool CelestialDB::find_planet(char *name)
{
	Planet p(name);

	auto[rightasc, declination] = p.get_equatorial_angle();
	output_coords(name, rightasc, declination);
	return true;
}

bool CelestialDB::find_star(char *name)
{
	Star s(name);
	output_coords(name, s.get_rightasc(), s.get_declination());
	return true;
}

void CelestialDB::output_coords(char *name, Angle rightasc, Angle declination)
{
	CelestialOut(name, rightasc, declination).update();
}

bool CelestialDB::turn_to_coordinates(Angle altitude, Angle azimuth)
{
	return true;
}
