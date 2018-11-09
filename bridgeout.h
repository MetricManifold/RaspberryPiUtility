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

