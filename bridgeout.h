/*!
 * \class BridgeOut
 * \file BridgeOut.h
 * \brief Provides support for Backend classes
 * \authors Steve Silber
 * \date 2018-11
 */

#pragma once

#include <tuple>

#include "telescopeui.h"

template<typename ...Args>
class BridgeOut
{
protected:
	static TelescopeUI * w;
	std::tuple<Args...> vs;

	BridgeOut(Args... args) : vs{ args... } { }

public:
	virtual void update() = 0;
	static void init(TelescopeUI * w)
	{
		BridgeOut<Args...>::w = w;
	}
};

