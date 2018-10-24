#pragma once

#include "control_in.h"

/*
 * the primary class for wrapping together all the backend objects and functions
 * used to talk between those objects
 */

class Backend
{

private:

	/*
	 * objects used in the backend services
	 */

public:
	/*
	 * constructor equipped with initializer list to initialize all the backend objects
	 */
	Backend()
	{

	}



	/*
	 * the update functions, overloaded by input state
	 */
	void update(ControlIn in)
	{

	}

};