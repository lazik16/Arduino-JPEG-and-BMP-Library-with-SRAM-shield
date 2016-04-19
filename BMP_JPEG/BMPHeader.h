// BMPHeader.h

#ifndef _BMPHEADER_h
#define _BMPHEADER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BMB_Macros.h"


// Functions with datatypes in this definition
void printBMPFileHeader(struct BMPHeader_Segment header);
void printBirmapV5Header(struct BITMAPV5HEADER_Segment header);

struct BMPHeader_Segment{
	unsigned char bfType[BMP_HEADER_IDENTIFIER_LENGTH]; //Identifier of BMP
	unsigned long bfSize; 
	unsigned int bfReserved1;
	unsigned int bfReserved2;
	unsigned long bfOffBits;
};

struct BITMAPV5HEADER_Segment{
	unsigned long bV5Size;
	unsigned long bV5Width;
	unsigned long bV5Height;
	unsigned int bV5Planes;
	unsigned int bV5BitCount;
	unsigned long bV5Compression;
	unsigned long bV5SizeImage;
	unsigned long bV5XPelsPerMeter;
	unsigned long bV5YPelsPerMeter;
	unsigned long bV5ClrUsed;
	unsigned long bV5ClrImportant;
	unsigned long bV5RedMask;
	unsigned long bV5GreenMask;
	unsigned long bV5BlueMask;
	unsigned long bV5AlphaMask;
	unsigned long bV5CSType;
	unsigned long bV5Endpoints[BMP_ENDPOINTS_COUNT];
	unsigned long bV5GammaRed;
	unsigned long bV5GammaGreen;
	unsigned long bV5GammaBlue;
	unsigned long bV5Intent;
	unsigned long bV5ProfileData;
	unsigned long bV5ProfileSize;
	unsigned long bV5Reserved;
};



#endif

