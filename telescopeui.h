/*!
 *	\class RaspberryPiUtility
 *	\file raspberrypiutility.h
 *	\brief RaspberryPiUtility class header provides communication between the UI and internal modules (MotorControl and Algorithmic modules)
 *	\details Derived from QMainWindow base class
 *	\authors Steve Silber, Conor Dunne
 *	\date 2018-11
 * 
 */

#pragma once

#include <QtWidgets/QMainWindow>
#include <QSignalMapper>

#include <string>
#include <iostream>
#include <sstream>

#include "ui_raspberrypiutility.h" ///< Qt template UI generated using Qt Creator
#include "backendwrapper.h"

class TelescopeUI: public QMainWindow
{
	Q_OBJECT
private:
	Ui::RaspberryPiUtilityClass ui; ///< References Qt UI elements from the template

public:
	/*!
	 * \brief Main constructor for RaspberryPiUtility class
	 * 
	 * \param Constant backend wrapper as pointer
	 * \param parent pointer of type QWidget
	 */
	TelescopeUI(Backend * const, QWidget *parent = Q_NULLPTR);



	/*!
	 * \brief Getter method for yaw input from UI
	 * \return double value for yaw
	 */
	double get_yaw_input() const;
	/*!
	 * \brief Getter method for pitch input from UI
	 * 
	 * \return double value for pitch
	 */
	double get_pitch_input() const;
	/*!
	 * \brief Getter method for pitch velocity input from UI
	 * 
	 * \return double value for velocity
	 */
	double get_pitch_vel_input() const;
	/*!
	 * \brief Getter method for yaw velocity input from UI
	 *
	 * \return double value for velocity
	 */
	double get_yaw_vel_input() const;

	/*!
	 * \brief Getter method for star name input from UI
	 * 
	 * \return string with star name
	 */
	std::string get_star_input() const;

	/*!
	 * \brief Getter method for planet name input from UI
	 *
	 * \return string with planet name
	 */
	std::string get_planet_input() const;





	/*!
	 * \brief Setter method for displaying yaw on UI 'LCD display'
	 * 
	 * \param v represents double value for yaw
	 */
	void set_yaw_output(double v);

	/*!
	 * \brief Setter method for displaying pitch on UI 'LCD display'
	 * 
	 * \param v represents double value for pitch
	 */
	void set_pitch_output(double v);

	/*!
	 * \brief Setter method for displaying pitch velocity on UI 'LCD display'
	 * 
	 * \param v represents double value for velocity
	 */
	void set_pitch_vel_output(double v);

	/*!
	 * \brief Setter method for displaying yaw velocity on UI 'LCD display'
	 *
	 * \param v represents double value for velocity
	 */
	void set_yaw_vel_output(double v);

	/*!
	 * \brief Setter method for writing lines to internal UI console
	 * 
	 * \param String that contains the line to be displayed on the console
	 */
	void append_console(std::string line); 

	/*!
	 * \brief Setter method for time display
	 * 
	 * \param line contains time as string
	 */
	void set_time_dis(std::string line);

	/*!
	 * \brief Setter method  for latitude display
	 *
	 * \param line contains latitude as string
	 */
	void set_lat_dis(std::string line);

	/*!
	 * \brief Setter method for longitude display
	 *
	 * \param line contains longitude as string
	 */
	void set_long_dis(std::string line);

	/*!
	 * \brief Setter method for star/planet name display
	 *
	 * \param line contains star/name as string
	 */
	void set_name_dis(std::string line);

	/*!
	 * \brief Setter method for right ascension display
	 *
	 * \param line contains right ascension as string
	 */
	void set_rasc_dis(std::string line);

	/*!
	 * \brief Setter method for declination display
	 *
	 * \param line contains declination as string
	 */
	void set_dec_dis(std::string line);

};

