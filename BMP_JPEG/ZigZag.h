// ZigZag.h

#ifndef _ZIGZAG_h
#define _ZIGZAG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "JPEG_Macros.h"


class ZigZagClass
{
	
	public :

		//static void doZigZag(int *inputData, int *outputData);  //input 8x8 matrix ... output array[64]
		static void doZigZag(int *inputData, int *outputData);  //input 8x8 matrix ... output array[64]
		static void doInverseZigZag(int *inputData, int *outputData);  //input array[64] ... output matrix 8x8
		static void doInverseZigZag(int *inputData, unsigned char *outputData);  //input array[64] ... output matrix 8x8
		
		
};

extern ZigZagClass ZigZag;

#endif

