

#include "serialport.h"

#ifdef _WIN64

SerialPort::SerialPort(char const *port)
{
	connected = false;
	handler = CreateFileA(
		static_cast<LPCSTR>(port),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (handler == INVALID_HANDLE_VALUE) {

		if (GetLastError() == ERROR_FILE_NOT_FOUND) 
		{
			printf("Error in serial port: Handle was not attached. Reason: %s not available\n", port);
		}

		else
		{
			printf("Extraneous error while initalizing serial port.");
		}
	}
	else 
	{
		DCB dcbSerialParameters = { 0 };
		if (!GetCommState(handler, &dcbSerialParameters)) 
		{
			printf("Failed to get current serial parameters");
		}
		else 
		{
			dcbSerialParameters.BaudRate = CBR_9600;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.Parity = NOPARITY;
			dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;


			if (!SetCommState(handler, &dcbSerialParameters))
			{
				printf("Error in serial port: Could not set serial port parameters\n");
			}
			else 
			{
				this->connected = true;
				PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(ARDUINO_WAIT_TIME);
			}
		}
	}
}

SerialPort::~SerialPort()
{
	if (this->connected) 
	{
		this->connected = false;
		CloseHandle(handler);
	}
}

int SerialPort::read(char *buffer, unsigned int buf_size) const
{
	COMSTAT status;
	DWORD errors;
	DWORD bytes_read;

	ClearCommError(handler, &errors, &status);

	if (status.cbInQue > 0) 
	{
		unsigned int toRead = (status.cbInQue > buf_size) ? buf_size : status.cbInQue;
		if (ReadFile(handler, buffer, toRead, &bytes_read, NULL))
		{
			return bytes_read;
		}
	}
	return false;
}


bool SerialPort::write(char *buffer, unsigned int buf_size) const
{
	HANDLE handler;
	COMSTAT status;
	DWORD errors;
	DWORD bytes_send;

	if (!WriteFile(handler, (void*)buffer, buf_size, &bytes_send, 0)) 
	{
		ClearCommError(handler, &errors, &status);
		return false;
	}
	else
	{
		return true;
	}
}

#else

SerialPort::SerialPort(char *port)
{

}

SerialPort::~SerialPort()
{

}

int SerialPort::read(char *buffer, unsigned int buf_size)
{

}

bool SerialPort::write(char *buffer, unsigned int buf_size)
{

}

#endif


bool SerialPort::has_con() const
{
	return this->connected;
}
