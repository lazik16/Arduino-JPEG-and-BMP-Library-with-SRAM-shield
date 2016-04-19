// JPEG.h

#ifndef _JPEG_h
#define _JPEG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SPIRamOrganization.h"
#include <SPI.h>
#include "SpiRAM.h"
#include <SD.h>
#include "JPEG_Macros.h"
#include "JPEGHeadersDefinition.h"
#include "DHTTable.h"
#include "ZigZag.h"
#include "BitRead.h"
#include "HuffmanCoding.h"
#include "Quantization.h"
#include "DCT.h"
#include "Color.h"
#include "ColorTransform.h"
#include "ExportFile.h"
#include "BitWrite.h"


class JPEG
{
private:
	 File inputJPEGFile, importFile;
	 File exportFile, headerFile;

	 //Working data
	 BitRead bitReadData;
	 BitWrite bitWriteData;
	 //float floatArray[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH]; // float array for DCT

	 signed int intArray[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH]; // int array for MCU work
	 signed int intArray1[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH]; // int array for MCU work
	 signed int intArray2[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH]; // int array for MCU work

	 //For color
	 signed int intArrayY0[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH]; // int array for MCU work
	 signed int intArrayY1[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH]; // int array for MCU work
	 signed int intArrayY2[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH]; // int array for MCU work
	 signed int intArrayY3[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH]; // int array for MCU work

	 signed int intArrayCb[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH]; // int array for MCU work
	 signed int intArrayCr[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH]; // int array for MCU work

	 signed int lineArray64[JPEG_MCU_COUNT]; // Array for transform with ZIG ZAG
	 signed int previsousDCvalue[SOF0_MAX_COMPONENT_COUNT] = {0,0,0}; // DC Y Cb Cr


	 // DQT from IRFAN for quality 75%
	 unsigned char quantizitonTableY[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH] = {{8,   6,   5,   8,  12,  20,  26,  31},
																		{6,   6,   7,  10,  13,  29,  30,  28},
																		{7,   7,   8,  12,  20,  29,  35,  28},
																		{7,   9,  11,  15,  26,  44,  40,  31},
																		{9,  11,  19,  28,  34,  55,  52,  39},
																		{12,  18,  28,  32,  41,  52,  57,  46},
																		{25,  32,  39,  44,  52,  61,  60,  51},
																		{36,  46,  48,  49,  56,  50,  52,  50}};

	 unsigned char quantizitonTableCbCr[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH] = {{ 9, 9, 12, 24, 50, 50, 50, 50 },
																			{ 9, 11, 13, 33, 50, 50, 50, 50 },
																			{ 12, 13, 28, 50, 50, 50, 50, 50 },
																			{ 24, 33, 50, 50, 50, 50, 50, 50 },
																			{ 50, 50, 50, 50, 50, 50, 50, 50 },
																			{ 50, 50, 50, 50, 50, 50, 50, 50 },
																			{ 50, 50, 50, 50, 50, 50, 50, 50 },
																			{ 50, 50, 50, 50, 50, 50, 50, 50 }};

	 unsigned char loadHeader();
	 unsigned char loadAPP0();
	 unsigned char loadAPP1();
	 unsigned char loadDQT();
	 unsigned char loadSOF0();
	 unsigned char loadDHT();
	 unsigned char loadSOS();
	 unsigned char loadImage();
	 unsigned char readMCUBlock(int* outputArray, unsigned char color, unsigned char DHTTable, unsigned char DQT_TableArray);
	 unsigned char transformColorToRGB(int* YArray, int* CbArray, int* CrArray); // color transform to input arrays
	 unsigned char transformColorToYCbCr(int* RArray, int* GArray, int* BArray, int* YArray, int* CbArray, int* CrArray);

	 unsigned char overSampleMatrix(int* input, int* output, unsigned char quad);
	 unsigned char downSampleMatrix(int* input, int* output, unsigned char quad);

	 unsigned char dumbColorDataToFile(File imageFile, unsigned int imageWidth, unsigned char colorDataFormat);
	 unsigned int  calculateNewImageSize(unsigned int oldSize, unsigned char multiplier);

	 unsigned char loadLineToSRAM(unsigned int &width, unsigned int &workWidth, unsigned long &offset);

	 unsigned char DCValueToFile(int* inputLineArray, unsigned char color);
	 unsigned char ZigZagArrayToFile(int* inputLineArray, unsigned char color);
	 unsigned char processDataInRAM(int workWidth);

 public:
	 SpiRAM sRAM = SpiRAM(SS_RAM_PIN);

	 // JPEG file information
	 APP0_Segment APP0_Variable;
	 char DQT_index = 0; // index for count DQT tables
	 DQT_Segment DQT_Table[JPEG_DQT_TABLES_COUNT]; //Supported only 8bit 8x8 table
	 char DHT_index = 0; // index for count DHT tables
	 DHTTable DHT_Tables[JPEG_DHT_TABLES_COUNT];
	 SOF0_Segment SOF0_Data;
	 SOS_Segment SOS_Data;

	 JPEG() {};
	 unsigned char open(char *inputFile);
	 unsigned char close();

	 void printInfo();

	 unsigned int readValue(unsigned char bitsCount);
	 unsigned char loadCodeFromDHT(unsigned char DHTtableID);

	 void printMatrix(int *inputData); // only debug 


	 unsigned char writeJPEG(char* inputFile);
};


#endif

