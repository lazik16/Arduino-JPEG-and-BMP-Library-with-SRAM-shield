// ExportFile.h

#ifndef _EXPORTFILE_h
#define _EXPORTFILE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SD.h>
#include <SPI.h>

#include "CommonMacros.h"
#include "SPIRamOrganization.h"

class ExportFileClass
{
 protected:


 public:
	 static File createFileWithHeaderInfo(char* imageName, unsigned int imageWidth, unsigned int imageHeight, unsigned char colorFormat);
	 static File createFileForJPEG(char* imageName);
	 static File createFileForBMP(char* imageName);
};

extern ExportFileClass ExportFile;

#endif

