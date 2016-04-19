// BMP.h

#ifndef _BMP_h
#define _BMP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SPIRamOrganization.h"
#include <SPI.h>
#include "SpiRAM.h"
#include <SD.h>

#include "JPEGHeadersDefinition.h"

#include "ExportFile.h"
#include "BMPHeader.h"
#include "SPIRam.h"
#include "SPIRamOrganization.h"
#include "BitRead.h"
#include "Color.h"


class BMP
{
 private:
	 File inputBMPFile;
	 File exportImage;
	 BitRead bitReadData;


 public:
	 SpiRAM sRAM = SpiRAM(SS_RAM_PIN);

	 BMP() {};
	 unsigned char open(char *inputFile);
	 unsigned char close();

	 unsigned char writeFile(char *inputImage);

	 void printInfo();

	 unsigned char loadHeader();
	 unsigned char loadFileInfo();
	 unsigned char loadHeaderSegment();

	 unsigned long SDReadLong();
	 unsigned char SDWriteLong(unsigned long value);

	 unsigned char loadPalette(unsigned int colorCount);
	 unsigned long colorCalculate(unsigned bitPerPixel);
	 unsigned char decodeRLE8();
	 unsigned char decodeRLE4();
	 unsigned char fillByZeroColor(unsigned long count);

	 unsigned long rowSize;

	 BMPHeader_Segment BMPFileInfo;
	 BITMAPV5HEADER_Segment BMPHeaderSegment;
};


#endif

