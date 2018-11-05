#include "raspberrypiutility.h"

#include "controlin.h"

RaspberryPiUtility::RaspberryPiUtility(Backend * const b, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/*
	 * create our algorithm objects
	 */
	connect(ui.btn_control, &QPushButton::clicked, this, [&]() { ControlIn(b, this).slot(); });

}


double RaspberryPiUtility::get_yaw_input() const
{
	return ui.yaw_input->value();
}

double RaspberryPiUtility::get_pitch_input() const
{
	return ui.pitch_input->value();
}

void RaspberryPiUtility::set_yaw_output(double v)
{
	ui.yaw_dis->display(v);
}

void RaspberryPiUtility::set_pitch_output(double v)
{
	ui.pitch_dis->display(v);
}
