// 
// 
// 

#include "JPEGHeadersDefinition.h"

void printAPP0(struct APP0_Segment APP0)
{
	Serial.println("APP0 INFO");
	Serial.print("Length: ");
	Serial.print(APP0.APP0_Length);
	Serial.print("\nIdentifier: ");
	for (unsigned char i = 0; i < APP0_JPEG_IDENTIFIER_LENGTH; i++)
	{
		Serial.print(APP0.APP0_Identifier[i]);
	}
	Serial.print("\nVersion: ");
	Serial.print(APP0.APP0_JPEGVersion[APP0_JPEG_VERSION_INDEX],DEC);
	Serial.print(".");
	Serial.print(APP0.APP0_JPEGVersion[APP0_JPEG_SUBVERSION_INDEX],DEC);
	Serial.print("\nDensity units: ");
	Serial.print(APP0.APP0_DensityUnits,DEC);
	Serial.print("\nX density: ");
	Serial.print(APP0.APP0_DensityX,DEC);
	Serial.print("\nY density: ");
	Serial.print(APP0.APP0_DensityY,DEC);
	Serial.print("\nTH width: ");
	Serial.print(APP0.APP0_ThumbnailWidth,DEC);
	Serial.print("\nTH height: ");
	Serial.println(APP0.APP0_ThumbnailHeight,DEC);
}

void printDQT(struct DQT_Segment DQT)
{
	Serial.println("DQT INFO");
	Serial.print("Length: ");
	Serial.print(DQT.DQT_Length);
	Serial.print("\nTable number: ");
	Serial.print(DQT.DQT_TableNumber,DEC);
	Serial.print("\nPrecision: ");
	Serial.println(DQT.DQT_TablePrecision,DEC);
	for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++)
	{
		for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
		{
			Serial.print(DQT.DQT_Table[i][j], DEC);
			Serial.print(" ");
		}
		Serial.println(" ");
	}
}

void printSOS(struct SOS_Segment SOS)
{
	Serial.println("SOS INFO");
	Serial.print("Length ");
	Serial.print(SOS.SOS_Length);
	Serial.print("\nComponent count: ");
	Serial.println(SOS.SOS_scanComponentsCount,DEC);

	for (unsigned char i = 0; i < SOS.SOS_scanComponentsCount; i++)
	{
		Serial.print("ID: ");
		Serial.print(SOS.components[i].componentId,DEC);
		Serial.print("\nHuffman AC: ");
		Serial.print(SOS.components[i].ACHuffmanTable,DEC);
		Serial.print("\nHuffman DC: ");
		Serial.println(SOS.components[i].DCHuffmanTable, DEC);
	}
}


void printSOF0(struct SOF0_Segment SOF0)
{
	Serial.println("SOF0 INFO");
	Serial.print("Length ");
	Serial.print(SOF0.SOF0_Length);
	Serial.print("\nBit precision: ");
	Serial.print(SOF0.SOF0_BitPrecision,DEC);
	Serial.print("\nImage height: ");
	Serial.print(SOF0.SOF0_ImageHeight);
	Serial.print("\nImage width: ");
	Serial.print(SOF0.SOF0_ImageWidth);
	Serial.print("\nComponent count: ");
	Serial.println(SOF0.SOF0_NumberOfColorComponents, DEC);
	
	for (unsigned char i = 0; i < SOF0.SOF0_NumberOfColorComponents; i++)
	{
		Serial.print("Color: ");
		Serial.print(SOF0.components[i].componentColor, DEC);
		Serial.print("\nVertical sampling: ");
		Serial.print(SOF0.components[i].verticalSamplingFactor, DEC);
		Serial.print("\nHorizontal sampling: ");
		Serial.print(SOF0.components[i].horizontalSamplingFactor, DEC);
		Serial.print("\nDQT Table: ");
		Serial.println(SOF0.components[i].DQT_TableNumber, DEC);
	}
}
