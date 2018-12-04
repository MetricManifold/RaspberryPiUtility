#include "celestialdb.h"

bool CelestialDB::find_planet(char *name)
{
	Planet p(name);

	auto[rightasc, declination] = p.get_equatorial_angle();
	output_body_details(name, rightasc, declination);
	return true;
}

bool CelestialDB::find_star(char *name)
{
	Star s(name);
	output_body_details(name, s.get_rightasc(), s.get_declination());
	return true;
}

void CelestialDB::output_coords(Angle altitude, Angle azimuth)
{
	ControlOut(altitude.get_degrees(), azimuth.get_degrees()).update();
}

void CelestialDB::output_body_details(char *name, Angle rightasc, Angle declination)
{
	CelestialOut(name, rightasc, declination).update();
}

bool CelestialDB::turn_to_coordinates(Angle altitude, Angle azimuth)
{
	tmc::to_coords(altitude.get_degrees(), azimuth.get_degrees());

	auto[yaw, pitch] = tmc::get_coords();

	// convert raw user input into coordinates
	Angle altitude_new(yaw / 180.0 * (atan(1) * 4));
	Angle azimuth_new(pitch / 180.0 * (atan(1) * 4));

#ifdef DEBUG

	printf(
		"received response from motor control and new coordinates, conversions are,\n"
		"\tdegrees, '%lf/%lf'\n"
		"\tradians, '%lf/%lf'\n"
		"\tarctime, '%.0lfd %.0lfm %.2lfs/%.0lfd %.0lfm %.2lfs'\n",
		// degrees and radians arguments
		altitude_new.get_degrees(), azimuth_new.get_degrees(),
		altitude_new.get_radians(), azimuth_new.get_radians(),
		// altitude arctime arguments
		altitude_new.get_degrees_arcminutes_arcseconds()["degrees"],
		altitude_new.get_degrees_arcminutes_arcseconds()["minutes"],
		altitude_new.get_degrees_arcminutes_arcseconds()["seconds"],
		// azimuth arctime arguments
		azimuth_new.get_degrees_arcminutes_arcseconds()["degrees"],
		azimuth_new.get_degrees_arcminutes_arcseconds()["minutes"],
		azimuth_new.get_degrees_arcminutes_arcseconds()["seconds"]);

#endif

	output_coords(altitude_new, azimuth_new);

	return true;
}
