/*!
 *	\class EquatorialCoordinates
 *	\file EquatorialCoordinates.h
 *	\brief EquatorialCoordinates class represents celestial coordinates in the equatorial (right ascension-declination) system
  *	\details Implements EquatorialCoordinates.h header
 *	\authors Matt Abado, Christian Wrona
 *	\date 2018-11
 */

#include "EquatorialCoordinates.h"

#include <math.h>

 /*!
  * \brief constructor method for EquatorialCoordinates using right ascension and declination Angles
  * \param altitude right_ascension the altitude right ascension as an Angle
  * \param declination represents the declination component as an Angle
  */
EquatorialCoordinates::EquatorialCoordinates(Angle right_ascension, Angle declination)
{
	this->_right_ascension = right_ascension;
	this->_declination = declination;
}

EquatorialCoordinates::~EquatorialCoordinates() 
{

}

/*!
 * \brief getter method for the right ascension
 * \return the right ascension as an Angle
 */
Angle EquatorialCoordinates::get_right_ascension()
{
	return this->_right_ascension;
}

/*!
 * \brief setter method for the right ascension
 * \param right_ascension represents the right ascension as an Angle
 */
void EquatorialCoordinates::set_right_ascension(Angle right_ascension)
{
	this->_right_ascension = right_ascension;
}

/*!
 * \brief getter method for the declination
 * \return the declination as an Angle
 */
Angle EquatorialCoordinates::get_declination()
{
	return this->_declination;
}

/*!
 * \brief setter method for the declination
 * \param declination represents the declination as an Angle
 */
void EquatorialCoordinates::set_declination(Angle declination)
{
	this->_declination = declination;
}

/*!
 * \brief convert coordinates to the horizontal system (see: http://star-www.st-and.ac.uk/~fv/webnotes/chapter7.htm )
 * \param latitude represents the user's latitude as an Angle
 * \param longitude represents the user's longitude as an Angle
 * \param local_sidereal_time represents the current local sidereal time as an Angle
 * \return the same celestial coordinates, represented in the horizontal system
 */
/*
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
*/