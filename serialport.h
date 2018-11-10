#pragma once

#define ARDUINO_WAIT_TIME 200

#define PORT_NAME "\\\\.\\COM1"
#ifdef _WIN64

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "gpio.h"

#endif


/*!
 *    \class SerialPort
 *    \file serialport.h
 *    \brief the driver for the Serial port enabling reading and writing, this
 *			is done in a blocking way
 *    \authors Steve Silber, Alex Yan
 *    \date 2018-11
 */
class SerialPort
{

private:

	/*
	 * ensure these variables are initialized only on windows systems
	 */
#ifdef _WIN64
	bool connected;
	HANDLE handler;
#endif

public:
	
	SerialPort(char const *port);
	~SerialPort();

	/*
	 * read the data from the arduino port
	 * @buffer The data to read from the serial port
	 * @buf_size The size of the data buffer in bytes
	 * @returns Integer representing the bytes that have been read in
	 */
	int read(char *buffer, unsigned int buf_size) const;

	/*
	 * write the data into the arduio port
	 * @buffer The data to write into the serial port
	 * @buf_size The size of the data buffer in bytes
	 * @returns Whether the write is successful (true) or not (false)
	 */
	bool write(char *buffer, unsigned int buf_size) const;

	/*
	 * verify the connection is established
	 * @returns Whether there is a connection (true) or not (false) to port
	 */
	bool has_con() const;

};


