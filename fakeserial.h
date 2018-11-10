#pragma once

#include <random>
#include <cmath>

#include "serialport.h"
#include "coordencoder.h"

/*!
 *    \class FakeSerial
 *    \file fakeserial.h
 *    \brief the FakeSerial class imitates some output from the serial port to use for testing purposes
 *			it effectively replaces the serial driver
 *    \authors Steve Silber, Alex Yan
 *    \date 2018-11
 *
 */
struct FakeSerial
{
public:
	FakeSerial(FakeSerial const&) = delete;
	void operator=(FakeSerial const&) = delete;

	/*
	 * read the data from the arduino port
	 * @buffer The data to read from the serial port
	 * @buf_size The size of the data buffer in bytes
	 * @returns Integer representing the bytes that have been read in
	 */
	int read(char *buffer, unsigned int buf_size);

	/*
	 * write the data into the arduio port
	 * @buffer The data to write into the serial port
	 * @buf_size The size of the data buffer in bytes
	 * @returns Whether the write is successful (true) or not (false)
	 */
	bool write(char *buffer, unsigned int buf_size);


private:
	double yaw, pitch;
	FakeSerial() : yaw{ 0 }, pitch{ 0 } {}

	friend FakeSerial &get_test_serial();
};

static FakeSerial &get_test_serial()
{
	static FakeSerial instance;
	return instance;
}
