// 
// 
// 

#include "BMPHeader.h"

void printBMPFileHeader(struct BMPHeader_Segment header)
{
	Serial.println("BMP INFO");
	Serial.print("Identifier: ");
	Serial.print((char)header.bfType[0]);
	Serial.print((char)header.bfType[1]);
	Serial.print("\nSize: ");
	Serial.print(header.bfSize, DEC);
	Serial.print("\nBitmap offset: ");
	Serial.println(header.bfOffBits,DEC);

}

void printBirmapV5Header(struct BITMAPV5HEADER_Segment header)
{
	Serial.println("BITMAPV5HEADER INFO");
	Serial.print("Header size: ");
	Serial.print(header.bV5Size,DEC);

	Serial.print("\nWidth: ");
	Serial.print(header.bV5Width, DEC);
	Serial.print("\nHeight: ");
	Serial.print(header.bV5Height, DEC);
	Serial.print("\nPlanes: ");
	Serial.print(header.bV5Planes, DEC);
	Serial.print("\nBitPerPixel: ");
	Serial.print(header.bV5BitCount, DEC);
	Serial.print("\nCompresion: ");
	Serial.print(header.bV5Compression, DEC);
	Serial.print("\nSize Image: ");
	Serial.print(header.bV5SizeImage, DEC);
	Serial.print("\nXPerMeter: ");
	Serial.println(header.bV5XPelsPerMeter, DEC);
	Serial.print("\nYPerMeter: ");
	Serial.println(header.bV5YPelsPerMeter, DEC);
	Serial.print("\nClrUsed: ");
	Serial.print(header.bV5ClrUsed, DEC);
	Serial.print("\nClr Important: ");
	Serial.print(header.bV5ClrImportant, DEC);

	if ((header.bV5Size == BITMAPV4HEADER) || (header.bV5Size == BITMAPV5HEADER)){
		Serial.print("\nR Mask: ");
		Serial.println(header.bV5RedMask, BIN);
		Serial.print("\nG Mask: ");
		Serial.println(header.bV5GreenMask, BIN);
		Serial.print("\nB Mask: ");
		Serial.println(header.bV5BlueMask, BIN);
		Serial.print("\nA Mask: ");
		Serial.println(header.bV5AlphaMask, BIN);

		Serial.print("\nCSType: ");
		Serial.println(header.bV5CSType, DEC);
		Serial.print("\nG Mask: ");

		for (unsigned char i = 0; i < 9; i++)
		{
			Serial.print(header.bV5Endpoints[i]);
			Serial.print("\n");
		}

		Serial.print("\nB Gama R: ");
		Serial.println(header.bV5GammaRed, DEC);
		Serial.print("\nA Gama G: ");
		Serial.println(header.bV5GammaGreen, DEC);
		Serial.print("\nA Gama B: ");
		Serial.println(header.bV5GammaBlue, DEC);
	}

	if (header.bV5Size == BITMAPV5HEADER){
		Serial.print("\nB Intent: ");
		Serial.println(header.bV5Intent, DEC);
		Serial.print("\nA Profile data: ");
		Serial.println(header.bV5ProfileData, DEC);
		Serial.print("\nA Profile size: ");
		Serial.println(header.bV5Size, DEC);
	}
}