
#include "motorcontrol.h"


void MotorControl::read()
{
	char data[MAX_DATA_LENGTH];
	SerialPort arduino(PORT_NAME);

	if (arduino.isConnected())
	{
		printf("Connection Established\n");
	}
	else
	{
		printf("ERROR, check port name\n");
	}

	// read the data
	int r = arduino.read(data, MAX_DATA_LENGTH);
	puts(data);
}

void MotorControl::write()
{
	SerialPort arduino(PORT_NAME);

	if (arduino.isConnected())
	{
		printf("Connection Established\n");
	}
	else
	{
		printf("ERROR, check port name\n");
	}

	char data[10];
	//Writing string to arduino
	arduino.write(data, MAX_DATA_LENGTH);

}


