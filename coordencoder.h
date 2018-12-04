/*!
 * \class ce  
 * \file coordencoder.h
 * \brief Methods for converting coordinates into integers and bytes. 
 * \authors Steve Silber
 * \date 2018-11
 */



#pragma once

#include <utility>
#include <iostream>

#define STR(X) #X

#define MSG_YAW_POS 32
#define MSG_PITCH_POS 32
#define BIT_LENGTH (MSG_YAW_POS + MSG_PITCH_POS)
#define MSG_LENGTH (BIT_LENGTH >> 3)
#define MSG_FORMAT ("%" STR(MSG_YAW_POS) "s%" STR(MSG_PITCH_POS) "s")
#define CHAR_BITS (sizeof(char) * 8)

#define NORMALIZATION_FACTOR 100.0

namespace ce
{
	void coords_to_char(double, double, char[MSG_LENGTH]);

	uint64_t coords_to_int(double, double);
	uint64_t char_to_int(char[MSG_LENGTH]);
	std::pair<double, double> bytes_to_coords(char[MSG_LENGTH]);
	std::pair<double, double> bytes_to_coords(uint64_t);

	void print_as_bits(uint64_t data, char *out);
	void print_as_bits(char *data, char *out);
}
