// BitReadWrite.h

#ifndef _BITREAD_h
#define _BITREAD_h


	#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SD.h>

#define JPEG_BITREAD_TYPE 1

class BitRead
{
 private:
	 File inputFile;
	 unsigned char readedByte;
	 signed char bitsReadIndex;
	 unsigned char fileType;
	 unsigned char lastByte;

 public:
	 BitRead(void) {};
	 BitRead(File file); // constructor
	 BitRead(File file, unsigned char type); // constructor for JPEG file 
	 unsigned char readBit(); // read one bit
	 void flush(); // errase loaded data
	 //void test(){ Serial.print("Bit pos "); Serial.println(inputFile.position()); }
};


#endif

