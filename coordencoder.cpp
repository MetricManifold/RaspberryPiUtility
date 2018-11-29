
#include "coordencoder.h"


void ce::coords_to_char(double yaw, double pitch, char * data)
{
	int data_i = coords_to_int(yaw, pitch);
	for (int i = 0; i < MSG_LENGTH; ++i)
	{
		data[i] = static_cast<char>(data_i >> (i * 8));
	}
}

unsigned int ce::coords_to_int(double yaw, double pitch)
{
	return 
		static_cast<int>(pitch * NORMALIZATION_FACTOR) 
		| (static_cast<int>(yaw * NORMALIZATION_FACTOR) << MSG_PITCH_POS);
}

unsigned int ce::char_to_int(char data[MSG_LENGTH])
{
	int data_i = 0;
	for (int i = 0; i < MSG_LENGTH; ++i)
	{
		data_i += (static_cast<int>(data[i]) << (8 * i));
	}
	return data_i;
}


std::pair<double, double> ce::bytes_to_coords(char data[MSG_LENGTH])
{
	return bytes_to_coords(char_to_int(data));
}


std::pair<double, double> ce::bytes_to_coords(unsigned int data)
{
	double yaw, pitch;
	unsigned int 
		yaw_i = ((1 << MSG_YAW_POS) - 1) << MSG_PITCH_POS, 
		pitch_i = (1 << MSG_PITCH_POS) - 1;

	yaw = ((yaw_i & data) >> MSG_PITCH_POS) / NORMALIZATION_FACTOR;
	pitch = (pitch_i & data) / NORMALIZATION_FACTOR;

	return { yaw, pitch };
}

void ce::print_as_bits(unsigned int data, char *out)
{
	char bits[BIT_LENGTH + 1];
	for (char *c = bits; c < bits + 16 + 16; ++c)
	{
		int i = (BIT_LENGTH - 1) - (c - bits);
		if ((1 << i) & data)
		{
			*c = '1';
		}
		else
		{
			*c = '0';
		}
	}
	bits[BIT_LENGTH] = '\0';
	std::copy(bits, bits + BIT_LENGTH + 1, out);
}

void ce::print_as_bits(char * data, char *out)
{
	print_as_bits(char_to_int(data), out);
}
