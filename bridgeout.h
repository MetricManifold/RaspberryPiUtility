#pragma once

#include <tuple>

#include "raspberrypiutility.h"
#include "backendwrapper.h"

template<typename ...Args>
class BridgeOut
{
protected:
	std::tuple<Args...> vs;
	BridgeOut(Args... args) : vs{ args... } {}

public:
	virtual void update(RaspberryPiUtility * const) = 0;
};