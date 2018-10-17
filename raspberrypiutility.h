#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_raspberrypiutility.h"

class RaspberryPiUtility : public QMainWindow
{
	Q_OBJECT

public:
	RaspberryPiUtility(QWidget *parent = Q_NULLPTR);

private:
	Ui::RaspberryPiUtilityClass ui;
};
