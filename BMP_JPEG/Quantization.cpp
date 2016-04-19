// 
// 
// 

#include "Quantization.h"

void QuantizationClass::quantization(int *inputData, int *outputData, unsigned char *quantizationTable){
	signed int val = 0;

	for (int j = 0; j < JPEG_MCU_LENGTH; j++)
	{
		for (int i = 0; i < JPEG_MCU_LENGTH; i++)
		{
			val = *((inputData + j * JPEG_MCU_LENGTH) + i) / (signed int)(*((quantizationTable + j * JPEG_MCU_LENGTH) + i));
			*((outputData + j * JPEG_MCU_LENGTH) + i) = val;
		}
	}


}

void QuantizationClass::deQuantization(int *inputData, float *outputData, unsigned char *quantizationTable){

	for (int j = 0; j < JPEG_MCU_LENGTH; j++)
	{
		for (int i = 0; i < JPEG_MCU_LENGTH; i++)
		{
			*((outputData + j*JPEG_MCU_LENGTH) + i) = *((inputData + j*JPEG_MCU_LENGTH) + i) * (*((quantizationTable + j*JPEG_MCU_LENGTH) + i));
		}
	}


}

void QuantizationClass::deQuantization(int *inputData, int *outputData, unsigned char *quantizationTable){

	for (int j = 0; j < JPEG_MCU_LENGTH; j++)
	{
		for (int i = 0; i < JPEG_MCU_LENGTH; i++)
		{
			*((outputData + j*JPEG_MCU_LENGTH) + i) = *((inputData + j*JPEG_MCU_LENGTH) + i) * (*((quantizationTable + j*JPEG_MCU_LENGTH) + i));
		}
	}


}


QuantizationClass Quantization;

