// 
// 
// 

#include "BMP.h"

unsigned char BMP::open(char *inputFile){
	//Serial.println(inputFile);
	inputBMPFile = SD.open(inputFile);
	inputBMPFile.seek(0);

	//Serial.print("BMP Bit read position ");
	Serial.println(inputBMPFile.position());


	loadHeader();

	rowSize = ((BMPHeaderSegment.bV5BitCount * BMPHeaderSegment.bV5Width + 31) / 32) * 4;
	//Serial.print("Row size: ");
	//Serial.println(rowSize, DEC);

	

	
	if (BMPHeaderSegment.bV5Compression == BI_RGB){

		//1bpp
		if ((BMPHeaderSegment.bV5BitCount == COLOR_1B)){

			if(BMPHeaderSegment.bV5ClrUsed == 0){
				BMPHeaderSegment.bV5ClrUsed = colorCalculate(BMPHeaderSegment.bV5BitCount);

			}

			loadPalette(BMPHeaderSegment.bV5ClrUsed);

			inputBMPFile.seek(BMPFileInfo.bfOffBits);

			exportImage = ExportFile.createFileWithHeaderInfo(inputBMPFile.name(), BMPHeaderSegment.bV5Width, BMPHeaderSegment.bV5Height, EXPORT_COLOR_RGB);
		
			//Serial.println("Export 1bit");
			bitReadData = BitRead(inputBMPFile);

			for (unsigned long j = 0; j < BMPHeaderSegment.bV5Height; j++)
			{
				for (unsigned long i = 0; i < BMPHeaderSegment.bV5Width; i++)
				{
					if (!bitReadData.readBit()){
						for (unsigned char i = 0; i < 3; i++)
						{
							exportImage.write(sRAM.readByte(i));
						}
					
					}
					else{
						for (unsigned char i = 3; i < 6; i++)
						{
							exportImage.write(sRAM.readByte(i));
						}
					}
					
				}

				bitReadData.flush();

				//Serial.print(inputBMPFile.position(), DEC);
				//Serial.print(" ");

				//Serial.println(BMPFileInfo.bfOffBits + (j+1)*rowSize, DEC);
				inputBMPFile.seek(BMPFileInfo.bfOffBits + (j + 1)*rowSize);
			}

			exportImage.close();

			for (unsigned char i = 0; i < 6; i++)
			{
				//Serial.println(sRAM.readByte(i));
			}
		}

		//2bpp
		if ((BMPHeaderSegment.bV5BitCount == COLOR_2B)){

			if (BMPHeaderSegment.bV5ClrUsed == 0){
				BMPHeaderSegment.bV5ClrUsed = colorCalculate(BMPHeaderSegment.bV5BitCount);

			}

			loadPalette(BMPHeaderSegment.bV5ClrUsed);

			inputBMPFile.seek(BMPFileInfo.bfOffBits);

			exportImage = ExportFile.createFileWithHeaderInfo(inputBMPFile.name(), BMPHeaderSegment.bV5Width, BMPHeaderSegment.bV5Height, EXPORT_COLOR_RGB);

			//Serial.println("Export 2bit");
			bitReadData = BitRead(inputBMPFile);

			unsigned char value;

			for (unsigned long j = 0; j < BMPHeaderSegment.bV5Height; j++)
			{
				for (unsigned long i = 0; i < BMPHeaderSegment.bV5Width; i++)
				{
					value = bitReadData.readBit() << 1;
					value |= bitReadData.readBit();

					//Serial.println(value);

					for (unsigned char i = value*3; i < (value*3+3); i++)
					{
						exportImage.write(sRAM.readByte(i));
					}

				}

				bitReadData.flush();

				//Serial.print(inputBMPFile.position(), DEC);
				//Serial.print(" ");

				//Serial.println(BMPFileInfo.bfOffBits + (j + 1)*rowSize, DEC);
				inputBMPFile.seek(BMPFileInfo.bfOffBits + (j + 1)*rowSize);
			}

			exportImage.close();

			for (unsigned char i = 0; i < 6; i++)
			{
				//Serial.println(sRAM.readByte(i));
			}
		}

		//4bpp
		if ((BMPHeaderSegment.bV5BitCount == COLOR_4B)){

			if (BMPHeaderSegment.bV5ClrUsed == 0){
				BMPHeaderSegment.bV5ClrUsed = colorCalculate(BMPHeaderSegment.bV5BitCount);

			}

			loadPalette(BMPHeaderSegment.bV5ClrUsed);

			inputBMPFile.seek(BMPFileInfo.bfOffBits);

			exportImage = ExportFile.createFileWithHeaderInfo(inputBMPFile.name(), BMPHeaderSegment.bV5Width, BMPHeaderSegment.bV5Height, EXPORT_COLOR_RGB);

			//Serial.println("Export 4bit");
			

			unsigned char value;
			unsigned char readed;

			for (unsigned long j = 0; j < BMPHeaderSegment.bV5Height; j++)
			{
				for (unsigned long i = 0; i < BMPHeaderSegment.bV5Width; i++)
				{
					//reading 1st or 2nd half of bit
					if (i % 2){
						value = readed & 0b00001111;
						//Serial.print("1 : ");
						//Serial.println(value, DEC);
					}
					else{
						readed = inputBMPFile.read();
						value = readed >> 4;
						//Serial.print("0 : ");
						//Serial.println(value, DEC);
					}

					for (unsigned long i = value * 3; i < (value * 3 + 3); i++)
					{
						//Serial.print("write ");
						//Serial.println(i);
						exportImage.write(sRAM.readByte(i));
					}

				}

				

				//Serial.print(inputBMPFile.position(), DEC);
				//Serial.print(" ");

				//Serial.println(BMPFileInfo.bfOffBits + (j + 1)*rowSize, DEC);
				inputBMPFile.seek(BMPFileInfo.bfOffBits + (j + 1)*rowSize);
			}

			exportImage.close();

			
			for (unsigned int i = 0; i < BMPHeaderSegment.bV5ClrUsed*3; i++)
			{
			//Serial.println(sRAM.readByte(i));
			}
			
		}

		//8bpp
		if ((BMPHeaderSegment.bV5BitCount == COLOR_8B)){

			if (BMPHeaderSegment.bV5ClrUsed == 0){
				BMPHeaderSegment.bV5ClrUsed = colorCalculate(BMPHeaderSegment.bV5BitCount);

			}

			loadPalette(BMPHeaderSegment.bV5ClrUsed);

			inputBMPFile.seek(BMPFileInfo.bfOffBits);

			exportImage = ExportFile.createFileWithHeaderInfo(inputBMPFile.name(), BMPHeaderSegment.bV5Width, BMPHeaderSegment.bV5Height, EXPORT_COLOR_RGB);

			//Serial.println("Export 8bit");
			

			unsigned long value;
			unsigned long startAddressForData = (unsigned long)BMPHeaderSegment.bV5ClrUsed * 3;
			//Serial.print("Color adr ");
			//Serial.println(startAddressForData);

			
			for (unsigned long j = 0; j < BMPHeaderSegment.bV5Height; j++)
			{
				//load line to SRAM
				for (unsigned long i = startAddressForData; i < (startAddressForData + (BMPHeaderSegment.bV5Width)); i++)
				{
					//Serial.println(i);
					sRAM.writeByte(i, inputBMPFile.read());
				}

				//decode data in SRAM with palete to SD
				for (unsigned long i = startAddressForData; i < (startAddressForData + (BMPHeaderSegment.bV5Width)); i++)
				{
					//Serial.println(i, DEC);
					value = sRAM.readByte(i);

					for (unsigned long i = value * 3; i < (value * 3 + 3); i++)
					{
						//Serial.print("write ");
						//Serial.println(i);
						exportImage.write(sRAM.readByte(i));
					}
				}

				//Serial.print(inputBMPFile.position(), DEC);
				//Serial.print(" ");

				//Serial.println(inputBMPFile.position() + (rowSize - (BMPHeaderSegment.bV5Width)), DEC);
				inputBMPFile.seek(inputBMPFile.position() + (rowSize - (BMPHeaderSegment.bV5Width)));
			}

			exportImage.close();

			/*
			for (unsigned int i = 0; i < BMPHeaderSegment.bV5ClrUsed*3; i++)
			{
				Serial.println(sRAM.readByte(i));
			}
			*/
		}

		if (BMPHeaderSegment.bV5BitCount == COLOR_24B){

			inputBMPFile.seek(BMPFileInfo.bfOffBits);

			exportImage = ExportFile.createFileWithHeaderInfo(inputBMPFile.name(), BMPHeaderSegment.bV5Width, BMPHeaderSegment.bV5Height, EXPORT_COLOR_RGB);

			RGB color;
			unsigned long adr = 0;

			//Serial.println("Export 24bit");
			for (unsigned long j = 0; j < BMPHeaderSegment.bV5Height; j++)
			{

				adr = 0;
				//load line to SRAM
				for (unsigned long i = 0; i < (BMPHeaderSegment.bV5Width); i++)
				{
					color.b = inputBMPFile.read();
					color.g = inputBMPFile.read();
					color.r = inputBMPFile.read();

					//Serial.println(inputBMPFile.position());
					sRAM.writeByte(adr++, color.r);
					sRAM.writeByte(adr++, color.g);
					sRAM.writeByte(adr++, color.b);
					//Serial.println(sRAM.readByte(i));
					//sRAM.writeByte(i, inputBMPFile.read());
					//exportImage.write(inputBMPFile.read());
				}


				for (unsigned long i = 0; i < (3 * BMPHeaderSegment.bV5Width); i++)
				{
					//exportImage.write(inputBMPFile.read());
					exportImage.write(sRAM.readByte(i));
				}
				//Serial.print(inputBMPFile.position(), DEC);
				//Serial.print(" ");
				//Serial.println(inputBMPFile.position() + (rowSize - (3 * BMPHeaderSegment.bV5Width)), DEC);
				inputBMPFile.seek(inputBMPFile.position() + (rowSize - (3 * BMPHeaderSegment.bV5Width)));
			}

			exportImage.close();
		}
		//Serial.println("\nEND BITMAP");
		//Serial.print("BMP END read position ");
		//Serial.println(inputBMPFile.position());
		
	}

	//RLE8
	if (BMPHeaderSegment.bV5Compression == BI_RLE8)
	{
		loadPalette(BMPHeaderSegment.bV5ClrUsed);

		inputBMPFile.seek(BMPFileInfo.bfOffBits);

		exportImage = ExportFile.createFileWithHeaderInfo(inputBMPFile.name(), BMPHeaderSegment.bV5Width, BMPHeaderSegment.bV5Height, EXPORT_COLOR_RGB);

		//Serial.println("Export RLE8");

		decodeRLE8();

		exportImage.close();

		//Serial.println("\nEND BITMAP");
		//Serial.print("BMP END read position ");
		//Serial.println(inputBMPFile.position());
	}
	
	//RLE4
	if (BMPHeaderSegment.bV5Compression == BI_RLE4)
	{
		loadPalette(BMPHeaderSegment.bV5ClrUsed);

		inputBMPFile.seek(BMPFileInfo.bfOffBits);

		exportImage = ExportFile.createFileWithHeaderInfo(inputBMPFile.name(), BMPHeaderSegment.bV5Width, BMPHeaderSegment.bV5Height, EXPORT_COLOR_RGB);

		//Serial.println("Export RLE4");

		decodeRLE4();

		exportImage.close();

		//Serial.println("\nEND BITMAP");
		//Serial.print("BMP END read position ");
		//Serial.println(inputBMPFile.position());
	}

	
	close();
}

