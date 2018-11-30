/*!
 * \file main.cpp
 * \brief Main program for TelescopeControlSystem
 * 
 */

#include "telescopeui.h"
#include "backendwrapper.h"
#include "planetrad.h"

#include <QtWidgets/QApplication>
#include <iostream>

/*!
 * \brief Main method
 * 
 * \param argc
 * \param argv
 * \return int program status
 */
int main(int argc, char *argv[])
{
	Backend b;

	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // for High DPI displays

	QApplication a(argc, argv);
	TelescopeUI w(&b);

	printf("initialized program\n");

	static Planet Mars{
		1.8496,
		49.668,
		336.322,
		1.523762,
		0.523998,
		0.093346,
		82.9625 };

	auto[ra, d] = get_planet_rad(Mars);
	

	w.show();
	return a.exec();
}
