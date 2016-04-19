// Quantization.h

#ifndef _QUANTIZATION_h
#define _QUANTIZATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "JPEG_Macros.h"

class QuantizationClass
{
 protected:


 public:
	 static void quantization(int *inputData, int *outputData, unsigned char *quantizationTable);
	 static void deQuantization(int *inputData, float *outputData, unsigned char *quantizationTable);
	 static void deQuantization(int *inputData, int *outputData, unsigned char *quantizationTable);
};

extern QuantizationClass Quantization;

#endif

