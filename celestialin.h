/*!
 * \class CelestialIn
 * \file celestialin.h
 * \brief Bridge between celestialdb class and UI
 * \authors Steve Silber, Alex Yan
 * \date 2018-11
 */


#pragma once

#include "bridgein.h"
#include "telescopeui.h"
#include "control.h"
#include "celestialdb.h"

class CelestialIn : public BridgeIn<std::string>
{
	using BridgeIn<std::string>::BridgeIn;

public:
	CelestialIn(TelescopeUI * const w) :
		BridgeIn(w->get_star_input())
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
		auto[object_name] = vs;
		Star((char *)object_name.c_str());
	}

};
