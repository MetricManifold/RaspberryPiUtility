#pragma once

#include <tuple>

#include "raspberrypiutility.h"

template<typename ...Args>
class BridgeOut
{
protected:
	static RaspberryPiUtility * w;
	std::tuple<Args...> vs;

	BridgeOut(Args... args) : vs{ args... } { }

public:
	virtual void update() = 0;
	static void init(RaspberryPiUtility * w)
	{
		BridgeOut<Args...>::w = w;
	}
};

