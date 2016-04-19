// 
// 
// 

#include "ZigZag.h"

void ZigZagClass::doZigZag(int *inputData, int *outputData){

	byte numbersAtLine = 0;
	byte outputIterator = 0;
	byte row = 0;
	byte col = 0;

	//First half of matrix
	do{
		// up
		col = 0;
		row = numbersAtLine;

		do {
			outputData[outputIterator] = *((inputData + row*JPEG_MCU_LENGTH) + col);
			outputIterator++;
			row--;
			col++;

		} while (col <= numbersAtLine);

		numbersAtLine++;

		// down
		col = numbersAtLine;
		row = 0;

		do {
			outputData[outputIterator] = *((inputData + row*JPEG_MCU_LENGTH) + col);
			outputIterator++;
			row++;
			col--;

		} while (row <= numbersAtLine);

		numbersAtLine++;



	} while (numbersAtLine != JPEG_MCU_LENGTH);

	numbersAtLine--;

	//Second half of matrix
	do{
		// up
		col = JPEG_MCU_LENGTH - numbersAtLine;
		row = JPEG_MCU_LENGTH - 1;

		do {
			outputData[outputIterator] = *((inputData + row*JPEG_MCU_LENGTH) + col);
			outputIterator++;
			row--;
			col++;

		} while (col < JPEG_MCU_LENGTH);

		numbersAtLine--;

		// down
		col = JPEG_MCU_LENGTH - 1;
		row = JPEG_MCU_LENGTH - numbersAtLine;

		do {
			outputData[outputIterator] = *((inputData + row*JPEG_MCU_LENGTH) + col);
			outputIterator++;
			row++;
			col--;

		} while (row < JPEG_MCU_LENGTH);

		numbersAtLine--;

	} while (numbersAtLine > 1);


	// last number of matrix
	outputData[outputIterator] = *((inputData + (JPEG_MCU_LENGTH - 1)*JPEG_MCU_LENGTH) + (JPEG_MCU_LENGTH - 1));

}


void ZigZagClass::doInverseZigZag(int *inputData, unsigned char *outputData){

	byte numbersAtLine = 0;
	byte inputIterator = 0;
	byte row = 0;
	byte col = 0;

	//First half of matrix
	do{
		// up
		col = 0;
		row = numbersAtLine;

		do {
			*((outputData + row*JPEG_MCU_LENGTH) + col) = (unsigned char)inputData[inputIterator];
			inputIterator++;
			row--;
			col++;

		} while (col <= numbersAtLine);

		numbersAtLine++;

		// down
		col = numbersAtLine;
		row = 0;

		do {
			*((outputData + row*JPEG_MCU_LENGTH) + col) = (unsigned char)inputData[inputIterator];
			inputIterator++;
			row++;
			col--;

		} while (row <= numbersAtLine);

		numbersAtLine++;



	} while (numbersAtLine != JPEG_MCU_LENGTH);

	numbersAtLine--;

	//Second half of matrix
	do{
		// up
		col = JPEG_MCU_LENGTH - numbersAtLine;
		row = JPEG_MCU_LENGTH - 1;

		do {
			*((outputData + row*JPEG_MCU_LENGTH) + col) = (unsigned char)inputData[inputIterator];
			inputIterator++;
			row--;
			col++;

		} while (col < JPEG_MCU_LENGTH);

		numbersAtLine--;

		// down
		col = JPEG_MCU_LENGTH - 1;
		row = JPEG_MCU_LENGTH - numbersAtLine;

		do {
			*((outputData + row*JPEG_MCU_LENGTH) + col) = (unsigned char)inputData[inputIterator];
			inputIterator++;
			row++;
			col--;

		} while (row < JPEG_MCU_LENGTH);

		numbersAtLine--;

	} while (numbersAtLine > 1);


	// last number of matrix
	*((outputData + (JPEG_MCU_LENGTH - 1)*JPEG_MCU_LENGTH) + (JPEG_MCU_LENGTH - 1)) = (unsigned char)inputData[inputIterator];

}

void ZigZagClass::doInverseZigZag(int *inputData, int *outputData){

	byte numbersAtLine = 0;
	byte inputIterator = 0;
	byte row = 0;
	byte col = 0;

	//First half of matrix
	do{
		// up
		col = 0;
		row = numbersAtLine;

		do {
			*((outputData + row*JPEG_MCU_LENGTH) + col) = (int)inputData[inputIterator];
			inputIterator++;
			row--;
			col++;

		} while (col <= numbersAtLine);

		numbersAtLine++;

		// down
		col = numbersAtLine;
		row = 0;

		do {
			*((outputData + row*JPEG_MCU_LENGTH) + col) = (int)inputData[inputIterator];
			inputIterator++;
			row++;
			col--;

		} while (row <= numbersAtLine);

		numbersAtLine++;



	} while (numbersAtLine != JPEG_MCU_LENGTH);

	numbersAtLine--;

	//Second half of matrix
	do{
		// up
		col = JPEG_MCU_LENGTH - numbersAtLine;
		row = JPEG_MCU_LENGTH - 1;

		do {
			*((outputData + row*JPEG_MCU_LENGTH) + col) = (int)inputData[inputIterator];
			inputIterator++;
			row--;
			col++;

		} while (col < JPEG_MCU_LENGTH);

		numbersAtLine--;

		// down
		col = JPEG_MCU_LENGTH - 1;
		row = JPEG_MCU_LENGTH - numbersAtLine;

		do {
			*((outputData + row*JPEG_MCU_LENGTH) + col) = (int)inputData[inputIterator];
			inputIterator++;
			row++;
			col--;

		} while (row < JPEG_MCU_LENGTH);

		numbersAtLine--;

	} while (numbersAtLine > 1);


	// last number of matrix
	*((outputData + (JPEG_MCU_LENGTH - 1)*JPEG_MCU_LENGTH) + (JPEG_MCU_LENGTH - 1)) = (int)inputData[inputIterator];

}