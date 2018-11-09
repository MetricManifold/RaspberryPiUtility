#pragma once

#include <string>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#ifdef _WIN64
#define GPIO_DIR "gpio"
#else
#define GPIO_DIR "/sys/class/gpio"
#endif

#define PIN_READ 4
#define PIN_POS 17
#define PIN_VEL 21
#define PIN_STATE 23
#define PIN_STOP 25

/*!
 *    \class Pin
 *    \file gpio.h
 *    \brief Each object instantiated from this class will control a GPIO pin
 *    \authors Steve Silber, Alex Yan
 *    \date 2018-11
 */
class Pin
{
public:

	/*
	 * constructor, create a GPIO object and export
	 */
	Pin();

	/*
	 * constructor, export with the defined pin
	 * @param gpionum The pin number for this pin
	 */
	Pin(int);

	/*
	 * constructor, give the direction of the pin too
	 * @param gpionum The pin number for this pin
	 * @param dir The direction for this pin
	 */
	Pin(int, char *);

	/*
	 * destructor, exports the pin
	 */
	~Pin() { unexport_gpio(); }

	/*
	 * exports GPIO
	 * @returns Whether the export succeeded (1) or failed (0)
	 */
	int export_gpio();

	/*
	 * exports GPIO
	 * @returns Whether the export succeeded (1) or failed (0)
	 */
	int unexport_gpio();

	/*
	 * sets the direction of GPIO pin, should only be called once
	 * @returns Whether the direction setting succeeded (1) or failed (0)
	 */
	int setdir_gpio(char * dir);

	/*
	 * sets a new value for GPIO pin
	 * @param val The value to set the GPIO to
	 * @returns Whether the export succeeded (1) or failed (0)
	 */
	int setval_gpio(int val) const;

	/*
	 * gets GPIO value
	 * @value The integer to print the output to
	 * @returns Whether the get succeeded (1) or failed (0)
	 */
	int getval_gpio(int& val) const;

	/*
	 * gets GPIO pin number
	 * @returns The pin number
	 */
	int get_gpionum() const;

private:

	/*
	 * writes the asked value to the asked directory
	 * @param to The directory and file to write to
	 * @param val The given value to write into the file
	 * @returns Whether the write was successful (1) or not (0)
	 */
	int write(char * to, char * val) const;

	/*
	 * writes the asked value to the asked directory
	 * @param to The directory and file to write to
	 * @param val The given value to write into the file
	 * @returns Whether the write was successful (1) or not (0)
	 */
	int write(char * to, int val) const;

	// GPIO number associated with the instance of an object
	int const gpionum;
};

