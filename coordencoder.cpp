
#include "coordencoder.h"


void ce::coords_to_char(double yaw, double pitch, char data[MSG_LENGTH])
{
	uint64_t data_i = coords_to_int(yaw, pitch);

	char out[BIT_LENGTH + 1]{ 0 };
	print_as_bits(data_i, out);


	int i = 0;
	for (unsigned char *c = reinterpret_cast<unsigned char *>(&data_i); c < reinterpret_cast<unsigned char *>(&data_i) + MSG_LENGTH; ++c)
	{
		data[i++] = *c;
	}
}

uint64_t ce::coords_to_int(double yaw, double pitch)
{
	uint64_t data = static_cast<uint64_t>(pitch * NORMALIZATION_FACTOR)
		| (static_cast<uint64_t>(yaw * NORMALIZATION_FACTOR) << MSG_PITCH_POS);
	return data;
}

uint64_t ce::char_to_int(char data[MSG_LENGTH])
{
	uint64_t data_i = 0;

	int i = 0;
	for (unsigned char *c = reinterpret_cast<unsigned char *>(&data_i); c < reinterpret_cast<unsigned char *>(&data_i) + MSG_LENGTH; ++c)
	{
		*c = data[i++];
	}
	return data_i;
}


std::pair<double, double> ce::bytes_to_coords(char data[MSG_LENGTH])
{
	return bytes_to_coords(char_to_int(data));
}


std::pair<double, double> ce::bytes_to_coords(uint64_t data)
{
	double yaw, pitch;
	uint64_t
		yaw_i = ((1llu << MSG_YAW_POS) - 1llu) << MSG_PITCH_POS,
		pitch_i = (1llu << MSG_PITCH_POS) - 1llu;

	yaw = ((yaw_i & data) >> MSG_PITCH_POS) / NORMALIZATION_FACTOR;
	pitch = (pitch_i & data) / NORMALIZATION_FACTOR;

	return { yaw, pitch };
}

void ce::print_as_bits(uint64_t data, char *out)
{
	char bits[BIT_LENGTH + 1];
	for (char *c = bits; c < bits + BIT_LENGTH; ++c)
	{
		unsigned i = (BIT_LENGTH - 1) - (c - bits);
		if ((1llu << i) & data)
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

void ce::print_as_bits(char *data, char *out)
{
	print_as_bits(char_to_int(data), out);
}
