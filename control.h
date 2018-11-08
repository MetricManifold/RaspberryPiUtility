#pragma once

#include <utility>
#include <thread>

#include "motorcontrol.h"

/*
 * the API for the Telescope Motor Control
 * there is no function to read the current coordinates as the design
 * does not allow the motor control to be polled
 */

typedef double Degree;
typedef double RealAngle;

extern void(*__no_fn)();
extern bool __queued;
extern std::thread __queue_thread;
extern std::mutex __mm;

namespace tmc
{
	/*
	 * takes a pair of coordinates as a destination to move the telescope to
	 * returns the coordinates before initiating the move
	 */
	template<typename T = decltype(__no_fn), typename ...Args>
	bool to_coords(Degree yaw, Degree pitch, T end_fn = __no_fn, Args ...fn_args)
	{
		if (motor_driver().is_free())
		{
			__queue_thread.join();
			__queue_thread = std::thread([&]()
			{
				{
					std::scoped_lock lck(__mm);
					motor_driver().write_pos(yaw, pitch);
				}
				while (!motor_driver().is_free());
				
				end_fn(fn_args...);
			});
			return true;
		}
		return false;
	}

	/*
	 * takes a pair of velocity coordinates, which will persistently move the
	 * telescope until stop is called or end of freedom of motion is reached
	 * returns the coordinates before initiating the translation
	 */
	template<typename T = decltype(__no_fn), typename ...Args>
	bool set_velocity(Degree yaw, Degree pitch, T end_fn = __no_fn, Args ...fn_args)
	{
		if (motor_driver().is_free())
		{
			__queue_thread.join();
			__queue_thread = std::thread([&]()
			{
				{
					std::scoped_lock lck(__mm);
					motor_driver().write_vel(yaw, pitch);
				}
				while (!motor_driver().is_free());

				end_fn(fn_args...);
			});
			return true;
		}
		return false;
	}

	/*
	 * calls an all stop on the telescope movement, if the telescope isn't moving,
	 * there is no effect
	 * returns the coordinates after stopping
	 * returning the coordinates means that a stop command could be BLOCKING
	 */
	template<typename T = decltype(__no_fn), typename ...Args>
	std::pair<double, double> stop(T on_stop)
	{
		motor_driver().all_stop();
		return motor_driver().read_pos();
	}
}