unsigned char BMP::writeFile(char *inputImage){

	unsigned long width, height;

	File importFile = SD.open(inputImage, FILE_READ);
	exportImage = ExportFile.createFileForBMP(inputImage);

	width = importFile.read() << 8 | importFile.read();
	//Serial.print("Width: ");
	//Serial.println(width, DEC);

	height = importFile.read() << 8 | importFile.read();
	//Serial.print("height: ");
	//Serial.println(height, DEC);

	importFile.read();

	exportImage.write(0x42); // B
	exportImage.write(0x4D);  // M

	rowSize = ((COLOR_24B * width + 31) / 32) * 4;
	//Serial.print("ROW ");
	//Serial.println(rowSize, DEC);


	unsigned char padding = rowSize - (width * 3);
	//Serial.print("PADDING ");
	//Serial.println(padding, DEC);

	SDWriteLong(BMP_HEADER_LENGTH + BITMAPINFOHEADER + height * rowSize); // file length

	SDWriteLong((unsigned long)0);

	SDWriteLong((unsigned long)54); // image offset 14 + 40

	SDWriteLong(BITMAPINFOHEADER);
	SDWriteLong(width);
	SDWriteLong(height);

	exportImage.write((unsigned char)0x01);
	exportImage.write((unsigned char)0x00);

	exportImage.write((unsigned char)COLOR_24B);
	exportImage.write((unsigned char)0x00);

	SDWriteLong(BI_RGB);
	SDWriteLong(0x00);

	SDWriteLong(0x00);
	SDWriteLong(0x00);

	SDWriteLong(0x00);
	SDWriteLong(0x00);

	unsigned long offset;
	RGB color;

	for (signed long i = height-1; i >= 0; i--)
	{
		//calculate offset in file
		offset = BIN_FILE_OFFSET + 3 * width * i;
		importFile.seek(offset);
		//Serial.print("OFFSET ");
		//Serial.println(offset, DEC);

		for (unsigned long j = 0; j < width; j++)
		{
			color.r = importFile.read();
			color.g = importFile.read();
			color.b = importFile.read();

			exportImage.write(color.b);
			exportImage.write(color.g);
			exportImage.write(color.r);
		}

		for (char p = 0; p < padding; p++)
		{
			exportImage.write((unsigned char)0x00); //write padding byte
		}
	}

	importFile.close();
	exportImage.close();
}


