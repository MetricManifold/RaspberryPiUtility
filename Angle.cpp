#include "Angle.h"

#define _USE_MATH_DEFINES
#include <math.h>

Angle::Angle() 
{ 

}

Angle::Angle(double radians)
{
	this->_angle_radians = fmod(radians, 2 * M_PI); //clip to [0, 2*pi) radians
}


Angle::Angle(double degrees, double arcminutes, double arcseconds)
{
	double total_degrees = degrees + (1.0 / 60.0) * arcminutes + (1.0 / (60.0 * 60.0)) * arcseconds;
	this->_angle_radians = fmod((M_PI / 180.0) * total_degrees,  2 * M_PI); //clip ro [0, 2*pi) radians
}

Angle::~Angle()
{

}

double Angle::get_radians()
{
    return this->_angle_radians;
}
double Angle::get_degrees()
{
    return 180 * M_1_PI * this->_angle_radians;
}
double Angle::get_arcminutes()
 {
	 return 60.0 * this->get_degrees();
 }
double Angle::get_arcseconds()
 {
	 return 60.0 * 60.0 * this->get_degrees();
 }
std::map<std::string, double> Angle::get_degrees_arcminutes_arcseconds()
 {
	 std::map<std::string, double> components;
	 components["degrees"] = floor(get_degrees());
	 components["arcminutes"] = floor(get_arcminutes());
	 components["arcseconds"] = get_arcseconds();
	 return components;
 }