#pragma once

/*!
 * \class ControlIn
 * \file controlIn.h
 * \brief Bridge between motor control and UI
 * \authors Steve Silber
 * \date 2018-11
 */



#pragma once

#include <QDoubleSpinBox>

#include "bridgein.h"
#include "telescopeui.h"
#include "celestialdb.h"

class VelocityIn : public BridgeIn<double, double>
{
	using BridgeIn<double, double>::BridgeIn;

public:
	VelocityIn(TelescopeUI * const w) :
		BridgeIn(w->get_yaw_vel_input(), w->get_pitch_vel_input())
	{
		/*
		 * further modify/transform the pulled values from the ui...
		 */
	}


	/*
	 * the function that actually bridges front end and backend by
	 * acting as the slot for the button press
	 */
	void slot()
	{
		printf("-- VELOCITY INPUT ---------------------------\n");
		auto[yaw, pitch] = vs;
		printf("yaw/pitch input, '%lf/%lf'\n", yaw, pitch);

		// convert raw user input into coordinates
		Angle altitude(yaw / 180.0 * (atan(1) * 4));
		Angle azimuth(pitch / 180.0 * (atan(1) * 4));

#ifdef DEBUG

		printf(
			// print a long formatted string with all conversions demonstrating
			// program acceptance tests
			"converted user input into normalized angle, conversions are,\n"
			"\tdegrees, '%lf/%lf'\n"
			"\tradians, '%lf/%lf'\n"
			"\tarctime, '%.0lfd %.0lfm %.2lfs/%.0lfd %.0lfm %.2lfs'\n",
			// degrees and radians arguments
			altitude.get_degrees(), azimuth.get_degrees(),
			altitude.get_radians(), azimuth.get_radians(),
			// altitude arctime arguments
			altitude.get_degrees_arcminutes_arcseconds()["degrees"],
			altitude.get_degrees_arcminutes_arcseconds()["arcminutes"],
			altitude.get_degrees_arcminutes_arcseconds()["arcseconds"],
			// azimuth arctime arguments
			azimuth.get_degrees_arcminutes_arcseconds()["degrees"],
			azimuth.get_degrees_arcminutes_arcseconds()["arcminutes"],
			azimuth.get_degrees_arcminutes_arcseconds()["arcseconds"]);

#endif

		CelestialDB::instance().turn_with_velocity(altitude, azimuth);
	}

};



