#pragma once

#include "Angle.h"
#include "HorizontalCoordinates.h"

class EquatorialCoordinates
{
public:
	EquatorialCoordinates(Angle right_ascension, Angle declination);
	~EquatorialCoordinates();

	Angle get_right_ascension();
	void set_right_ascension(Angle right_ascension);

	Angle get_declination();
	void set_declination(Angle declination);

	HorizontalCoordinates get_horizontal(Angle latitude, Angle longitude, Angle local_sidereal_time);

private:
	Angle _right_ascension;
	Angle _declination;
};