unsigned char BMP::loadHeader(){
	loadFileInfo();
	printBMPFileHeader(BMPFileInfo);

	loadHeaderSegment();
	printBirmapV5Header(BMPHeaderSegment);

	//Serial.print("Position: ");
	//Serial.println(inputBMPFile.position(),DEC);
}

unsigned char BMP::loadFileInfo(){
	
	for (char i = 0; i < BMP_HEADER_IDENTIFIER_LENGTH; i++)
	{
		BMPFileInfo.bfType[i] = inputBMPFile.read();
	}

	BMPFileInfo.bfSize = SDReadLong();
	BMPFileInfo.bfReserved1 = inputBMPFile.read()  | inputBMPFile.read()<< 8;
	BMPFileInfo.bfReserved2 = inputBMPFile.read()  | inputBMPFile.read()<< 8;
	BMPFileInfo.bfOffBits = SDReadLong();

	return RETURN_CODE_OK;
}

unsigned char BMP::loadHeaderSegment(){

	BMPHeaderSegment.bV5Size = SDReadLong();
	BMPHeaderSegment.bV5Width = SDReadLong();
	BMPHeaderSegment.bV5Height = SDReadLong();

	BMPHeaderSegment.bV5Planes = inputBMPFile.read() | inputBMPFile.read() << 8;
	BMPHeaderSegment.bV5BitCount = inputBMPFile.read() | inputBMPFile.read() << 8;

	BMPHeaderSegment.bV5Compression = SDReadLong();
	BMPHeaderSegment.bV5SizeImage = SDReadLong();

	BMPHeaderSegment.bV5XPelsPerMeter = SDReadLong();
	BMPHeaderSegment.bV5YPelsPerMeter = SDReadLong();
	BMPHeaderSegment.bV5ClrUsed = SDReadLong();
	BMPHeaderSegment.bV5ClrImportant = SDReadLong();
	//V4

	if ((BMPHeaderSegment.bV5Size == BITMAPV4HEADER) || (BMPHeaderSegment.bV5Size == BITMAPV5HEADER)){
		BMPHeaderSegment.bV5RedMask = SDReadLong();
		BMPHeaderSegment.bV5GreenMask = SDReadLong();
		BMPHeaderSegment.bV5BlueMask = SDReadLong();
		BMPHeaderSegment.bV5AlphaMask = SDReadLong();
		BMPHeaderSegment.bV5CSType = SDReadLong();

		for (char i = 0; i < 9; i++)
		{
			BMPHeaderSegment.bV5Endpoints[i] = SDReadLong();
		}

		BMPHeaderSegment.bV5GammaRed = SDReadLong();
		BMPHeaderSegment.bV5GammaGreen = SDReadLong();
		BMPHeaderSegment.bV5GammaBlue = SDReadLong();
	}
	//V5
	if (BMPHeaderSegment.bV5Size == BITMAPV5HEADER){
		BMPHeaderSegment.bV5Intent = SDReadLong();
		BMPHeaderSegment.bV5ProfileData = SDReadLong();
		BMPHeaderSegment.bV5ProfileSize = SDReadLong();
		BMPHeaderSegment.bV5Reserved = SDReadLong();
	}
	return RETURN_CODE_OK;
}

