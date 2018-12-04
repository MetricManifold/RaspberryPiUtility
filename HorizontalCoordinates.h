/*!
 *	\class HorizontalCoordinates
 *	\file HorizontalCoordinates.h
 *	\brief HorizontalCoordinates class represents celestial coordinates in the horizontal (altitude-azimuth) system
 *	\authors Matt Abado, Christian Wrona
 *	\date 2018-11
 */

#pragma once

#include "Angle.h"

class EquatorialCoordinates;

class HorizontalCoordinates
{
public:

	/*!
	 * \brief constructor method for HorizontalCoordinates using altitude and azimuth Angles
	 * \param altitude represents the altitude component as an Angle
	 * \param azimuth represents the azimuth component as an Angle
	 */
	HorizontalCoordinates(Angle altitude, Angle azimuth);

	~HorizontalCoordinates();

	/*!
	 * \brief getter method for the altitude
	 * \return the altitude as an Angle
	 */
	Angle get_altitude();

	/*!
	 * \brief setter method for the altitude
	 * \param altitude represents the altitude as an Angle
	 */
	void set_altitude(Angle altitude);

	/*!
	 * \brief getter method for the azimuth
	 * \return the azimuth as an Angle
	 */
	Angle get_azimuth();

	/*!
	 * \brief setter method for the azimuth
	 * \param azimuth represents the altitude as an Angle
	 */
	void set_azimuth(Angle azimuth);

	/*!
	 * \brief convert coordinates to the equatorial system (see: http://star-www.st-and.ac.uk/~fv/webnotes/chapter7.htm )
	 * \param latitude represents the user's latitude as an Angle
	 * \param longitude represents the user's longitude as an Angle
	 * \param local_sidereal_time represents the current local sidereal time as an Angle
	 * \return the same celestial coordinates, represented in the equatorial system
	 */
	EquatorialCoordinates get_equatorial(Angle latitude, Angle longitude, Angle local_sidereal_time);

private:
	Angle _altitude;  ///< internal representation of the altitude
	Angle _azimuth;   ///< internal representation of the azimuth
};

