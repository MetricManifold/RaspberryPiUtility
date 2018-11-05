#pragma once

#include <tuple>

#include "backendwrapper.h"

template<typename ...Args>
class BridgeIn
{
protected:
	static Backend * b;
	std::tuple<Args...> vs;

	BridgeIn(Args ...args) : vs{ args... } { }

	virtual void slot() = 0;

public:
	static void init(Backend * b) 
	{ 
		BridgeIn<Args...>::b = b; 
	}
};
