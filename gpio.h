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

/* GPIO Class
 * Purpose: Each object instantiated from this class will control a GPIO pin
 * The GPIO pin number must be passed to the overloaded class constructor
 */
class Pin
{
public:

	Pin();								// create a GPIO object and export
	Pin(int);							// export with the defined pin
	Pin(int, char *);					// give the direction of the pin too

	~Pin() { unexport_gpio(); }

	int export_gpio();					// exports GPIO
	int unexport_gpio();				// unexport GPIO
	int setdir_gpio(char * dir);		// Set GPIO Direction
	int setval_gpio(int val) const;		// Set GPIO Value (putput pins)
	int getval_gpio(int& val) const;	// Get GPIO Value (input/ output pins)
	int get_gpionum() const;			// return the GPIO number associated with the instance of an object

private:

	int write(char * to, char * val) const;
	int write(char * to, int val) const;

	// GPIO number associated with the instance of an object
	int const gpionum;
};

