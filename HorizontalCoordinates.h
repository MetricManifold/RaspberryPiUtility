#pragma once

#include "Angle.h"
#include "EquatorialCoordinates.h"

class HorizontalCoordinates
{
public:
	HorizontalCoordinates(Angle altitude, Angle azimuth);
	~HorizontalCoordinates();

	Angle get_altitude();
	void set_altitude(Angle altitude);

	Angle get_azimuth();
	void set_azimuth(Angle azimuth);

	EquatorialCoordinates get_equatorial(Angle latitude, Angle longitude, Angle local_sidereal_time);

private:
	Angle _altitude;
	Angle _azimuth;
};

