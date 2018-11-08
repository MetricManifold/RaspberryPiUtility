#pragma once


#include <iostream>
#include <thread>
#include <mutex>

#include "serialport.h"
#include "gpio.h"

#define PORT_NAME "\\\\.\\COM20"
#define STR(X) #X

#define MSG_YAW_POS 9
#define MSG_PITCH_POS 7
#define MSG_LENGTH (MSG_YAW_POS + MSG_PITCH_POS)
#define MSG_FORMAT ("%" STR(MSG_YAW_POS) "s%" STR(MSG_PITCH_POS) "s")

#define PIN_READ 4
#define PIN_POS 17
#define PIN_VEL 21
#define PIN_STATE 23
#define PIN_STOP 25

#define BAD_READ (std::pair{ -1.0, -1.0 })

/*
 * the MotorControl class acts as the driver interface; it ensures
 * incoming and outgoing data is normalized and within range before it
 * is injested by the driver.
 */


struct MotorControl
{
public:
	MotorControl(MotorControl const&) = delete;
	void operator=(MotorControl const&) = delete;

	std::pair<double, double> read_pos();
	void all_stop();
	bool write_pos(int, int);
	bool write_vel(int, int);
	bool is_free();

	friend static MotorControl &motor_driver();

private:

	SerialPort const serial;		// serial connection to the arduino
	Pin const
		pread,						// pin to request a read
		ppos,						// pin to indicate position communication
		pvel,						// pin to indicate velocity communication
		pstate,						// pin to indicate the state
		pstop;						// pin to indicate stop communication

	std::mutex mm;					// mutex for control to check the pin state

	MotorControl() :
		serial{ SerialPort(PORT_NAME) },
		pread{ Pin(PIN_READ, "out") },
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
