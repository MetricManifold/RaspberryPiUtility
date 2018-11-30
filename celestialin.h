#pragma once

#include "bridgein.h"
#include "telescopeui.h"
#include "control.h"
#include "celestialdb.h"
#include "star.h"

class CelestialIn : public BridgeIn<std::string>
{
	using BridgeIn<std::string>::BridgeIn;

public:
	CelestialIn(TelescopeUI * const w) :
		BridgeIn("")
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
		Star(object_name.c_str());
	}

};
