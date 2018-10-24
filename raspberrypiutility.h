#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_raspberrypiutility.h"

#include "control_out.h"

class RaspberryPiUtility : public QMainWindow
{
	Q_OBJECT

private:
	Ui::RaspberryPiUtilityClass ui;

public:
	RaspberryPiUtility(QWidget *parent = Q_NULLPTR);


	/*
	 * the update functions, overloaded by output state
	 */
	void update(ControlOut out);








	/*
	 * getter functions for returning certain UI elements
	 */
	QDoubleSpinBox const *get_yaw_input();
	QDoubleSpinBox const *get_pitch_input();



};
