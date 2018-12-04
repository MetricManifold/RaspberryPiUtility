/*!
 *	\class HorizontalCoordinates
 *	\file HorizontalCoordinates.cpp
 *	\brief HorizontalCoordinates class represents celestial coordinates in the horizontal (altitude-azimuth) system
 *	\details Implements HorizontalCoordinates.h header
 *	\authors Matt Abado, Christian Wrona
 *	\date 2018-11
 */

#include "HorizontalCoordinates.h"
#include "EquatorialCoordinates.h"

#include <math.h>

 /*!
  * \brief constructor method for HorizontalCoordinates using altitude and azimuth Angles
  * \param altitude represents the altitude component as an Angle
  * \param azimuth represents the azimuth component as an Angle
  */
HorizontalCoordinates::HorizontalCoordinates(Angle altitude, Angle azimuth)
{
	this->_altitude = altitude;
	this->_azimuth = azimuth;
}

HorizontalCoordinates::~HorizontalCoordinates() 
{

}

/*!
 * \brief getter method for the altitude
 * \return the altitude as an Angle
 */
Angle HorizontalCoordinates::get_altitude()
{
	return this->_altitude;
}

/*!
 * \brief setter method for the altitude
 * \param altitude represents the altitude as an Angle
 */
void HorizontalCoordinates::set_altitude(Angle altitude)
{
	this->_altitude = altitude;
}

/*!
 * \brief getter method for the azimuth
 * \return the azimuth as an Angle
 */
Angle HorizontalCoordinates::get_azimuth()
{
	return this->_azimuth;
}

/*!
 * \brief setter method for the azimuth
 * \param azimuth represents the altitude as an Angle
 */
void HorizontalCoordinates::set_azimuth(Angle azimuth)
{
	this->_azimuth = azimuth;
}

/*!
 * \brief convert coordinates to the equatorial system (see: http://star-www.st-and.ac.uk/~fv/webnotes/chapter7.htm )
 * \param latitude represents the user's latitude as an Angle
 * \param longitude represents the user's longitude as an Angle
 * \param local_sidereal_time represents the current local sidereal time as an Angle
 * \return the same celestial coordinates, represented in the equatorial system
 */
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

