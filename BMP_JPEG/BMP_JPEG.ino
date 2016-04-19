
#include "BMP.h"
#include "JPEG.h"
#include <SPI.h>
#include <SD.h>





#define SD_SSPIN 53 // Mega


unsigned long startTime[15];
unsigned long endTime[15];

void setup()
{

	/* add setup code here */
	Serial.begin(250000);

	if (!SD.begin(SD_SSPIN)) {
		Serial.println("Card failed, or not present");
		// don't do anything more:
		return;
	}
	Serial.println("card initialized.");

	delay(1000);
	JPEG JPEGImage;
	BMP BMPImage;

	
	
	//TIME TEST
/*
	startTime[0] = millis();
	//JPEGImage.open("osu80.jpg");
	JPEGImage.open("color1.jpg");
	endTime[0] = millis();

	startTime[1] = millis();
	//JPEGImage.open("osu160.jpg");
	JPEGImage.open("color2.jpg");
	endTime[1] = millis();

	startTime[2] = millis();
	//JPEGImage.open("osu320.jpg");
	JPEGImage.open("color3.jpg");
	endTime[2] = millis();

	Serial.print("TIME 1 : ");
	Serial.println(endTime[0] - startTime[0], DEC);

	Serial.print("TIME 2 : ");
	Serial.println(endTime[1] - startTime[1], DEC);

	Serial.print("TIME 3 : ");
	Serial.println(endTime[2] - startTime[2], DEC);
*/
	//END TIME TEST 

	

	//TIME TEST
	Serial.println("BMP Decompres");
	
	Serial.println("NEXT");
	startTime[0] = millis();
	BMPImage.open("testbmp.bmp");
	endTime[0] = millis();

	Serial.print("TIME 1 : ");
	Serial.println(endTime[0] - startTime[0], DEC);

	Serial.println("NEXT");
	startTime[1] = millis();
	BMPImage.open("bmp256c.bmp");
	endTime[1] = millis();

	Serial.print("TIME 2 : ");
	Serial.println(endTime[1] - startTime[1], DEC);

	Serial.println("NEXT");
	startTime[2] = millis();
	BMPImage.open("bmp16c.bmp");
	endTime[2] = millis();

	Serial.print("TIME 3 : ");
	Serial.println(endTime[2] - startTime[2], DEC);
	
	Serial.println("NEXT");
	startTime[3] = millis();
	BMPImage.open("bmp2c.bmp");
	endTime[3] = millis();

	Serial.print("TIME 4 : ");
	Serial.println(endTime[3] - startTime[3], DEC);

	Serial.println("NEXT");
	startTime[4] = millis();
	BMPImage.open("bmprle8.bmp");
	endTime[4] = millis();

	Serial.print("TIME 5 : ");
	Serial.println(endTime[4] - startTime[4], DEC);

	Serial.println("NEXT");
	startTime[5] = millis();
	BMPImage.open("bmprle4.bmp");
	endTime[5] = millis();
	
	Serial.print("TIME 1 : ");
	Serial.println(endTime[0] - startTime[0], DEC);

	Serial.print("TIME 2 : ");
	Serial.println(endTime[1] - startTime[1], DEC);

	Serial.print("TIME 3 : ");
	Serial.println(endTime[2] - startTime[2], DEC);

	Serial.print("TIME 4 : ");
	Serial.println(endTime[3] - startTime[3], DEC);

	Serial.print("TIME 5 : ");
	Serial.println(endTime[4] - startTime[4], DEC);

	Serial.print("TIME 6 : ");
	Serial.println(endTime[5] - startTime[5], DEC);
	/*
	startTime[0] = millis();
	JPEGImage.writeJPEG("/EXPORT/car.bin");
	endTime[0] = millis();
	
	startTime[1] = millis();
	JPEGImage.writeJPEG("/EXPORT/jing.bin");
	endTime[1] = millis();


	startTime[2] = millis();
	JPEGImage.writeJPEG("/EXPORT/puppy.bin");
	endTime[2] = millis();

	startTime[3] = millis();
	JPEGImage.writeJPEG("/EXPORT/pac.bin");
	endTime[3] = millis();

	startTime[4] = millis();
	JPEGImage.writeJPEG("/EXPORT/robot.bin");
	endTime[4] = millis();
	*/
	/*
	startTime[0] = millis();
	//JPEGImage.writeJPEG("/EXPORT/osu80.bin");
	//JPEGImage.writeJPEG("/EXPORT/color1.bin");
	//JPEGImage.writeJPEG("/EXPORT/natur.bin");
	JPEGImage.writeJPEG("/EXPORT/zelen.bin");
	endTime[0] = millis();
	*/
	/*
	startTime[1] = millis();
	//JPEGImage.writeJPEG("/EXPORT/osu160.bin");
	JPEGImage.writeJPEG("/EXPORT/color2.bin");
	endTime[1] = millis();

	
	startTime[2] = millis();
	//JPEGImage.writeJPEG("/EXPORT/osu320.bin");
	JPEGImage.writeJPEG("/EXPORT/color3.bin");
	endTime[2] = millis();

	startTime[3] = millis();
	JPEGImage.writeJPEG("/EXPORT/color.bin");
	endTime[3] = millis();
	*/
	/*
	Serial.print("TIME 1 : ");
	Serial.println(endTime[0] - startTime[0], DEC);

	Serial.print("TIME 2 : ");
	Serial.println(endTime[1] - startTime[1], DEC);

	Serial.print("TIME 3 : ");
	Serial.println(endTime[2] - startTime[2], DEC);

	Serial.print("TIME 4 : ");
	Serial.println(endTime[3] - startTime[3], DEC);

	Serial.print("TIME 5 : ");
	Serial.println(endTime[4] - startTime[4], DEC);

	BMPImage.writeFile("/EXPORT/robot.bin");
	*/
	//END TIME TEST 
/*
	Serial.println("Width 160");

	Serial.println("NEXT");
	startTime[0] = millis();
	JPEGImage.open("car.jpg");
	endTime[0] = millis();

	Serial.println("NEXT");
	startTime[1] = millis();
	JPEGImage.open("jing.jpg");
	endTime[1] = millis();

	Serial.println("NEXT");
	startTime[2] = millis();
	JPEGImage.open("puppy.jpg");
	endTime[2] = millis();

	Serial.println("NEXT");
	startTime[3] = millis();
	JPEGImage.open("natur.jpg");
	endTime[3] = millis();

	Serial.println("NEXT");
	startTime[4] = millis();
	JPEGImage.open("robot.jpg");
	endTime[4] = millis();

	Serial.print("TIME 1 : ");
	Serial.println(endTime[0] - startTime[0], DEC);

	Serial.print("TIME 2 : ");
	Serial.println(endTime[1] - startTime[1], DEC);

	Serial.print("TIME 3 : ");
	Serial.println(endTime[2] - startTime[2], DEC);

	Serial.print("TIME 4 : ");
	Serial.println(endTime[3] - startTime[3], DEC);

	Serial.print("TIME 5 : ");
	Serial.println(endTime[4] - startTime[4], DEC);
*/
/*
	Serial.println("Width 320");

	Serial.println("NEXT");
	startTime[0] = millis();
	JPEGImage.open("car1.jpg");
	endTime[0] = millis();

	Serial.println("NEXT");
	startTime[1] = millis();
	JPEGImage.open("jing1.jpg");
	endTime[1] = millis();

	Serial.println("NEXT");
	startTime[2] = millis();
	JPEGImage.open("puppy1.jpg");
	endTime[2] = millis();

	Serial.println("NEXT");
	startTime[3] = millis();
	JPEGImage.open("natur1.jpg");
	endTime[3] = millis();

	Serial.println("NEXT");
	startTime[4] = millis();
	JPEGImage.open("robot1.jpg");
	endTime[4] = millis();

	Serial.print("TIME 1 : ");
	Serial.println(endTime[0] - startTime[0], DEC);

	Serial.print("TIME 2 : ");
	Serial.println(endTime[1] - startTime[1], DEC);

	Serial.print("TIME 3 : ");
	Serial.println(endTime[2] - startTime[2], DEC);

	Serial.print("TIME 4 : ");
	Serial.println(endTime[3] - startTime[3], DEC);

	Serial.print("TIME 5 : ");
	Serial.println(endTime[4] - startTime[4], DEC);
*/
/*
	Serial.println("Width 640");

	Serial.println("NEXT");
	startTime[0] = millis();
	JPEGImage.open("car2.jpg");
	endTime[0] = millis();

	Serial.println("NEXT");
	startTime[1] = millis();
	JPEGImage.open("jing2.jpg");
	endTime[1] = millis();

	Serial.println("NEXT");
	startTime[2] = millis();
	JPEGImage.open("puppy2.jpg");
	endTime[2] = millis();

	Serial.println("NEXT");
	startTime[3] = millis();
	JPEGImage.open("natur2.jpg");
	endTime[3] = millis();

	Serial.println("NEXT");
	startTime[4] = millis();
	JPEGImage.open("robot2.jpg");
	endTime[4] = millis();

	Serial.print("TIME 1 : ");
	Serial.println(endTime[0] - startTime[0], DEC);

	Serial.print("TIME 2 : ");
	Serial.println(endTime[1] - startTime[1], DEC);

	Serial.print("TIME 3 : ");
	Serial.println(endTime[2] - startTime[2], DEC);

	Serial.print("TIME 4 : ");
	Serial.println(endTime[3] - startTime[3], DEC);

	Serial.print("TIME 5 : ");
	Serial.println(endTime[4] - startTime[4], DEC);
	*/

	//END TIME TEST 
	

}

void loop()
{
        
  /* add main program code here */

}

