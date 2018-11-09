/*!
 *	\class RaspberryPiUtility
 *	\file raspberrypiutility.cpp
 *	\brief RaspberryPiUtility class provides communication between the UI and internal modules (MotorControl and Algorithmic modules)
 *	\details Implements RaspberryPiUtility header
 *	\authors Steve Silber, Conor Dunne
 *	\date 2018-11
 *
 */

#include "telescopeui.h"

/*!
 * \brief Implementation of main constructor for RaspberryPiUtility. Creates an instance of the Qt UI template, forming the UI for TelescopeControl. 
 *
 * \param b pointer of type Backend
 * \param parent pointer of type QWidget
 */
TelescopeUI::TelescopeUI(Backend * const b, QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this); ///< Creates UI elements

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
        std::stringstream ss;
        ss << "Setting Alitude=" << pitch << ", Azimuth=" << yaw;
		this->append_console(ss.str());


		// Inform user that telescope is moving (simulating for now)
		this->append_console("Tracking...");

		// Update display using data from control
		// As a placeholder, we are displaying the input values directly
		this->set_pitch_output(pitch);
		this->set_yaw_output(yaw);

	});

	

}

/*!
* \brief Getter method for yaw input from UI
* \return double value for yaw
*/
double TelescopeUI::get_yaw_input() const
{
	return ui.yaw_input->value();
}

/*!
 * \brief Getter method for pitch input from UI
 * \return double value for pitch
 */
double TelescopeUI::get_pitch_input() const
{
	return ui.pitch_input->value();
}

/*!
* \brief Setter method for displaying yaw on UI 'LCD display'
*
* \param v represents double value for yaw
*/
void TelescopeUI::set_yaw_output(double v)
{
	ui.yaw_dis->display(v);
}

/*!
* \brief Setter method for displaying pitch on UI 'LCD display'
*
* \param v represents double value for pitch
*/
void TelescopeUI::set_pitch_output(double v)
{
	ui.pitch_dis->display(v);
}

/*!
* \brief Setter method for writing lines to internal UI console
*
* \param String that contains the line to be displayed on the console
*/
void TelescopeUI::append_console(std::string line) {
	ui.console->append(QString::fromStdString(line));
}