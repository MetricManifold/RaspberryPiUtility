/*!
 * \class Star
 * \file star.h
 * \brief Part of Celestial Database. Retrives star object from webpage. 
 * \authors Steve Silber
 * \date 2018-11
 */

#pragma once

#include "downloadpage.h"
#include "coordinates.h"
#include "Angle.h"

#include <iostream>
#include <string>

#define STAR_HOST_NAME "www.stellar-database.com"
#define STAR_URL "Scripts/search_star.exe?Name="
#define STAR_ID "star"
#define STAR_FMT STAR_ID " " RIGHT_ASC_FMT " " DECLINATION_FMT
#define HTTP_READ_FMT "</B> %dh%dm%lfs, %d&deg;%d'%lf\""

class Star
{
	char *name;
	char *url;

	rightasc rasc;		// right ascension
	declination dec;	// declination

public:
	/**
	 * Construts a new star object by parsing the webpage
	 * @param name The name of the star
	 */
	Star(char *name);
	~Star();

	Angle get_rightasc()
	{
		return Angle(rasc.h);
	}

	Angle get_declination()
	{
		return Angle(dec.d);
	}

private:

	/*
	 * given a file, the function will print out a line of information associated with
	 * this star to the file, which just includes a formated right ascension and
	 * declination
	 * @param f File into which to print
	 */
	void print_info(FILE *f);

};

