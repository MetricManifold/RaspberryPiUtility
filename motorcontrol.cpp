
#include "motorcontrol.h"


std::pair<double, double> MotorControl::read_pos()
{
	// prevent concurrent reads
	std::lock_guard lck(mm);

	char data[MSG_LENGTH];
	if (serial.has_con())
	{

#ifdef DEBUG
		bool r = get_test_serial().read(data, MSG_LENGTH);
#else
		bool r = serial.read(data, MSG_LENGTH);
#endif
		if (!r)
		{
			printf("Error reading from serial port\n");
			return BAD_READ;
		}
		
		auto[yaw, pitch] = ce::bytes_to_coords(data);
		return { yaw, pitch };
	}
	else
	{
		printf("Error connecting to serial port '%s', check port name\n", PORT_NAME);
		return BAD_READ;
	}

}


bool MotorControl::write_pos(double yaw, double pitch)
{
	// prevent concurrent writes
	std::lock_guard lck(mm);

	int isup;
	pstate.getval_gpio(isup);
	if (isup)
	{
		return false;
	}

	if (serial.has_con())
	{
		ppos.setval_gpio(1);

		// writing string to arduino
		char data[MSG_LENGTH];
		ce::coords_to_char(yaw, pitch, data);

#ifdef DEBUG
		bool r = get_test_serial().write(data, MSG_LENGTH);
#else
		bool r = serial.write(data, MSG_LENGTH);
#endif
		ppos.setval_gpio(0);
		return r;
	}
	else
	{
		printf("Error connecting to serial port '%s', check port name\n", PORT_NAME);
		return false;
	}
}


bool MotorControl::write_vel(double yaw, double pitch)
{
	// prevent concurent writes
	std::lock_guard lck(mm);

	int isup;
	pstate.getval_gpio(isup);
	if (isup)
	{
		return false;
	}

	if (serial.has_con())
	{
		pvel.setval_gpio(1);

		// writing string to arduino
		char data[MSG_LENGTH];
		ce::coords_to_char(yaw, pitch, data);

#ifdef DEBUG
		bool r = get_test_serial().write(data, MSG_LENGTH);
#else
		bool r = serial.write(data, MSG_LENGTH);
#endif
		pvel.setval_gpio(0);
		return r;
	}
	else
	{
		printf("Error connecting to serial port '%s', check port name\n", PORT_NAME);
		return false;
	}

	return true;
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

#ifdef DEBUG

	return true;

#else
	std::lock_guard lck(mm);

	int isup;
	pstate.getval_gpio(isup);
	return !isup;

#endif
}


