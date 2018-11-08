
#include "motorcontrol.h"


std::pair<double, double> MotorControl::read_pos()
{
	char data[MSG_LENGTH];
	if (serial.has_con())
	{
		// request and read data
		pread.setval_gpio(1);
		int 
			yaw = 0, 
			pitch = 0;

		int i = 0;
		serial.read(data, MSG_LENGTH);
		pread.setval_gpio(0);

		// parse the sent data
		for (char *c = data + MSG_LENGTH - 1; c >= data; --c, ++i)
		{
			// if we entered the yaw part
			if (c == data + MSG_YAW_POS - 1)
			{
				i = 0;
			}

			// if we are in the pitch part of the string
			if (c >= data + MSG_YAW_POS)
			{
				if (*c == '0')
				{
					pitch += 0b1 << i;
				}
			}
			// otherwise we are in the yaw part
			else
			{
				if (*c == '0')
				{
					yaw += 0b1 << i;
				}
			}
		}

		return { yaw, pitch };
		
	}
	else
	{
		printf("Error connecting to serial port '%s', check port name\n", PORT_NAME);
		return BAD_READ;
	}

}


bool MotorControl::write_pos(int yaw, int pitch)
{
	{
		std::lock_guard lck(mm);

		int isup;
		pstate.getval_gpio(isup);
		if (isup)
		{
			return false;
		}
	}
	if (serial.has_con())
	{
		ppos.setval_gpio(1);

		// writing string to arduino
		char data[MSG_LENGTH];


		// encode the data
		int i = 0;
		for (char *c = data + MSG_LENGTH - 1; c >= data; --c, ++i)
		{
			// if we entered the yaw part
			if (c == data + MSG_YAW_POS - 1)
			{
				i = 0;
			}

			// if we are in the pitch part of the string
			if (c >= data + MSG_YAW_POS)
			{
				if (pitch & 1 << i)
				{
					*c = '1';
				}
				else
				{
					*c = '0';
				}
			}
			// otherwise we are in the yaw part
			else
			{
				if (yaw & 1 << i)
				{
					*c = '1';
				}
				else
				{
					*c = '0';
				}
			}
		}
		printf("%s", data);

		sprintf(data,
			MSG_FORMAT,
			static_cast<int>(yaw),
			static_cast<int>(pitch));

		serial.write(data, MSG_LENGTH);

		ppos.setval_gpio(0);
		return true;
	}
	else
	{
		printf("Error connecting to serial port '%s', check port name\n", PORT_NAME);
		return false;
	}
}


bool MotorControl::write_vel(int yaw, int pitch)
{
	{
		std::lock_guard lck(mm);

		int isup;
		pstate.getval_gpio(isup);
		if (isup)
		{
			return false;
		}
	}
	if (serial.has_con())
	{
		pvel.setval_gpio(1);

		// writing string to arduino
		char data[MSG_LENGTH];


		// encode the data
		int i = 0;
		for (char *c = data + MSG_LENGTH - 1; c >= data; --c, ++i)
		{
			// if we entered the yaw part
			if (c == data + MSG_YAW_POS - 1)
			{
				i = 0;
			}

			// if we are in the pitch part of the string
			if (c >= data + MSG_YAW_POS)
			{
				if (pitch & 1 << i)
				{
					*c = '1';
				}
				else
				{
					*c = '0';
				}
			}
			// otherwise we are in the yaw part
			else
			{
				if (yaw & 1 << i)
				{
					*c = '1';
				}
				else
				{
					*c = '0';
				}
			}
		}
		printf("%s", data);

		sprintf(data,
			MSG_FORMAT,
			static_cast<int>(yaw),
			static_cast<int>(pitch));

		serial.write(data, MSG_LENGTH);

		pvel.setval_gpio(0);
		return true;
	}
	else
	{
		printf("Error connecting to serial port '%s', check port name\n", PORT_NAME);
		return false;
	}

}

void MotorControl::all_stop()
{
	pstop.setval_gpio(1);
	int isup = true;

	std::lock_guard lck(mm);
	while (isup)
	{
		pstate.getval_gpio(isup);
	}
}

bool MotorControl::is_free()
{
	std::lock_guard lck(mm);

	int isup;
	pstate.getval_gpio(isup);
	return isup;
}