unsigned char BMP::close(){
	inputBMPFile.close();
}

void BMP::printInfo(){
	printBMPFileHeader(BMPFileInfo);
	printBirmapV5Header(BMPHeaderSegment);
}


unsigned long BMP::SDReadLong(){
	unsigned long ret = 0;
	ret = inputBMPFile.read();
	ret |= inputBMPFile.read() << 8;
	ret |= ((unsigned long)inputBMPFile.read()) << 16;
	ret |= ((unsigned long)inputBMPFile.read()) << 24;
	return ret;
}

unsigned char BMP::SDWriteLong(unsigned long value){
	
	exportImage.write((unsigned char)value);
	exportImage.write(value >> 8);
	exportImage.write(value >> 16);
	exportImage.write(value >> 24);
}

unsigned char BMP::loadPalette(unsigned int colorCount){
	RGB color;
	unsigned long adr = 0;

	for (unsigned int i = 0; i < colorCount; i++) // load 6bytes of color
	{
		/*
		if ((i>0) && ((i % 3) == 0)){//skip reserver byte
			//Serial.println("Skip Byte");
			inputBMPFile.seek(inputBMPFile.position() + 1);
		}
		*/
		color.b = inputBMPFile.read();
		color.g = inputBMPFile.read();
		color.r = inputBMPFile.read();

		//Serial.println(inputBMPFile.position());
		sRAM.writeByte(adr++, color.r);
		sRAM.writeByte(adr++, color.g);
		sRAM.writeByte(adr++, color.b);
		//Serial.println(sRAM.readByte(i));

		inputBMPFile.seek(inputBMPFile.position() + 1);

	}
}

