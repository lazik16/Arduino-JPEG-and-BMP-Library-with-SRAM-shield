// 
// 
// 

#include "SPIRamOrganization.h"

unsigned long SPIRAMOrganizationClass::calculateSPIRamOffset(unsigned char tableIndex){
	unsigned long address = tableIndex * SPI_DHT_BLOCK;

	return address;
}

unsigned long SPIRAMOrganizationClass::calculateSPIRamColorOffset(unsigned char color, boolean downsaple){
	unsigned long address;

	switch (color)
	{
	case JPEG_COLOR_Y: address = Y_COLOR_OFFSET;
		break;
	case JPEG_COLOR_CB: if (downsaple)
						{
							address = CB_COLOR_OFFSET_DOWNSAMPLE;
						}
						else{
							address = CB_COLOR_OFFSET_NOT_DOWNSAMPLE;
						}
		break;
	case JPEG_COLOR_CR: if (downsaple)
						{
							address = CR_COLOR_OFFSET_DOWNSAMPLE;
						}
						else{
							address = CR_COLOR_OFFSET_NOT_DOWNSAMPLE;
						}
		break;
	}

	return address;
}

unsigned long SPIRAMOrganizationClass::calculateSPIRamExportOffset(unsigned char color){
	unsigned long address = 0;
	switch (color)
	{
	case R_COLOR: address = EXPORT_R_COLOR_OFFSET;
		break;
	case G_COLOR: address = EXPORT_G_COLOR_OFFSET;
		break;
	case B_COLOR: address = EXPORT_B_COLOR_OFFSET;
		break;
	}


	return address;
}

SPIRAMOrganizationClass SPIRAMOrganization;