// Color.h

#ifndef _COLOR_h
#define _COLOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

struct RGB
{
	unsigned char r;
	unsigned char g; 
	unsigned char b;

};

struct YCbCr
{
	unsigned char y;
	unsigned char cb;
	unsigned char cr;

};

#endif