unsigned long BMP::colorCalculate(unsigned bitPerPixel){
	unsigned long ret = 0;
	
	switch (bitPerPixel)
	{
	case 1: ret = 2;
		break;
	case 2: ret = 4;
		break;
	case 4: ret = 16;
		break;
	case 8: ret = 256;
		break;

	default: ret = 0;
		break;
	}

	return ret;
}

unsigned char BMP::decodeRLE8(){
	unsigned char cmd;
	unsigned char value;
	unsigned long width = 0;
	unsigned long height = 0;
	unsigned char stop = 0; // to exit from cycle


	while (!stop){
		cmd = inputBMPFile.read();
		value = inputBMPFile.read();

		//Serial.print("CMD: ");
		//Serial.print(cmd, DEC);
		//Serial.print(" Val: ");
		//Serial.println(value, DEC);

		if (cmd != RLE_ESCAPE){ // compress data
			for (unsigned int i = 0; i < cmd; i++)
			{
				for (unsigned long i = (unsigned long)value * 3; i < ((unsigned long)value * 3 + 3); i++)
				{
					exportImage.write(sRAM.readByte(i));
				}

				width++;
			}
		}

		if (cmd == RLE_ESCAPE)
		{
			unsigned long zeros = 0;

			switch (value){
			case RLE_ENDLINE: // fill end of line by ZEROS

				if (width < BMPHeaderSegment.bV5Width){
					zeros = (BMPHeaderSegment.bV5Width - width - 1) * 3;
					fillByZeroColor(zeros);
				}
				
				/*
				Serial.print("ENDL Width: ");
				Serial.print(width);
				Serial.print(" zero: ");
				Serial.print(zeros);
				Serial.print(" height: ");
				Serial.println(height);
				*/

				width = 0;
				height++;

				break;
			case RLE_ENDBITMAP : // END of bitmap

				if (width < BMPHeaderSegment.bV5Width){// finish line
					zeros = (BMPHeaderSegment.bV5Width - width - 1) * 3;
					fillByZeroColor(zeros);

					height++;
				}

				if (height < BMPHeaderSegment.bV5Height-1){ //calculate lines to end BMP
					zeros += (BMPHeaderSegment.bV5Height - height - 1)*BMPHeaderSegment.bV5Width*3;
				}
				
				fillByZeroColor(zeros);

				/*
				Serial.print("ENDBMP Width: ");
				Serial.print(width);
				Serial.print(" zero: ");
				Serial.print(zeros);
				Serial.print(" height: ");
				Serial.println(height);
				*/

				stop = 1;
				break;

			case RLE_DELTA : // Move in bitmap, fill array between actual and new point bz zeros
				//Serial.println("Delta");
				//Serial.println(inputBMPFile.position());
				inputBMPFile.read();
				inputBMPFile.read();

				/*
				Serial.println(inputBMPFile.position());
				Serial.print("\nheight: ");
				Serial.println(height);

				Serial.println("END Delta");
				*/
				break;

			default: // absolute mode
				// value is count of noncompress bytes

				//Serial.println("Not compress: ");
				

				for (unsigned int i = 0; i < value; i++)
				{
					unsigned char inputByte = inputBMPFile.read();

					//Serial.print(inputByte);
					//Serial.print(" ");

					for (unsigned long i = (unsigned long)inputByte * 3; i < ((unsigned long)inputByte * 3 + 3); i++)
					{
						exportImage.write(sRAM.readByte(i));
					}

					width++;
				}

				if (value % 2) {// compensation odd bytes
					//Serial.println("Compensation");
					inputBMPFile.seek(inputBMPFile.position() + 1);
				}

				//Serial.println("\n End noncompresss");

				break;
			}
		}
		
	}
}

