#include "raspberrypiutility.h"

//#include "controlin.h"

RaspberryPiUtility::RaspberryPiUtility(Backend * const b, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/*
	 * create our algorithm objects
	 */

	// Upon pushing 'set coordinates' button send data to control 
	connect(ui.btn_enter_coords, &QPushButton::clicked, this, [&]() { 

		double yaw = this->get_yaw_input();
		double pitch = this->get_pitch_input();
		
		// For testing purposes, data is being sent to the console
		printf("yaw = %lf, pitch = %lf\n", yaw, pitch);

		// Send data to Qt console
		this->append_console(std::stringstream() << "Setting Altitude=" << pitch << ", Azimuth=" << yaw);

		// Update display using data from control
		// As a placeholder, we are displaying the input values directly
		this->set_pitch_output(pitch);
		this->set_yaw_output(yaw);

	});

	

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

void RaspberryPiUtility::append_console(std::stringstream line) {
	ui.console->append(QString::fromStdString(line.str()));
}
