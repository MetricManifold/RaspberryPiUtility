#pragma once

#include <tuple>

#include "raspberrypiutility.h"
#include "backendwrapper.h"

template<typename ...Args>
class BridgeIn
{
protected:
	Backend * const b;
	std::tuple<Args...> vs;
	BridgeIn(Backend * const b, Args ...args) : vs{ args... }, b{ b } { }
	
	virtual void slot() = 0;
};