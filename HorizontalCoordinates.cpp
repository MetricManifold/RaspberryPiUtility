#include "HorizontalCoordinates.h"

#include <math.h>

HorizontalCoordinates::HorizontalCoordinates(Angle altitude, Angle azimuth)
{
	this->_altitude = altitude;
	this->_azimuth = azimuth;
}

HorizontalCoordinates::~HorizontalCoordinates() 
{

}


Angle HorizontalCoordinates::get_altitude()
{
	return this->_altitude;
}

void HorizontalCoordinates::set_altitude(Angle altitude)
{
	this->_altitude = altitude;
}

Angle HorizontalCoordinates::get_azimuth()
{
	return this->_azimuth;
}

void HorizontalCoordinates::set_azimuth(Angle azimuth)
{
	this->_azimuth = azimuth;
}

EquatorialCoordinates HorizontalCoordinates::get_equatorial(Angle latitude, Angle longitude, Angle local_sidereal_time)
{
	//for convenience, let's use radians
	double latitude_radians = latitude.get_radians();
	double longitude_radians = longitude.get_radians();
	double local_sidereal_time_radians = local_sidereal_time.get_radians();
	double altitude_radians = _altitude.get_radians();
	double azimuth_radians = _azimuth.get_radians();

	double sin_declination = sin(altitude_radians)*sin(latitude_radians) + cos(altitude_radians)*cos(latitude_radians)*cos(azimuth_radians);
	double declination = asin(sin_declination);

	double sin_hour_angle = -1 * sin(azimuth_radians)*cos(altitude_radians) / cos(declination);
	double hour_angle = asin(sin_hour_angle);
	double right_ascension = local_sidereal_time_radians - hour_angle;

	return EquatorialCoordinates(Angle(right_ascension), Angle(declination));
}