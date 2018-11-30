#include "star.h"


Star::Star(char *name) :
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

Star::~Star()
{
	delete[] name;
	delete[] url;
}


void Star::print_info(FILE *f)
{
	fprintf(f, STAR_FMT, rasc.h, rasc.m, rasc.s, dec.d, dec.am, dec.as);
}
