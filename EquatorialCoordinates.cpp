#include "EquatorialCoordinates.h"

#include <math.h>

EquatorialCoordinates::EquatorialCoordinates(Angle right_ascension, Angle declination)
{
	this->_right_ascension = right_ascension;
	this->_declination = declination;
}

EquatorialCoordinates::~EquatorialCoordinates() 
{

}


Angle EquatorialCoordinates::get_right_ascension()
{
	return this->_right_ascension;
}

void EquatorialCoordinates::set_right_ascension(Angle right_ascension)
{
	this->_right_ascension = right_ascension;
}

Angle EquatorialCoordinates::get_declination()
{
	return this->_declination;
}

void EquatorialCoordinates::set_declination(Angle declination)
{
	this->_declination = declination;
}

HorizontalCoordinates EquatorialCoordinates::get_horizontal(Angle latitude, Angle longitude, Angle local_sidereal_time)
{
	//for convenience, let's use radians
	double latitude_radians = latitude.get_radians();
	double longitude_radians = longitude.get_radians();
	double local_sidereal_time_radians = local_sidereal_time.get_radians();
	double right_ascension_radians = _right_ascension.get_radians();
	double declination_radians = _declination.get_radians();

	double hour_angle = local_sidereal_time_radians - right_ascension_radians;
	double sin_altitude = sin(declination_radians)*sin(latitude_radians) + cos(declination_radians)*cos(latitude_radians)*cos(hour_angle);
	double altitude = asin(sin_altitude);

	double sin_azimuth = -1 * sin(hour_angle)*cos(latitude_radians) / cos(latitude_radians);
	double azimuth = asin(sin_azimuth);

	return HorizontalCoordinates(Angle(altitude), Angle(azimuth));
}