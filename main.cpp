/*!
 * \file main.cpp
 * \brief Main program for TelescopeControlSystem
 * 
 */

#include "telescopeui.h"
#include "backendwrapper.h"

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
	w.show();
	return a.exec();
}
