/*!
 * \class Planet
 * \file planet.h
 * \brief Part of Celestial database. Retrieves planet object from webpage.
 * \authors Steve Silber
 * \date 2018-11
 */


#pragma once

#define PLANET_WEBPAGE "https://en.wikipedia.org/wiki/"

#include <iostream>
#include <string>


#include "downloadpage.h"
#include "coordinates.h"
#include "Angle.h"

#define PLANET_HOST_NAME "www.wikipedia.com"
#define PLANET_URL "wiki/"
#define PLANET_ID "planet"
#define PLANET_FMT PLANET_ID " "
#define PLANET_I_FMT "</B> %dh%dm%lfs, %d&deg;%d'%lf\""
#define PLANET_O_FMT "</B> %dh%dm%lfs, %d&deg;%d'%lf\""
#define PLANET_P_FMT "</B> %dh%dm%lfs, %d&deg;%d'%lf\""

#define MINUTE 0
#define HOUR 12
#define DAY 1
#define MONTH 1
#define YEAR 2000

class Planet
{
	char *name;
	char *url;

	double
		i,		// inclination
		o,		// longitude of the ascending node
		p,		// longitude of the perihelion
		a,		// mean distance
		n,		// daily motion
		e,		// eccentricy
		L;		// mean longitude

public:
	Planet(double i, double o, double p, double a, double n, double e, double L) :
		i{ i },
		o{ o },
		p{ p },
		a{ a },
		n{ n },
		e{ e },
		L{ L } {}

	Planet(char *name) :
		name{ new char[strlen(name) + 1] },
		url{ new char[strlen(PLANET_URL) + strlen(name) + 1] }
	{
		strcpy(this->name, name);
		sprintf(url, "%s%s", PLANET_URL, name);

		for (char *iter = url + sizeof(PLANET_URL) / sizeof(char); *iter; ++iter)
		{
			if (*iter == ' ')
			{
				*iter = '+';
			}
		}

		char contents[HTTP_BUFFER_CONTENT];
		bool r = web::get_page(contents, PLANET_HOST_NAME, url);

		if (!r)
		{
			printf("could not access online database\n");
			exit(8);
		}

		char
			stri[] = "and Declination",
			stro[] = "ascending node",
			strp[] = "perihelion",
			stra[] = "mean distance",
			strn[] = "daily motion",
			stre[] = "eccentricity",
			strL[] = "mean longitude";

		using inf = std::pair<char *, double*>[];
		auto cmp = inf{ 
			{stri, &i},
			{stro, &o},
			{strp, &p},
			{stra, &a},
			{strn, &n},
			{stre, &e},
			{strL, &L},
		};

		//size_t sublen = sizeof(substr) / sizeof(char);
		char *delim = ":";
		char *line = strtok(contents, delim);
		do
		{
			size_t len = strlen(line);
			//if (strcmp(line + (len - sublen + 1), substr) == 0)
			{
				line = strtok(NULL, delim);
				int a, b, c, d;
				double e, f;

				//sscanf(line, HTTP_READ_FMT, &a, &b, &e, &c, &d, &f);
				//rasc = rightasc{ a, b, e };
				//dec = declination{ c, d, f };

				printf("loaded right ascension and declination for '%s'\n", name);
				break;
			}
		} while ((line = strtok(NULL, delim)) != NULL);
	}
	~Planet()
	{
		delete[] name;
		delete[] url;
	}
	friend std::pair<Angle, Angle> get_planet_rad(Planet &p);

private:
	void print_info(FILE *f)
	{

	}

};


