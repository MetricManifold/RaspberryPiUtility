

#include "raspberrypiutility.h"

#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RaspberryPiUtility w;

	printf("printing ouptut");
	w.show();
	return a.exec();
}
