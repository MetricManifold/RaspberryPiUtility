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
	int am;
	double as;
} declination;

