// DHTTable.h

#ifndef _DHTTABLE_h
#define _DHTTABLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "JPEG_Macros.h"
#include <SD.h>

class DHTTable
{
 public:
	 unsigned char HuffCodesGenerated;
	 unsigned int  DHT_Length;
	 unsigned char DHT_Number; // 0-3, otherwise error
	 unsigned char DHT_Type; // 0-1, otherwise error, 0 = DC, 1 = AC table
	 unsigned char DHT_CodesCount[DHT_CODE_MAX_LENGTH]; // index 0 = Count of length 1, index 1 Count od length 2 .....
														// index 15 = lenght 16
	 unsigned char DHT_CodesOffset[DHT_CODE_MAX_LENGTH]; // offsets of start codes in RAM by length
	 void printDHT();

	 
};


#endif

