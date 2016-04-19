// JPEG_Macros.h

#ifndef _JPEG_MACROS_h
#define _JPEG_MACROS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define FF_MARKER 0xff
#define SOI_MARKER 0xd8
#define APP0_MARKER 0xe0
#define APP1_MARKER 0xe1
#define DQT_MARKER 0xdb
#define DHT_MARKER 0xc4
#define SOF0_MARKER 0xc0
#define SOF1_MARKER 0xc1
#define SOS_MARKER 0xda
#define EOI_MARKER 0xd9

#define RETURN_CODE_OK 1
#define RETURN_CODE_ERROR 0

#define JPEG_MCU_COUNT 64

#define STANDARD_APP0_LENGTH 16
#define APP0_JPEG_IDENTIFIER_LENGTH 5
#define APP0_JPEG_VERSION_LENGTH 2
#define APP0_JPEG_VERSION_INDEX 0
#define APP0_JPEG_SUBVERSION_INDEX 1

#define JPEG_DQT_TABLES_COUNT 2
#define DQT_VALUES_COUNT 64

#define DHT_TABLES_COUNT 4
#define DHT_CODE_MAX_LENGTH 16
#define DHT_MAX_CODES 255 // 255 + 0

#define SOS_MAX_COMPONENT_COUNT 3 // Supported only YCbCr model
#define SOS_SKIP_BYTES 3 // Bytes at end of SOS Marker

#define SOF0_MAX_COMPONENT_COUNT 3


#define JPEG_DHT_TABLES_COUNT 4

#define JPEG_MCU_LENGTH 8

#define JPEG_BITREAD_TYPE 1 // for recognize 0x00 after 0xff

#define JPEG_COLOR_Y 0
#define JPEG_COLOR_CB 1
#define JPEG_COLOR_CR 2

#define R_COLOR 0
#define G_COLOR 1
#define B_COLOR 2

#define JPEG_DHT_Y 0 // table 0 1 
#define JPEG_DHT_CB_CR 2 // table 2 3
#define JPEG_DQT_Y 0 // table 0
#define JPEG_DQT_CB_CR 1 // table 1


#define JPEG_COLOR_FORMAT_RGB 0 // 8 lines of RGB
#define JPEG_COLOR_FORMAT_RGB_DOWNSAMPLED 1 // 16 lines of R, 8 G,R must be oversampled
#define JPEG_COLOR_FORMAT_GRAYSCALE 2 // 8 lines of Color channel

#define JPEG_HUFFMAN_DC 0
#define JPEG_HUFFMAN_AC 1
#define JPEG_HUFFMAN_COLOR_Y 0
#define JPEG_HUFFMAN_COLOR_CB_CR 1
#define JPEG_HUFFMAN_COLOR_CB 1
#define JPEG_HUFFMAN_COLOR_CR 2

#define JPEG_HEADER_FILE1 "/HEADERS/HEADER1.bin" //from start file to SOF0
#define JPEG_HEADER_FILE2 "/HEADERS/HEADER2.bin" //after SOF0 to Huffman tables

#endif

