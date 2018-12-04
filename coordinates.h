/*!
 * \class rightasc, declination 
 * \file coordinates.h
 * \brief Structures for equatorial coordinates
 * \authors Steve Silber
 * \date 2018-11
 */

#pragma once

#define RIGHT_ASC_FMT "%dh%dm%lfs"
#define DECLINATION_FMT "%d*%d'%lf"

typedef struct
{
	int h;
	int m;
	double s;
} rightasc;

typedef struct
{
	int d;
	int m;
	double s;
} declination;

