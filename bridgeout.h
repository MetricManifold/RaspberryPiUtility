#pragma once

#include <tuple>

#include "raspberrypiutility.h"
#include "backendwrapper.h"

template<typename ...Args>
class BridgeOut
{
protected:
	static RaspberryPiUtility * const w;
	std::tuple<Args...> vs;
	BridgeOut(Args... args, RaspberryPiUtility * const w = nullptr) : vs{ args... }, w{ (w) ? w : this->w } {}

public:
	virtual void update(RaspberryPiUtility * const) = 0;
};