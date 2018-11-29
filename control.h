#pragma once

#include <utility>
#include <thread>

#include "motorcontrol.h"


typedef double Degree;
typedef double RealAngle;

// function that does nothing, helper as default parameter
static void(*__no_fn)() = []() {};


/*!
 *    \namespace tmc
 *    \file control.h
 *    \brief the API for the Telescope Motor Control
 *			there is no function to read the current coordinates as the design
 *			does not allow the motor control to be polled
 *    \authors Steve Silber, Alex Yan
 *    \date 2018-11
 *
 */
namespace tmc
{
	/*
	 * takes a pair of coordinates as a destination to move the telescope to
	 * returns the coordinates before initiating the move
	 * this function is NONBLOCKING
	 * @param yaw The yaw value to act as new position in horizontal direction
	 * @param pitch The pitch value to act as new position in vertical direction
	 * @param end_fn The function that's called when the motor activity finishes
	 * @param fn_args Arguments passed to the end_fn function
	 */
	template<typename T = decltype(__no_fn), typename ...Args>
	bool to_coords(Degree yaw, Degree pitch, T end_fn = __no_fn, Args ...fn_args)
	{
		bool r = motor_driver().write_pos(yaw, pitch);
		if (r)
		{
			std::thread([&]()
			{
				while (!motor_driver().is_free());
				//__no_fn(fn_args...);
			}).detach();
		}
		
		return r;
	}

	/*
	 * takes a pair of velocity coordinates, which will persistently move the
	 * telescope until stop is called or end of freedom of motion is reached
	 * returns the coordinates before initiating the translation
	 * this function is NONBLOCKING
	 * @param yaw The yaw value to act as speed in horizontal direction
	 * @param pitch The pitch value to act as speed in vertical direction
	 * @param end_fn The function that's called when the motor activity finishes
	 * @param fn_args Arguments passed to the end_fn function
	 */
	template<typename T = decltype(__no_fn), typename ...Args>
	bool set_velocity(Degree yaw, Degree pitch, T end_fn = __no_fn, Args ...fn_args)
	{
		bool r = motor_driver().write_vel(yaw, pitch);
		if (r)
		{
			std::thread([&]()
			{
				while (!motor_driver().is_free());
				//__no_fn(fn_args...);
			}).detach();
		}

		return r;
	}

	std::pair<Degree, Degree> get_coords();

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