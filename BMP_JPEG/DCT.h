// DCT.h

#ifndef _DCT_h
#define _DCT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "JPEG_Macros.h"
#include "ValidateData.h"

#define SQRT_05 0.7071
#define PI_8 0.3927

class DCTClass
{
private:
	static void DCT_Lines(int *inputData, float *outputData);
	static void DCT_Rows(float *inputData, int *outputData);

	static void IDCT_Lines(float *inputData, float *outputData);
	static void IDCT_Rows(float *inputData, int *outputData);
	
	static void IDCT_Lines(int *inputData, float *outputData);

 public:
	static void doFDCT(int *inputData, int *outputData); // input char 8x8 array ... output int 8x8 array

	static void doIDCT(float *inputData, int *outputData); // input float 8x8 array ... output char 8x8 array

	static void doIDCT(int *inputData, int *outputData); // input int 8x8 array ... output char 8x8 array
};

extern DCTClass DCT;
#endif

