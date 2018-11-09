#pragma once

#include <string>
#include <map>

class Angle
{
public:
	Angle();
	Angle(double radians);
	Angle(double degrees, double arcminutes, double arcseconds);
	~Angle();

	//radians are best, really
	double get_radians();

	double get_degrees();

	//total angle, measured in arcminutes (e.g. 20 degrees = 20*60 arcminutes)
	double get_arcminutes();

	//total angle, measured in arcseconds (e.g. 20 degrees = 20*60*60 arcseconds)
	double get_arcseconds();

	//angle as represented in many celestial databases (e.g. 10 deg 37 arcmin 12.32 arcsec)
	//access using result["degrees"], result["arcminutes"], result["arcseconds"]
	std::map<std::string, double> get_degrees_arcminutes_arcseconds();

 private:
	 double _angle_radians;
};