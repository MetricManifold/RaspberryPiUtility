
#include "controlapi.h"


void read()
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


