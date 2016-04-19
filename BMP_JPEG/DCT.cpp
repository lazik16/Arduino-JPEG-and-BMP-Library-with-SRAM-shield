// 
// 
// 

#include "DCT.h"

void DCTClass::doFDCT(int *inputData, int *outputData)
{
	ValidateData.addNumber((int *)inputData, -128);
	ValidateData.validateData((int *)inputData, -127, 127);

	float workingDataArray[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH];
	//1D DCT LINES
	DCT_Lines(inputData, (float *) workingDataArray);

	//1D DCT ROWS
	DCT_Rows((float *) workingDataArray, outputData);
}

void DCTClass::DCT_Lines(int *inputData, float *outputData)
{
	float sum = 0;
	float xk, c;

	for (unsigned char vertical = 0; vertical < JPEG_MCU_LENGTH; vertical++)
	{
		for (unsigned char horizontal = 0; horizontal < JPEG_MCU_LENGTH; horizontal++)
		{
			sum = 0;

			for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
			{
				xk = *((inputData + vertical * JPEG_MCU_LENGTH) + j);
				c = (float)(PI_8)* (float)horizontal * ((float)j + 0.5);
				sum += xk * (float) cos(c);
			}
			if (horizontal == 0)
			{
				sum *= SQRT_05;
			}

			*((outputData + vertical* JPEG_MCU_LENGTH) + horizontal) = sum / 2.0;

		}
	}

}

void DCTClass::DCT_Rows(float *inputData, int *outputData)
{
	float sum = 0;
	float xk, c;

	for (unsigned char horizontal = 0; horizontal < JPEG_MCU_LENGTH; horizontal++)
	{
		for (unsigned char vertical = 0; vertical < JPEG_MCU_LENGTH; vertical++)
		{
			sum = 0;
			for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
			{
				xk = *((inputData + j * JPEG_MCU_LENGTH) + horizontal);
				c = (float)(PI_8) * (float)vertical * ((float)j + 0.5);
				sum += xk * (float)cos(c);
			}
			if (vertical == 0)
			{
				sum *= SQRT_05;
			}
			*((outputData + vertical * JPEG_MCU_LENGTH) + horizontal) = (signed int)(round(sum / 2.0));

		}
	}

}

void DCTClass::doIDCT(float *inputData, int *outputData)
{
	float workingDataArray[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH];
	//1D IDCT LINES
	IDCT_Lines(inputData,(float *) workingDataArray);

	//1D IDCT ROWS
	IDCT_Rows((float *) workingDataArray, outputData);
	ValidateData.addNumber((int *)outputData,128);
	ValidateData.validateData((int *)outputData, 0, 255);
}

void DCTClass::IDCT_Lines(float *inputData, float *outputData)
{


	for (int vertical = 0; vertical < JPEG_MCU_LENGTH; vertical++)
	{
		for (int horizontal = 0; horizontal < JPEG_MCU_LENGTH; horizontal++)
		{
			float sum = 0;
			for (int j = 0; j < JPEG_MCU_LENGTH; j++)
			{
				float xk = *((inputData + vertical*JPEG_MCU_LENGTH) + j);
				float c = (float)(PI / JPEG_MCU_LENGTH) * (float)j * ((float)horizontal + 0.5);
				sum += xk * cos(c);
				if (j == 0)
				{
					sum *= sqrt(0.5);
				}
			}


			*((outputData + vertical*JPEG_MCU_LENGTH) + horizontal) = sum / 2.0;

		}
	}

}

void DCTClass::IDCT_Rows(float *inputData, int *outputData)
{


	for (unsigned char horizontal = 0; horizontal < JPEG_MCU_LENGTH; horizontal++)
	{
		for (unsigned char vertical = 0; vertical < JPEG_MCU_LENGTH; vertical++)
		{

			float sum = 0;
			for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
			{
				float xk = *((inputData + j*JPEG_MCU_LENGTH) + horizontal);
				float c = (float)(PI / JPEG_MCU_LENGTH) * (float)j * ((float)vertical + 0.5);
				sum += xk * cos(c);
				if (j == 0)
				{
					sum *= sqrt(0.5);
				}
			}

			*((outputData + vertical*JPEG_MCU_LENGTH) + horizontal) = (int) round(sum / 2.0);
		}
	}
}

// int

void DCTClass::doIDCT(int *inputData, int *outputData)
{
	float workingDataArray[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH];
	//1D IDCT LINES
	IDCT_Lines(inputData, (float *)workingDataArray);

	//1D IDCT ROWS
	IDCT_Rows((float *)workingDataArray, outputData);
	ValidateData.addNumber((int *)outputData, 128);
	ValidateData.validateData((int *)outputData, 0, 255);
}

void DCTClass::IDCT_Lines(int *inputData, float *outputData)
{


	for (int vertical = 0; vertical < JPEG_MCU_LENGTH; vertical++)
	{
		for (int horizontal = 0; horizontal < JPEG_MCU_LENGTH; horizontal++)
		{
			float sum = 0;
			for (int j = 0; j < JPEG_MCU_LENGTH; j++)
			{
				float xk = *((inputData + vertical*JPEG_MCU_LENGTH) + j);
				float c = (float)(PI / JPEG_MCU_LENGTH) * (float)j * ((float)horizontal + 0.5);
				sum += xk * cos(c);
				if (j == 0)
				{
					sum *= sqrt(0.5);
				}
			}


			*((outputData + vertical*JPEG_MCU_LENGTH) + horizontal) = sum / 2.0;

		}
	}

}
