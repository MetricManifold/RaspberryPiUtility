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
#include "controlin.h"
#include "controlout.h"
#include "celestialin.h"
#include "celestialout.h"

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

	ControlIn::init(b);
	ControlOut::init(this);

	//CelestialIn::init(b);
	CelestialOut::init(this);

	
	// Upon selecting file->exit, terminate program
	connect(ui.actionExit, &QAction::triggered, this, [&]() {
		QApplication::quit();
	});

	/*
	 * Control functions
	 */

	// Upon pushing 'set coordinates' button send data to control 
	connect(ui.btn_enter_coords, &QPushButton::clicked, this, [&]() { 

		ControlIn(this).slot();

		double yaw = this->get_yaw_input();
		double pitch = this->get_pitch_input();
		
		// Send data to Qt console
        std::stringstream ss;
        ss << "Setting Alitude=" << pitch << ", Azimuth=" << yaw;
		this->append_console(ss.str());


		// Inform user that telescope is moving (simulating for now)
		this->append_console("Tracking...");

		// Update display using data from control
		// As a placeholder, we are displaying the input values directly
		// this->set_pitch_output(pitch);
		// this->set_yaw_output(yaw);

	});

	// Upon pushing 'Set' velocity button send velocity setting to control
	connect(ui.btn_set_vel, &QPushButton::clicked, this, [&]() {

		double pitch_vel = this->get_pitch_vel_input();
		double yaw_vel = this->get_yaw_vel_input();

		// Send data to Qt console
		std::stringstream ss; 
		ss << "Setting alitude velocity=" << pitch_vel << " azimuth velocity=" << yaw_vel;
		this->append_console(ss.str());

		// As placeholder, we're displaying input values directly
		this->set_pitch_vel_output(pitch_vel);
		this->set_yaw_vel_output(pitch_vel);
	});

	// Upon pushing 'stop' button, set velocity to zero, effectively stopping the telescope.
	connect(ui.btn_stop_vel, &QPushButton::clicked, this, [&]() {
		
		// Send data to Qt console
		this->append_console("Stopping Telescope! Tracking cancelled.");
	});

	

	/******************************
	Celestial Database functions
	*******************************/
	// Search for star
	connect(ui.btn_search_star, &QPushButton::clicked, this, [&]() {
		CelestialIn(this).slot();

	});

	// Search for planet
	connect(ui.btn_search_planet, &QPushButton::clicked, this, [&]() {

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
 * \brief Getter method for pitch velocity input from UI
 * 
 * \return double value for velocity
 */
double TelescopeUI::get_pitch_vel_input() const {
	return ui.pitch_vel_input->value();
}
/*!
 * \brief Getter method for yaw velocity input from UI
 *
 * \return double value for velocity
 */
double TelescopeUI::get_yaw_vel_input() const {
	return ui.yaw_vel_input->value();
}

/*!
	 * \brief Getter method for star name input from UI
	 *
	 * \return string with star name
	 */
std::string TelescopeUI::get_star_input() const {
	return ui.input_star->text().toStdString();
}

/*!
 * \brief Getter method for planet name input from UI
 *
 * \return string with planet name
 */
std::string TelescopeUI::get_planet_input() const {
	return ui.input_planet->text().toStdString();
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
 * \brief Setter method for displaying pitch velocity on UI 'LCD display'
 *
 * \param v represents double value for velocity
 */
void TelescopeUI::set_pitch_vel_output(double v) {
	ui.pitch_vel_dis->display(v);
}
/*!
 * \brief Setter method for displaying yaw velocity on UI 'LCD display'
 *
 * \param v represents double value for velocity
 */
void TelescopeUI::set_yaw_vel_output(double v) {
	ui.yaw_vel_dis->display(v);
}


/*!
* \brief Setter method for writing lines to internal UI console
*
* \param String that contains the line to be displayed on the console
*/
void TelescopeUI::append_console(std::string line) {
	ui.console->append(QString::fromStdString(line));
}

/*!
 * \brief Setter method for time display
 *
 * \param line contains time as string
 */
void TelescopeUI::set_time_dis(std::string line) {
	ui.time_dis->setText(QString::fromStdString(line));
}

/*!
 * \brief Setter method  for latitude display
 *
 * \param line contains latitude as string
 */
void TelescopeUI::set_lat_dis(std::string line) {
	ui.lat_dis->setText(QString::fromStdString(line));
}

/*!
 * \brief Setter method for longitude display
 *
 * \param line contains longitude as string
 */
void TelescopeUI::set_long_dis(std::string line) {
	ui.long_dis->setText(QString::fromStdString(line));
}

/*!
 * \brief Setter method for star/planet name display
 *
 * \param line contains star/name as string
 */
void TelescopeUI::set_name_dis(std::string line) {
	ui.name_dis->setText(QString::fromStdString(line));
}

/*!
 * \brief Setter method for right ascension display
 *
 * \param line contains right ascension as string
 */
void TelescopeUI::set_rasc_dis(std::string line) {
	ui.rasc_dis->setText(QString::fromStdString(line));
}

/*!
 * \brief Setter method for declination display
 *
 * \param line contains declination as string
 */
void TelescopeUI::set_dec_dis(std::string line) {
	ui.dec_dis->setText(QString::fromStdString(line));
}