unsigned char BMP::decodeRLE4(){
	unsigned char cmd;
	unsigned char value;
	unsigned char color[2]; // byte are 2 colors
	unsigned long width = 0;
	unsigned long height = 0;
	unsigned char stop = 0; // to exit from cycle


	while (!stop){
		cmd = inputBMPFile.read();
		value = inputBMPFile.read();

		/*
		Serial.print("CMD: ");
		Serial.print(cmd, DEC);
		Serial.print(" Val: ");
		Serial.println(value, HEX);
		*/

		if (cmd != RLE_ESCAPE){ // compress data

			color[0] = (value & 0b11110000) >> 4;
			color[1] = value & 0b00001111;

			/*
			Serial.print(" Val: ");
			Serial.print(color[0], HEX);
			Serial.print(" ");
			Serial.println(color[1], HEX);
			*/

			for (unsigned int i = 0; i < cmd; i++)
			{
				if (i % 2){
					value = color[1];
				}
				else{
					value = color[0];
				}

				for (unsigned long i = (long)value * 3; i < ((long)value * 3 + 3); i++)
				{
					exportImage.write(sRAM.readByte(i));
				}

				width++;
			}
		}

		if (cmd == RLE_ESCAPE)
		{
			unsigned long zeros = 0;

			switch (value){
			case RLE_ENDLINE: // fill end of line by ZEROS

				if (width < BMPHeaderSegment.bV5Width){
					zeros = (BMPHeaderSegment.bV5Width - width - 1) * 3;
					fillByZeroColor(zeros);
				}

				/*
				Serial.print("ENDL Width: ");
				Serial.print(width);
				Serial.print(" zero: ");
				Serial.print(zeros);
				Serial.print(" height: ");
				Serial.println(height);
				*/

				width = 0;
				height++;

				break;
			case RLE_ENDBITMAP: // END of bitmap

				if (width < BMPHeaderSegment.bV5Width){// finish line
					zeros = (BMPHeaderSegment.bV5Width - width - 1) * 3;
					fillByZeroColor(zeros);

					height++;
				}

				if (height < BMPHeaderSegment.bV5Height - 1){ //calculate lines to end BMP
					zeros += (BMPHeaderSegment.bV5Height - height - 1)*BMPHeaderSegment.bV5Width * 3;
				}

				fillByZeroColor(zeros);

				/*
				Serial.print("ENDBMP Width: ");
				Serial.print(width);
				Serial.print(" zero: ");
				Serial.print(zeros);
				Serial.print(" height: ");
				Serial.println(height);
				*/

				stop = 1;
				break;

			case RLE_DELTA: // Move in bitmap, fill array between actual and new point bz zeros
				//Serial.println("Delta");
				//Serial.println(inputBMPFile.position());
				inputBMPFile.read();
				inputBMPFile.read();
				//Serial.println(inputBMPFile.position());
				//Serial.print("\nheight: ");
				//Serial.println(height);

				//Serial.println("END Delta");

				break;

			default: // absolute mode
				// value is count of noncompress bytes
				unsigned char loadByte;
				unsigned char colorForWrite;

				//Serial.println("Not compress: ");

				for (unsigned int i = 0; i < value; i++)
				{
					if (i % 2){
						colorForWrite = color[1];
						//Serial.print(color[1], HEX);
						//Serial.print(" ");
					}
					else{
						loadByte = inputBMPFile.read();
						color[0] = (loadByte & 0b11110000) >> 4;
						color[1] = loadByte & 0b00001111;

						colorForWrite = color[0];
						//Serial.print(color[0], HEX);
						//Serial.print(" ");
					}

					for (unsigned long i = (unsigned long)value * 3; i < ((unsigned long)value * 3 + 3); i++)
					{
						exportImage.write(sRAM.readByte(i));
					}

					width++;
				}

				// compensation odd bytes
				if (value % 2) { // allign odd
					value++;	
				}

				if ((value % 4) != 0) {
					//Serial.println("Compensation");
					inputBMPFile.seek(inputBMPFile.position() + 1);
				}

				

				//Serial.println("\n End noncompresss");

				break;
			}
		}

	}
}


unsigned char BMP::fillByZeroColor(unsigned long count){
	for (unsigned long i = 0; i < count * 3; i++)
	{
		exportImage.write((uint8_t)ZERO);
	}
}