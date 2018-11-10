#pragma once

#include <utility>
#include <iostream>

#define STR(X) #X

#define MSG_YAW_POS 16
#define MSG_PITCH_POS 16
#define BIT_LENGTH (MSG_YAW_POS + MSG_PITCH_POS)
#define MSG_LENGTH (BIT_LENGTH >> 3)
#define MSG_FORMAT ("%" STR(MSG_YAW_POS) "s%" STR(MSG_PITCH_POS) "s")

#define NORMALIZATION_FACTOR 100.0

namespace ce
{
	void coords_to_char(double, double, char *);


	unsigned int coords_to_int(double, double);
	unsigned int char_to_int(char[MSG_LENGTH]);
	std::pair<double, double> bytes_to_coords(char[MSG_LENGTH]);
	std::pair<double, double> bytes_to_coords(unsigned int);


	void print_as_bits(unsigned int data, char *out);
	void print_as_bits(char *data, char *out);
}
