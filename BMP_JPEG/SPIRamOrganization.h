// SPIRamOrganization.h

#ifndef _SPIRAMORGANIZATION_h
#define _SPIRAMORGANIZATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "JPEG_Macros.h"

#define SPIRAM_BYTES  131072 

#define SS_RAM_PIN 52 //Due
//#define SS_RAM_PIN 45 //MEGA
//#define SS_RAM_PIN 42 //SRAM SHIELD

#define SPI_DHT_BLOCK 256

//offset for color
#define COLOR_LINE_MAX_LENGTH_NOT_DOWNSAMPLE 5418
#define COLOR_LINE_MAX_LENGTH_DOWNSAMPLE 2709

#define Y_COLOR_OFFSET 1024 // Y is after DHT tables
#define R_COLOR_OFFSET 1024 // R is after DHT tables

#define CB_COLOR_OFFSET_NOT_DOWNSAMPLE  44368
#define G_COLOR_OFFSET_NOT_DOWNSAMPLE  44368
#define CB_COLOR_OFFSET_DOWNSAMPLE  87712 

#define CR_COLOR_OFFSET_NOT_DOWNSAMPLE  87712
#define B_COLOR_OFFSET_NOT_DOWNSAMPLE  87712
#define CR_COLOR_OFFSET_DOWNSAMPLE  109384 // controll....

#define COLOR_LINE_MULTIPLY_NOT_DOWNSAMPLE 8
#define COLOR_LINE_MULTIPLY_DOWNSAMPLE 16

#define EXPORT_LINE_MAX_LENGTH 2730
#define EXPORT_R_COLOR_OFFSET 0
#define EXPORT_G_COLOR_OFFSET 43680
#define EXPORT_B_COLOR_OFFSET 87360

class SPIRAMOrganizationClass
{
	public:
		static unsigned long calculateSPIRamOffset(unsigned char tableIndex);
		static unsigned long calculateSPIRamColorOffset(unsigned char color, boolean downsaple);
		static unsigned long calculateSPIRamExportOffset(unsigned char color);
};

extern SPIRAMOrganizationClass SPIRAMOrganization;
#endif

