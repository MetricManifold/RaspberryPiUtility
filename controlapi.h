#pragma once


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serialport.h"

#define MAX_DATA_LENGTH 64
#define PORT_NAME "\\\\.\\COM20"

namespace capi
{
	void read();
	void write();
}