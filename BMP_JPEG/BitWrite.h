// BitWrite.h

#ifndef _BITWRITE_h
#define _BITWRITE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SD.h>

class BitWrite
{
private:
	File outputFile;
	unsigned char writeByte;
	signed char bitsWriteIndex;

public:
	BitWrite(void);
	BitWrite(File file); // constructor
	unsigned char writeValue(unsigned int value, unsigned char length); // write bits from value
	unsigned char writeLast(); // flush byte to file
};

#endif

