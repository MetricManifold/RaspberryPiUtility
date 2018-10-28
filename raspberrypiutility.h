#pragma once

#include <QtWidgets/QMainWindow>
#include <QSignalMapper>

#include "ui_raspberrypiutility.h"
#include "backendwrapper.h"

class RaspberryPiUtility : public QMainWindow
{
	Q_OBJECT

private:
	Ui::RaspberryPiUtilityClass ui;

public:
	RaspberryPiUtility(Backend * const, QWidget *parent = Q_NULLPTR);



	/*
	 * getter functions for returning certain UI elements
	 */
	double get_yaw_input() const;
	double get_pitch_input() const;





	/*
	 * the setting functions for required elements
	 */

	void set_yaw_output(double v);
	void set_pitch_output(double v);



};
