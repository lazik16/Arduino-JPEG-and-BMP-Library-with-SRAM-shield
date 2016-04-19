// 
// 
// 

#include "ValidateData.h"

void ValidateDataClass::validateData(int *inputData, int minValue, int maxValue)
{
	for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++)
	{
		for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
		{
			if ((*((inputData + i * JPEG_MCU_LENGTH) + j)) < minValue)
				(*((inputData + i * JPEG_MCU_LENGTH) + j)) = minValue;

			if ((*((inputData + i * JPEG_MCU_LENGTH) + j)) > maxValue)
				(*((inputData + i * JPEG_MCU_LENGTH) + j)) = maxValue;
		}

	}

}

void ValidateDataClass::addNumber(int *inputData, int number) {
	for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++)
	{
		for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
		{
			(*((inputData + i * JPEG_MCU_LENGTH) + j)) += number;

		}

	}
}


ValidateDataClass ValidateData;

