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

enum class object_type { PLANET, STAR };

class CelestialIn : public BridgeIn<object_type, std::string, std::string>
{
	using BridgeIn<object_type, std::string, std::string>::BridgeIn;

public:
	CelestialIn(object_type t, TelescopeUI * const w) :
		BridgeIn(t, w->get_star_input(), w->get_planet_input())
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
#ifdef _WIN64
		auto[t, star_name, planet_name] = vs;
#else
                auto t = std::get<0>(vs);
                auto star_name = std::get<1>(vs);
                auto planet_name = std::get<2>(vs);

#endif
		switch (t)
		{
		case object_type::PLANET:

			CelestialDB::instance().find_planet((char *)planet_name.c_str());
			break;

		case object_type::STAR:

			CelestialDB::instance().find_star((char *)star_name.c_str());
			break;

		}
	}

};
