#pragma once


#define ARDUINO_WAIT_TIME 2000

#define MAX_DATA_LENGTH 255


#ifdef _WIN64

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#endif

class SerialPort
{

private:

	HANDLE handler;
	bool connected;
	COMSTAT status;
	DWORD errors;

public:

	SerialPort(char *port);
	~SerialPort();

	int read(char *buffer, unsigned int buf_size);
	bool write(char *buffer, unsigned int buf_size);
	bool isConnected();

};


