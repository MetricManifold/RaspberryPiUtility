#include "planet.h"



Planet::Planet(double i, double o, double p, double a, double n, double e, double L) :
	i{ i * (atan(1) * 4) / 180.0 },
	o{ o * (atan(1) * 4) / 180.0 },
	p{ p * (atan(1) * 4) / 180.0 },
	n{ n * (atan(1) * 4) / 180.0 },
	L{ L * (atan(1) * 4) / 180.0 },
	e{ e },
	a{ a },
	state{ true },
	epoch{ WIKI_MINUTE, WIKI_HOUR, WIKI_DAY, WIKI_MONTH, WIKI_YEAR } {}

Planet::Planet(char *name) :
	i{ -1 },
	o{ -1 },
	p{ -1 },
	n{ -1 },
	L{ -1 },
	e{ -1 },
	a{ -1 },
	name{ new char[strlen(name) + 1] },
	url{ new char[strlen(PLANET_URL) + strlen(name) + 1] }
{
	strcpy(this->name, name);

	// make sure the first letter after every space is uppercase

	*this->name = toupper(*this->name);
	for (char *iter = this->name; *iter; ++iter)
	{
		if (*iter == ' ')
		{
			*(iter + 1) = toupper(*(iter + 1));
		}
	}

	sprintf(url, "%s%s", PLANET_URL, this->name);

	for (char *iter = url + sizeof(PLANET_URL) / sizeof(char); *iter; ++iter)
	{
		if (*iter == ' ')
		{
			*iter = '_';
		}
	}

	char *contents = new char[HTTP_BUFFER_CONTENT];

	char *full_url = new char[strlen(PLANET_HOST_NAME) + strlen(url) + 2];
	strcpy(full_url, PLANET_HOST_NAME);
	strcat(full_url, "/");
	strcat(full_url, url);

	bool r = web::get_page_qt(contents, full_url);
	delete[] full_url;

	if (!r)
	{
		printf("Could not access wikipedia\n");
		exit(8);
	}

	/*
	 * clean up the webpage first and narrow down the information for
	 * easier parsing
	 */

	char buffer[HTTP_BUFFER_MEDIUM];
	char *iter = contents;
	size_t pos = 0;

	auto to_buffer = [&](char c)
	{
		if (c == '\u2019')
		{
			c = '-';
		}

		if (
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			c == ':' ||
			c == '.' ||
			c == ' ' ||
			c == '-')
		{
			buffer[pos++] = c;
		}
	};

	// track to start of the wikipedia info list
	while (++iter, !(
		*iter == 't' &&
		*(iter + 1) == 'b' &&
		*(iter + 2) == 'o' &&
		*(iter + 3) == 'd' &&
		*(iter + 4) == 'y'));

	// while inside the table
	while (++iter, !(
		*iter == '/' &&
		*(iter + 1) == 't' &&
		*(iter + 2) == 'b' &&
		*(iter + 3) == 'o' &&
		*(iter + 4) == 'd' &&
		*(iter + 5) == 'y'))
	{
		if (*iter == '<' && *(iter + 1) == 'a')
		{
			char key[] = "title=";
			constexpr size_t keylen = sizeof(key) / sizeof(char);

			// track to the title of the link
			while (++iter, *iter != '>')
			{
				char chk[keylen];
				std::copy(iter - keylen + 1, iter, chk);

				if (strcmp(chk, key) == 0)
				{
					break;
				}
			}

			if (*iter == '>')
			{
				continue;
			}
			else
			{
				// copy the link into buffer
				while (*iter++, *iter != '"')
				{
					to_buffer(*iter);
				}
				buffer[pos++] = '\n';
			}
		}
		else if (*(iter - 2) == '<' && *(iter - 1) == 't' && *iter == 'd')
		{
			using inf = std::tuple<char *, char *>;

			/*
			 * a list of keys that will be replaced as the buffer is being filled
			 */
			static inf replace[] = {
				{ "million", "E6 " },
				{ "billion", "E9 " },
				{ "years", "yr" } };

			static char *ignore[] = {
				{ "class=\"sortkey\"" },
				{ "href=\"#cite" } };


			// track to the end of the row
			while (++iter, *iter != '>');

			// boolean tracks whether some content should be skipped when being
			// placed in the buffer
			bool do_copy = true;

			while (*iter++, !(
				*(iter) == '<' &&
				*(iter + 1) == '/' &&
				*(iter + 2) == 't' &&
				*(iter + 3) == 'd'))
			{
				// if the iterator is on the start of an element
				if (*iter == '<')
				{
					do_copy = true;

					// while the element is being parsed, check for certain keys
					while (++iter, *iter != '>')
					{
						/*
						 * spans with this class are special structures in wikipedia
						 * with garbage information that can always be ignored
						 */

						for (auto const& ignore_str : ignore)
						{
							size_t ignore_len = strlen(ignore_str);
							if (*iter == *ignore_str)
							{
								char chk[32];
								std::copy(iter, iter + ignore_len, chk);
								chk[ignore_len] = '\0';

								if (strcmp(chk, ignore_str) == 0)
								{
									do_copy = false;
								}
							}
						}

					}
				}
				else if (do_copy)
				{
					// skip the encoded characters of the form &#000;
					if (*iter == '&' && *(iter + 1) == '#')
					{
						while (++iter, *iter != ';');
						++iter;
					}

					bool replaced = false;
					for (auto const& s : replace)
					{
						auto[from, to] = s;
						size_t from_len = strlen(from);
						size_t to_len = strlen(to);

						// if the first letter matches, proceed to check whole string
						if (*iter == *from)
						{
							// copy to a buffer and check
							char chk[32];
							std::copy(iter, iter + from_len, chk);
							chk[from_len] = '\0';

							if (strcmp(chk, from) == 0)
							{
								strcat(buffer, to);
								pos += to_len;
								iter += from_len - 1;
								replaced = true;
							}
						}
					}

					// if no replacement was made, copy to the buffer as usual
					if (!replaced)
					{
						to_buffer(*iter);
					}

				}
			}
			buffer[pos++] = '\n';
		}
	}
	buffer[pos] = '\0';
	delete[] contents;

	char
		strM[] = "Mean anomaly",
		stri[] = "Orbital inclination",
		stro[] = "Longitude of the ascending node",
		strp[] = "Argument of periapsis",
		stra[] = "Semi-major and semi-minor axes",
		strn[] = "Orbital period",
		stre[] = "Orbital eccentricity",
		strL[] = "mean longitude";


	char
		fmtM[] = "%lf%*[^\n]",
		fmti[] = "%lf%*[^\n]",
		fmto[] = "%lf%*[^\n]",
		fmtp[] = "%lf%*[^\n]",
		fmta[] = "%lf%*[^\n]",
		fmtn[] = "%*[^y]yr%lf%*[^\n]",
		fmte[] = "%lf%*[^\n]",
		fmtL[] = "%s";

	using inf = std::tuple<char *, char *, double *, size_t>;
	inf cmp[] = {
		inf{strM, fmtM, &M, strlen(strM)},
		inf{stri, fmti, &i, strlen(stri)},
		inf{stro, fmto, &o, strlen(stro)},
		inf{strp, fmtp, &p, strlen(strp)},
		inf{stra, fmta, &a, strlen(stra)},
		inf{strn, fmtn, &n, strlen(strn)},
		inf{stre, fmte, &e, strlen(stre)},
		inf{strL, fmtL, &L, strlen(strL)},
	};

	char *delim = "\n";
	char *line = strtok(buffer, delim);
	do
	{
		size_t len = strlen(line);
		for (auto const& s : cmp)
		{
			auto[substr, fmt, val, sublen] = s;
			if (strcmp(line, substr) == 0)
			{
				line = strtok(NULL, delim);

				double t;
				int a = sscanf(line, fmt, &t);

				if (a > 0)
				{
					*val = t;
				}

				break;
			}
		}
	} while ((line = strtok(NULL, delim)) != NULL);


	// check that all parameters were filled
	if (
		i == -1 ||
		o == -1 ||
		p == -1 ||
		n == -1 ||
		L == -1 ||
		e == -1 ||
		a == -1)
	{
		printf("At least one of the parameters for planet '%s' was \
				not found on wikipedia\n", name);
		state = false;
	}
	else
	{
		state = true;
	}

	/*
	 * normalize the parameters we got from wikipedia
	 */

	 // convert all these to radians
	i *= (atan(1) * 4) / 180.0;
	o *= (atan(1) * 4) / 180.0;
	p *= (atan(1) * 4) / 180.0;
	M *= (atan(1) * 4) / 180.0;

	// daily movement is read in as number of days it takes to orbit the sun, so
	// find percentage of orbit covered in a day (1 / n), convert to radians
	n = ((1 / n) * 2 * (atan(1) * 4));

	// convert from kilometers to astronomical units
	a *= 6.68459E-9;

	/*
	 * Because of derivation for right ascension and declination using
	 * orbital parameters, the mean longitude is used. From the wikipedia
	 * source, it cannot be used, so derive it from information we do have
	 */
	L = M + p;

	// set the proper epoch
	epoch = { WIKI_MINUTE, WIKI_HOUR, WIKI_DAY, WIKI_MONTH, WIKI_YEAR };
}

