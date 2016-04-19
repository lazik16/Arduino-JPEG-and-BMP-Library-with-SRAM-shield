// BMB_Macros.h

#ifndef _BMB_MACROS_h
#define _BMB_MACROS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define BMP_HEADER_LENGTH 14
#define BMP_HEADER_IDENTIFIER_LENGTH 2

// Info headers
#define BITMAPINFOHEADER 40
#define BITMAPV4HEADER 108
#define BITMAPV5HEADER 124

#define BMP_ENDPOINTS_COUNT 9

#define COLOR_1B 1
#define COLOR_2B 2
#define COLOR_4B 4
#define COLOR_8B 8
#define COLOR_16B 16
#define COLOR_24B 24
#define COLOR_32B 32

#define BI_RGB 0
#define BI_RLE4 2 
#define BI_RLE8 1
#define BI_ALPHABITFIELDS 6

#define RLE_ESCAPE 0
#define RLE_ENDLINE 0
#define RLE_ENDBITMAP 1
#define RLE_DELTA 2

#define BIN_FILE_OFFSET 5

#endif

