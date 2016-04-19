// CommonMacros.h

#ifndef _COMMONMACROS_h
#define _COMMONMACROS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//Export File

#define PATH_MAX_LENGTH 30
#define EXPORT_FOLDER "/EXPORT"
#define EXPORT_PATH "/EXPORT/"
#define EXPORT_FILE_ENDING "bin"
#define JPEG_EXPORT_FILE_ENDING "jpg"
#define BMP_EXPORT_FILE_ENDING "bmp"

//Export file Color 
#define EXPORT_COLOR_RGB 0
#define EXPORT_COLOR_YCBCR 1

#define ZERO 0

#endif