Planet::~Planet()
{
	delete[] name;
	delete[] url;
}


/*
 * define earth as the reference point
 */
static Planet Earth{
	0.0,
	0.0,
	103.147,
	1.0000,
	0.985611,
	0.016679,
	324.5489
};

std::pair<Angle, Angle> Planet::get_equatorial_angle()
{
	auto juliandate = [](
		unsigned int year,
		unsigned int month,
		unsigned int day,
		unsigned int hours,
		unsigned int minutes) -> double
	{
		int
			yearp, monthp,
			A, B, C, D;
		if (month == 1 || month == 2)
		{
			yearp = year - 1;
			monthp = month + 12;
		}
		else
		{
			yearp = year;
			monthp = month;
		}


		A = yearp / 100.0;
		B = 2 - A + A / 4.0;

		if (yearp < 0)
		{
			C = trunc((365.25 * yearp) - 0.75);
		}
		else
		{
			C = 365.25 * yearp;
		}
		D = 30.6001 * (monthp + 1);
		double jd = B + C + D + day + 1720994.5 + (hours + minutes / 60.0) / 24.0;
		return jd;
	};


	// get the local time
	time_t tt;
	struct tm *ti;

	// store the local time
	time(&tt);
	ti = localtime(&tt);

	double d =
		juliandate(ti->tm_year + 1900, ti->tm_mon, ti->tm_mday, ti->tm_hour, ti->tm_min)
		- juliandate(epoch.year, epoch.month, epoch.day, epoch.hour, epoch.minute);

	auto rect_coords = [&d](Planet &pl) -> std::tuple<double, double, double>
	{


		/*
		 * Mean anomaly:
		 * n is daily motion
		 * d is the number of days since the date of the elements
		 * L is the mean longitude
		 * p is the longitude of perihelion
		 * M should be in range 0 to 360 degrees, add or subtract
		 * multiples of 360 to bring M into this range.
		 */
		double M = pl.n * d + pl.L - pl.p;

		/*
		 * True anomoly
		 * v is true anomaly
		 * M is mean anomaly
		 * e is eccentricity
		 * using the expanded Taylor series
		 */
		double v = M + (2 * pl.e - 0.25 *pow(pl.e, 3) + 5 / 96 * pow(pl.e, 5)) * sin(M) +
			(1.25 * pow(pl.e, 2) - 11 / 24 * pow(pl.e, 4)) * sin(2 * M) +
			(13 / 12 * pow(pl.e, 3) - 43 / 64 * pow(pl.e, 5)) * sin(3 * M) +
			103 / 96 * pow(pl.e, 4) * sin(4 * M) + 1097 / 960 * pow(pl.e, 5) * sin(5 * M);

		/*
		 * radius vector of the planet
		 */
		double r = pl.a * (1 - pl.e * pl.e) / (1 + pl.e * cos(v));

		/*
		 * Heliocentric coordinates
		 * r is radius vector
		 * v is true anomaly
		 * o is longitude of ascending node
		 * p is longitude of perihelion
		 * i is inclination of plane of orbit
		 * the quantity v + p - o is the angle of the planet measured
		 * in the plane of the orbit from the ascending node
		 */
		double X = r * (cos(pl.o) * cos(v + pl.p - pl.o) - sin(pl.o) * sin(v + pl.p - pl.o) * cos(pl.i));
		double Y = r * (sin(pl.o) * cos(v + pl.p - pl.o) + cos(pl.o) * sin(v + pl.p - pl.o) * cos(pl.i));
		double Z = r * (sin(v + pl.p - pl.o) * sin(pl.i));

		return { X, Y, Z };
	};


	/*
	 * Heliocentric coordinates for Mars
	 * r is radius vector
	 * v is true anomaly
	 * o is longitude of ascending node
	 * p is longitude of perihelion
	 * i is inclination of plane of orbit
	 * the quantity v + p - o is the angle of the planet measured
	 * in the plane of the orbit from the ascending node
	 */
	auto[X, Y, Z] = rect_coords(*this);

	/*
	 * Heliocentric coordinates for Earth
	 * r is radius vector of Earth
	 * v is true anomaly for Earth
	 * p is longitude of perihelion for Earth
	 */
	auto[Xe, Ye, Ze] = rect_coords(Earth);

	/*
	 * normalized coordinates, namely the
	 * geocentric ecliptic coodinates
	 */
	double Xp = X - Xe;
	double Yp = Y - Ye;
	double Zp = Z - Ze;

	/*
	 * convert to geocentric equatorial
	 */
	double ec = 23.439292 * atan(1) * 4 / 180.0; // obliquity of the elipctic
	double Xq = Xp;
	double Yq = Yp * cos(ec) - Zp * sin(ec);
	double Zq = Yp * sin(ec) + Zp * cos(ec);

	/*
	 * right ascension in radians
	 */
	double alpha = atan2(Yq, Xq);
	alpha = alpha * 180.0 / (atan(1) * 4) / 15;
	alpha = (alpha < 0) ? alpha + 24 : alpha;

	/*
	 * declination in radians
	 */
	double delta = atan2(Zq, sqrt(Xq * Xq + Yq * Yq));
	delta = delta * 180.0 / (atan(1) * 4);

	return { alpha, delta };
}

