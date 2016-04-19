// JPEGHeadersDefinition.h

#ifndef _JPEGHEADERSDEFINITION_h
#define _JPEGHEADERSDEFINITION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "JPEG_Macros.h"

// Functions with datatypes in this definition
void printAPP0(struct APP0_Segment APP0);
void printDQT(struct DQT_Segment DQT);
void printDHT(struct DHT_Segment DHT);
void printSOS(struct SOS_Segment SOS);
void printSOF0(struct SOF0_Segment SOF0);

struct APP0_Segment
{
	unsigned int APP0_Length;
	unsigned char APP0_Identifier[APP0_JPEG_IDENTIFIER_LENGTH];
	unsigned char APP0_JPEGVersion[APP0_JPEG_VERSION_LENGTH]; //First byte Version, second Subversion of JPEG
	unsigned char APP0_DensityUnits;
	unsigned char APP0_DensityX;
	unsigned char APP0_DensityY;
	unsigned int APP0_ThumbnailWidth;
	unsigned int APP0_ThumbnailHeight;
};

struct DQT_Segment
{
	//Supported only 8bit 8x8 table
	unsigned int DQT_Length;
	unsigned char DQT_TableNumber;
	unsigned char DQT_TablePrecision;
	unsigned char DQT_Table[JPEG_MCU_LENGTH][JPEG_MCU_LENGTH];
};
/*
struct DHT_Segment
{
	unsigned int DHT_Length;
	unsigned char DHT_Number; // 0-3, otherwise error
	unsigned char DHT_Type; // 0-1, otherwise error, 0 = DC, 1 = AC table
	unsigned char DHT_CodesCount[DHT_CODE_MAX_LENGTH]; // index 0 = Count of length 1, index 1 Count od length 2 .....
	// index 15 = lenght 16
};
*/
struct SOSColorComponent
{
	unsigned char  componentId;
	unsigned char  ACHuffmanTable;
	unsigned char  DCHuffmanTable;
};

struct SOS_Segment
{
	unsigned int SOS_Length;
	unsigned char SOS_scanComponentsCount; //  >= 1 and <=4, otherwise error
	struct SOSColorComponent components[SOS_MAX_COMPONENT_COUNT];

};

struct SOFColorComponent
{
	unsigned char  componentColor;
	unsigned char  samplingFactor;
	unsigned char  verticalSamplingFactor;
	unsigned char  horizontalSamplingFactor;
	unsigned char  DQT_TableNumber;
};

struct SOF0_Segment
{
	unsigned int SOF0_Length;
	unsigned char SOF0_BitPrecision; // supported only 8bit
	unsigned int SOF0_ImageHeight;
	unsigned int SOF0_ImageWidth;
	unsigned char SOF0_NumberOfColorComponents;
	struct SOFColorComponent components[SOF0_MAX_COMPONENT_COUNT];
};




#endif

