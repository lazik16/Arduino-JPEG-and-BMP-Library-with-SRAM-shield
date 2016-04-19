// 
// 
// 

#include "BitWrite.h"

BitWrite::BitWrite(void){
	bitsWriteIndex = 7;
	writeByte = 0;

	//DEBUG test for pointer
	//Serial.print("Bit read position ");
	//Serial.println(inputFile.position());

}

BitWrite::BitWrite(File file){
	outputFile = file;
	bitsWriteIndex = 7;
	writeByte = 0;

	//DEBUG test for pointer
	//Serial.print("Bit read position ");
	//Serial.println(inputFile.position());

}

unsigned char BitWrite::writeValue(unsigned int value, unsigned char length){
	
	//Serial.print("Val ");
	//Serial.print(value,BIN);
	//Serial.print(" ");
	
	//Serial.print(value, DEC);
	//Serial.print(" ");
	//Serial.print(" Len ");
	//Serial.println(length, DEC);
	


	for (signed char i = (length -1); i >= 0; i--)
	{
		bitWrite(writeByte, bitsWriteIndex, bitRead(value, i));
		//Serial.print("BITW ");
		//Serial.println(writeByte, BIN);
		bitsWriteIndex--;
		if (bitsWriteIndex < 0)
		{	
			bitsWriteIndex = 7;
			
			outputFile.write(writeByte);

			if (writeByte == 0xff){
				outputFile.write((unsigned char)0x00);
				//Serial.println("ZERO");
			}
			//Serial.print("Writed ");
			//Serial.print(writeByte, BIN);
			//Serial.print(" ");
			//Serial.println(bitsWriteIndex, DEC);
			writeByte = 0;
		}
	}


	return 1;
}

unsigned char BitWrite::writeLast(){
	outputFile.write(writeByte);
	//Serial.print("Writed ");
	//Serial.println(writeByte, BIN);
	writeByte = 0;
}