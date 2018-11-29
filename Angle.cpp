/*!
 *	\class Angle
 *	\file Angle.cpp
 *	\brief Angle class represents angular measurements and allows conversion between different units
  *	\details Implements Angle.h header
 *	\authors Matt Abado, Christian Wrona
 *	\date 2018-11
 */

#include "Angle.h"

#define _USE_MATH_DEFINES
#include <math.h>

/*!
 * \brief null constructor method for an Angle -- does not create a meaningful Angle
 */
Angle::Angle() 
{ 

}

/*!
 * \brief constructor method for an Angle using radians
 * \param radians represents the angle in radians
 */
Angle::Angle(double radians)
{
	this->_angle_radians = fmod(radians, 2 * M_PI); //clip to [0, 2*pi) radians
}

/*!
 * \brief constructor method for an Angle using degrees, arcminutes, arcseconds
 * \param degrees represents the degree part of the Angle
 * \param arcminutes represents the arcminutes part of the Angle
 * \param arcseconds represents the arcseconds part of Angle
 */
Angle::Angle(double degrees, double arcminutes, double arcseconds)
{
	double total_degrees = degrees + (1.0 / 60.0) * arcminutes + (1.0 / (60.0 * 60.0)) * arcseconds;
	this->_angle_radians = fmod((M_PI / 180.0) * total_degrees,  2 * M_PI); //clip ro [0, 2*pi) radians
}

Angle::~Angle()
{

}

/*!
 * \brief getter method for the Angle, measured in radians
 * \return the Angle, measured in radians
 */
double Angle::get_radians()
{
    return this->_angle_radians;
}

/*!
 * \brief getter method for the Angle, measured in degrees
 * \return the Angle, measured in degrees
 */
double Angle::get_degrees()
{
    return 180 * M_1_PI * this->_angle_radians;
}

/*!
 * \brief getter method for the Angle, measured in arcminutes
 * \return the Angle, measured in arcminutes
 */
double Angle::get_arcminutes()
 {
	 return 60.0 * this->get_degrees();
 }

/*!
 * \brief getter method for the Angle, measured in arcseconds
 * \return the Angle, measured in arcseconds
 */
double Angle::get_arcseconds()
 {
	 return 60.0 * 60.0 * this->get_degrees();
 }

/*!
 * \brief getter method for the Angle, measured in (degrees, arcminutes, arcseconds) -- (e.g. 10 deg 37 arcmin 12.32 arcsec)
 * \return the Angle, measured in "degrees", "arcminutes", and "arcseconds" (access each component with its respective key)
 */
std::map<std::string, double> Angle::get_degrees_arcminutes_arcseconds()
 {
	 std::map<std::string, double> components;
	 components["degrees"] = floor(get_degrees());
	 components["arcminutes"] = floor(get_arcminutes());
	 components["arcseconds"] = get_arcseconds();
	 return components;
 }