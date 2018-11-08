
#include "gpio.h"


Pin::Pin() : Pin(4) {}
Pin::Pin(int gpionum) : gpionum{ gpionum } { setval_gpio(gpionum); }
Pin::Pin(int gpionum, char * dir) : Pin(gpionum) { setdir_gpio(dir); }

int Pin::export_gpio()
{
	char export_str[] = GPIO_DIR "/export";
	return write(export_str, gpionum);
}

int Pin::unexport_gpio()
{
	char unexport_str[] = GPIO_DIR "/unexport";
	return write(unexport_str, gpionum);
}

int Pin::setdir_gpio(char * dir)
{
	char setdir_str_f[] = GPIO_DIR "/gpio%d/direction";
	char setdir_str[sizeof(setdir_str_f) / sizeof(char)];
	sprintf(setdir_str, setdir_str_f, gpionum);
	return write(setdir_str, dir);
}

int Pin::setval_gpio(int val) const
{
	char setval_str_f[] = GPIO_DIR "/gpio%d/value";
	char setval_str[sizeof(setval_str_f) / sizeof(char)];
	sprintf(setval_str, setval_str_f, gpionum);
	return write(setval_str, val);
}

int Pin::getval_gpio(int& val) const
{
	char getval_str_f[] = GPIO_DIR "/gpio%d/value";
	char getval_str[sizeof(getval_str_f) / sizeof(char)];
	sprintf(getval_str, getval_str_f, gpionum);

	FILE *getvalgpio;
	if ((getvalgpio = fopen(getval_str, "r")) == 0) 
	{
		printf("OPERATION FAILED: Unable to get GPIO %d\n", gpionum);
		return -1;
	}

	fscanf(getvalgpio, "%d", &val);
	fclose(getvalgpio); //close the value file
	return 0;
}

int Pin::get_gpionum() const
{

	return gpionum;

}

int Pin::write(char * to, int val) const
{
	// Open "export" file
	FILE *f;
	if ((f = fopen(to, "w")) == 0)
	{
		printf("Error writing GPIO: Unable to open '%s'\n", to);
		return -1;
	}

	// write to the file
	fprintf(f, "%d", val);
	fclose(f);
	return 0;
}


int Pin::write(char * to, char * val) const
{
	// Open "export" file
	FILE *f;
	if ((f = fopen(to, "w")) == 0) {
		printf("OPERATION FAILED: Unable to export GPIO %d\n", gpionum);
		return -1;
	}

	// write to the file
	fprintf(f, "%s", val);
	fclose(f);
	return 0;
}


