#pragma once


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#include "serialport.h"
#include "gpio.h"

#define PORT_NAME "\\\\.\\COM1"
#define STR(X) #X

#define MSG_YAW_POS 9
#define MSG_PITCH_POS 7
#define MSG_LENGTH (MSG_YAW_POS + MSG_PITCH_POS)
#define MSG_FORMAT ("%" STR(MSG_YAW_POS) "s%" STR(MSG_PITCH_POS) "s")

#define BAD_READ (std::pair{ -1.0, -1.0 })

/*!
 *    \class MotorControl
 *    \file motorcontrol.h
 *    \brief the MotorControl class acts as the driver interface; it ensures
 *			incoming and outgoing data is normalized and within range before it
 *			is injested by the driver.
 *    \authors Steve Silber, Alex Yan
 *    \date 2018-11
 *
 */
struct MotorControl
{
public:
	MotorControl(MotorControl const&) = delete;
	void operator=(MotorControl const&) = delete;

	/*
	 * returns the position read in from the serial port, doesn't
	 * trigger any pins
	 * @returns Pair object containing the yaw and pitch, respectively
	 */
	std::pair<double, double> read_pos();

	/*
	 * calls the all stop command by flipping the required pin to HIGH;
	 * this is blocking until activity pin is LOW
	 */
	void all_stop();

	/*
	 * writes the provided yaw and pitch to the serial port to give the motors
	 * a new direction, will not write if the resource is active
	 * @param yaw The new yaw position for the telescope
	 * @param pitch The new pitch position for the telescope
	 * @returns Whether the write is successful (true) or not (false)
	 */
	bool write_pos(int, int);

	/*
	 * writes the provided yaw and pitch to the serial port to give the motors
	 * a new velocity, will not write if the resource is active
	 * @param yaw The new yaw velocity for the telescope
	 * @param pitch The new pitch velocity for the telescope
	 * @returns Whether the write is successful (true) or not (false)
	 */
	bool write_vel(int, int);

	/*
	 * returns whether the activity pin is HIGH or LOW
	 * @returns If the activity pin is HIGH then false, LOW then true
	 */
	bool is_free();

	/*
	 * let the motor driver function, which returns the state, easily access
	 * members from this class
	 */
	friend static MotorControl &motor_driver();

private:

	SerialPort const serial;		// serial connection to the arduino
	Pin const
		ppos,						// pin to indicate position communication
		pvel,						// pin to indicate velocity communication
		pstate,						// pin to indicate the state
		pstop;						// pin to indicate stop communication

	std::mutex mm;					// mutex for control to check the pin state

	/*
	 * motor control constructor that initializes all pins and says whether there
	 * is a connection or not
	 */
	MotorControl() :
		serial{ SerialPort(PORT_NAME) },
		ppos{ Pin(PIN_POS, "out") },
		pvel{ Pin(PIN_VEL, "out") },
		pstate{ Pin(PIN_STATE, "in") },
		pstop{ Pin(PIN_STOP, "out") }
	{
		if (!serial.has_con())
		{
			printf("No connection to serial port '%s'!\n", PORT_NAME);
		}
		else
		{
			printf("Connection to serial '%s' established\n", PORT_NAME);
		}

		
	}


};

static MotorControl &motor_driver()
{
	static MotorControl state;
	return state;
}
