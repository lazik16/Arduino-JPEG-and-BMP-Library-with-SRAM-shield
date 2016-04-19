// 
// 
// 

#include "BitRead.h"

BitRead::BitRead(File file){
	inputFile = file;
	bitsReadIndex = -1;
	fileType = 0;

	//DEBUG test for pointer
	//Serial.print("Bit read position ");
	//Serial.println(inputFile.position());
	
}

BitRead::BitRead(File file, unsigned char type){
	inputFile = file;
	bitsReadIndex = -1;
	fileType = type;
	lastByte = 0;
}

unsigned char BitRead::readBit(){
	unsigned char ret = 0;
	if (bitsReadIndex == -1)
	{
		lastByte = readedByte;
		readedByte = inputFile.read();

		if (fileType = JPEG_BITREAD_TYPE){ // only for JPEG use
			if ((lastByte == 0xff) && (readedByte == 0x00)) //skip 0x00 after 0xff
			{
				//Serial.println("BITREAD SKIP");
				readedByte = inputFile.read();
			}
		}

		bitsReadIndex = 7;
		
		
		//Serial.print("BitRead loaded byte ");
		//Serial.println(readedByte, BIN);
	 
	}

	
	ret = bitRead(readedByte, bitsReadIndex);
	//Serial.print("BitRead index ");
	//Serial.print(bitsReadIndex, DEC);
	//Serial.print(" BitRead return ");
	//Serial.println(ret, BIN);

	bitsReadIndex--;

	return ret;
}

void BitRead::flush(){
	bitsReadIndex = -1;
}
