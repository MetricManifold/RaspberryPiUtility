

#include "raspberrypiutility.h"
#include "backendwrapper.h"

#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
	Backend b;

	QApplication a(argc, argv);
	RaspberryPiUtility w(&b);

	printf("printing ouptut");
	w.show();
	return a.exec();
}
