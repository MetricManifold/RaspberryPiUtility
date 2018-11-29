/*!
 *	\class EquatorialCoordinates
 *	\file EquatorialCoordinates.h
 *	\brief EquatorialCoordinates class represents celestial coordinates in the equatorial (right ascension-declination) system
 *	\authors Matt Abado, Christian Wrona
 *	\date 2018-11
 */

#pragma once

#include "Angle.h"
#include "HorizontalCoordinates.h"

class EquatorialCoordinates
{
public:

	/*!
	 * \brief constructor method for EquatorialCoordinates using right ascension and declination Angles
	 * \param altitude right_ascension the altitude right ascension as an Angle
	 * \param declination represents the declination component as an Angle
	 */
	EquatorialCoordinates(Angle right_ascension, Angle declination);


	~EquatorialCoordinates();

	/*!
	 * \brief getter method for the right ascension
	 * \return the right ascension as an Angle
	 */
	Angle get_right_ascension();

	/*!
	 * \brief setter method for the right ascension
	 * \param right_ascension represents the right ascension as an Angle
	 */
	void set_right_ascension(Angle right_ascension);

	/*!
	 * \brief getter method for the declination
	 * \return the declination as an Angle
	 */
	Angle get_declination();

	/*!
	 * \brief setter method for the declination
	 * \param declination represents the declination as an Angle
	 */
	void set_declination(Angle declination);

	/*!
	 * \brief convert coordinates to the horizontal system (see: http://star-www.st-and.ac.uk/~fv/webnotes/chapter7.htm )
	 * \param latitude represents the user's latitude as an Angle
	 * \param longitude represents the user's longitude as an Angle
	 * \param local_sidereal_time represents the current local sidereal time as an Angle
	 * \return the same celestial coordinates, represented in the horizontal system
	 */
	HorizontalCoordinates get_horizontal(Angle latitude, Angle longitude, Angle local_sidereal_time);

private:
	Angle _right_ascension;   ///< internal representation of the right ascension
	Angle _declination;		  ///< internal representation of the declination
};

