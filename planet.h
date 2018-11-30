/*!
 * \class Planet
 * \file planet.h
 * \brief Part of Celestial database. Retrieves planet object from webpage.
 * \authors Steve Silber
 * \date 2018-11
 */


#pragma once

#define PLANET_WEBPAGE "https://en.wikipedia.org/wiki/"


#include "downloadpage.h"
#include "coordinates.h"

#include <iostream>
#include <string>

#define STAR_HOST_NAME "www.wikipedia.com"
#define STAR_URL "wiki/"
#define STAR_ID "planet"
#define STAR_FMT "%s %dh %dm %lfs,  %f"
#define HTTP_READ_FMT "</B> %dh%dm%lfs, %d&deg;%d'%lf\""

class Star
{
	char *name;
	char *url;

	rightasc rasc;		// right ascension
	declination dec;	// declination

public:
	Star(char *name) :
		name{ new char[strlen(name) + 1] },
		url{ new char[strlen(STAR_URL) + strlen(name) + 1] }
	{
		strcpy(this->name, name);
		sprintf(url, "%s%s", STAR_URL, name);

		for (char *iter = url + sizeof(STAR_URL) / sizeof(char); *iter; ++iter)
		{
			if (*iter == ' ')
			{
				*iter = '+';
			}
		}

		char contents[HTTP_BUFFER_CONTENT];
		bool r = web::get_page(contents, STAR_HOST_NAME, url);

		if (!r)
		{
			printf("could not access online database\n");
			exit(8);
		}

		char substr[] = "and Declination";
		size_t sublen = sizeof(substr) / sizeof(char);

		char *delim = ":";
		char *line = strtok(contents, delim);
		do
		{
			size_t len = strlen(line);
			if (strcmp(line + (len - sublen + 1), substr) == 0)
			{
				line = strtok(NULL, delim);
				int a, b, c, d;
				double e, f;

				sscanf(line, HTTP_READ_FMT, &a, &b, &e, &c, &d, &f);
				rasc = rightasc{ a, b, e };
				dec = declination{ c, d, f };

				printf("loaded right ascension and declination for '%s'\n", name);
				break;
			}
		} while ((line = strtok(NULL, delim)) != NULL);
	}
	~Star()
	{
		delete[] name;
		delete[] url;
	}

private:
	void print_info(FILE *f)
	{

	}

};


