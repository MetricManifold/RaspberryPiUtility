#pragma once


#define ARDUINO_WAIT_TIME 2000


#ifdef _WIN64

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#endif

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
	 */
	int read(char *buffer, unsigned int buf_size) const;

	/*
	 * write the data into the arduio port
	 */
	bool write(char *buffer, unsigned int buf_size) const;

	/*
	 * verify the connection is established
	 */
	bool has_con() const;

};


