// ValidateData.h

#ifndef _VALIDATEDATA_h
#define _VALIDATEDATA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "JPEG_Macros.h"

class ValidateDataClass
{
 protected:


 public:
	 static void addNumber(int *inputData, int number);
	 static void validateData(int *inputData, int minValue, int maxValue);
};

extern ValidateDataClass ValidateData;

#endif

