/*!
 *	\class Angle
 *	\file Angle.h
 *	\brief Angle class represents angular measurements and allows conversion between different units
 *	\authors Matt Abado, Christian Wrona
 *	\date 2018-11
 */

#pragma once

#include <string>
#include <map>

class Angle
{
public:

	/*!
	 * \brief null constructor method for an Angle -- does not create a meaningful Angle
	 */
	Angle();

	/*!
	 * \brief constructor method for an Angle using radians
	 * \param radians represents the angle in radians
	 */
	Angle(double radians);

	/*!
	 * \brief constructor method for an Angle using degrees, arcminutes, arcseconds
	 * \param degrees represents the degree part of the Angle
	 * \param arcminutes represents the arcminutes part of the Angle
	 * \param arcseconds represents the arcseconds part of Angle
	 */
	Angle(double degrees, double arcminutes, double arcseconds);

	~Angle();

	/*!
	 * \brief getter method for the Angle, measured in radians
	 * \return the Angle, measured in radians
	 */
	double get_radians();

	/*!
	 * \brief getter method for the Angle, measured in degrees
	 * \return the Angle, measured in degrees
	 */
	double get_degrees();

	/*!
	 * \brief getter method for the Angle, measured in arcminutes
	 * \return the Angle, measured in arcminutes
	 */
	double get_arcminutes();

	/*!
	 * \brief getter method for the Angle, measured in arcseconds
	 * \return the Angle, measured in arcseconds
	 */
	double get_arcseconds();

	/*!
	 * \brief getter method for the Angle, measured in (degrees, arcminutes, arcseconds) -- (e.g. 10 deg 37 arcmin 12.32 arcsec)
	 * \return the Angle, measured in "degrees", "arcminutes", and "arcseconds" (access each component with its respective key)
	 */
	std::map<std::string, double> get_degrees_arcminutes_arcseconds();

 private:
	 double _angle_radians; ///< internal representation of the angle
};