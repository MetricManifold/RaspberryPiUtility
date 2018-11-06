#pragma once


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serialport.h"

#define MAX_DATA_LENGTH 64
#define PORT_NAME "\\\\.\\COM20"

struct MotorControl
{
	void read();
	void write();
}