#include "raspberrypiutility.h"

RaspberryPiUtility::RaspberryPiUtility(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void RaspberryPiUtility::update(ControlOut out)
{
	ui.pitch_dis->display(out.pitch_value);
	ui.yaw_dis->display(out.yaw_value);
}


QDoubleSpinBox const *RaspberryPiUtility::get_yaw_input()
{
	return ui.yaw_input;
}

QDoubleSpinBox const *RaspberryPiUtility::get_pitch_input()
{
	return ui.pitch_input;
}

