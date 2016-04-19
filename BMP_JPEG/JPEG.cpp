// 
// 
// 

#include "JPEG.h"

#define START 0UL

unsigned char JPEG::open(char *inputFile)
{
	//Serial.println(inputFile);
	inputJPEGFile = SD.open(inputFile);
	inputJPEGFile.seek(START);
	
	//Serial.print("JPEG Bit read position ");
	//Serial.println(inputJPEGFile.position());


	bitReadData = BitRead(inputJPEGFile, JPEG_BITREAD_TYPE);

	DQT_index = 0;
	DHT_index = 0;
	
	loadHeader();

}

unsigned char JPEG::close(){
	inputJPEGFile.close();
}

void JPEG::printInfo(){
	printAPP0(APP0_Variable);
	
	printSOF0(SOF0_Data);

	for (unsigned char i = 0; i < DQT_index; i++)
	{
		printDQT(DQT_Table[i]);
	}

	for (unsigned char i = 0; i < DHT_index; i++)
	{
		DHT_Tables[i].printDHT();
	}
	printSOS(SOS_Data);
}

	


unsigned char JPEG::loadHeader()
{
	boolean loaded = false;
	unsigned char data = 0;
	
	do{
		data = inputJPEGFile.read();

		switch (data){
			case FF_MARKER: 
				//Serial.println("FF");
				break;

			case SOI_MARKER: //is JPEG file
				//Serial.println("SOI");
				
				break;

			case APP0_MARKER: 
				//Serial.println("APP0");
				loadAPP0();
				//printAPP0(APP0_Variable);
				
				break;

			case APP1_MARKER:
				loadAPP1();
				
				break;

			case DQT_MARKER: 
				//Serial.println("DQT");
				loadDQT();
				break;

			case DHT_MARKER:
				//Serial.println("DHT");
				loadDHT();
				//Serial.print("DHT index ");
				//Serial.println(DHT_index,DEC);

				break;

			case SOS_MARKER: 
				loadSOS();

				//Serial.println("IMAGE DATA");
				loadImage();
				loaded = true;
				return RETURN_CODE_OK;
				break;

			case SOF0_MARKER:
				//Serial.println("SOF0");
				loadSOF0();
				//printSOF0(SOF0_Data);
				break;

		}
	} while (data != EOI_MARKER);
	
	return RETURN_CODE_OK;
}

unsigned char JPEG::loadAPP0()
{
	APP0_Variable.APP0_Length = inputJPEGFile.read() << 8 | inputJPEGFile.read();
	for (char i = 0; i < APP0_JPEG_IDENTIFIER_LENGTH; i++)
	{
		APP0_Variable.APP0_Identifier[i] = inputJPEGFile.read();
	}
	APP0_Variable.APP0_JPEGVersion[APP0_JPEG_VERSION_INDEX] = inputJPEGFile.read();
	APP0_Variable.APP0_JPEGVersion[APP0_JPEG_SUBVERSION_INDEX] = inputJPEGFile.read();
	APP0_Variable.APP0_DensityUnits = inputJPEGFile.read();
	APP0_Variable.APP0_DensityX = inputJPEGFile.read() << 8 | inputJPEGFile.read();
	APP0_Variable.APP0_DensityY = inputJPEGFile.read() << 8 | inputJPEGFile.read();
	APP0_Variable.APP0_ThumbnailWidth = inputJPEGFile.read();
	APP0_Variable.APP0_ThumbnailHeight = inputJPEGFile.read();

	// while is on end of APP0 thumbnail, read it
	if (APP0_Variable.APP0_Length > STANDARD_APP0_LENGTH){
		for (char i = 0; i < APP0_Variable.APP0_Length - STANDARD_APP0_LENGTH; i++)
		{
			inputJPEGFile.read();
		}
	}

	return RETURN_CODE_OK;
}

unsigned char JPEG::loadAPP1()
{
	unsigned int APP1Length = inputJPEGFile.read() << 8 | inputJPEGFile.read();
	for (unsigned int i = 0; i < APP1Length - 2; i++)
	{
		inputJPEGFile.read();
	}

	return RETURN_CODE_OK;
}

unsigned char JPEG::loadDQT()
{
	DQT_Table[DQT_index].DQT_Length = inputJPEGFile.read() << 8 | inputJPEGFile.read();

	signed char data = inputJPEGFile.read();
	DQT_Table[DQT_index].DQT_TableNumber = 0b00001111 & data;
	DQT_Table[DQT_index].DQT_TablePrecision = data >> 4;
	//Serial.print("DQT VALUES");
	for (unsigned char i = 0; i < DQT_VALUES_COUNT; i++)
	{
		lineArray64[i] = inputJPEGFile.read();
		//Serial.print(lineArray64[i], HEX);
		//Serial.print(" ");
	}
	// transform to 8x8 DQT Array
	ZigZag.doInverseZigZag((int *)lineArray64, (unsigned char *)DQT_Table[DQT_index].DQT_Table);
	//Serial.println("END DQT VALUES");
	DQT_index++;
	return RETURN_CODE_OK;
}

unsigned char JPEG::loadSOF0()
{
	SOF0_Data.SOF0_Length = inputJPEGFile.read() << 8 | inputJPEGFile.read();
	SOF0_Data.SOF0_BitPrecision = inputJPEGFile.read();
	SOF0_Data.SOF0_ImageHeight = inputJPEGFile.read() << 8 | inputJPEGFile.read();
	SOF0_Data.SOF0_ImageWidth = inputJPEGFile.read() << 8 | inputJPEGFile.read();
	SOF0_Data.SOF0_NumberOfColorComponents = inputJPEGFile.read();
	for (unsigned char i = 0; i < SOF0_Data.SOF0_NumberOfColorComponents; i++)
	{
		SOF0_Data.components[i].componentColor = inputJPEGFile.read();
		SOF0_Data.components[i].samplingFactor = inputJPEGFile.read();
		SOF0_Data.components[i].verticalSamplingFactor = SOF0_Data.components[i].samplingFactor & 0b00001111;
		SOF0_Data.components[i].horizontalSamplingFactor = SOF0_Data.components[i].samplingFactor >> 4;
		SOF0_Data.components[i].DQT_TableNumber = inputJPEGFile.read();
	}
}

unsigned char JPEG::loadDHT()
{
	//Serial.print("loading dht");
	//Serial.println(DHT_index);
	DHT_Tables[DHT_index].DHT_Length = inputJPEGFile.read() << 8 | inputJPEGFile.read();
	unsigned char data = inputJPEGFile.read();
	DHT_Tables[DHT_index].DHT_Type = bitRead(data, 4);
	DHT_Tables[DHT_index].DHT_Number = data & 0b00001111;

	//load symbols and store do SPI SRAM
	//Serial.println("COUNT CODES");

	unsigned char codesCount = 0;

	for (unsigned char i = 0; i < DHT_CODE_MAX_LENGTH; i++)
	{
		DHT_Tables[DHT_index].DHT_CodesCount[i] = inputJPEGFile.read();
		
		
		DHT_Tables[DHT_index].DHT_CodesOffset[i] = codesCount; 
		
		//Serial.print(DHT_Tables[DHT_index].DHT_CodesCount[i], HEX);
		//Serial.print(" ");

		codesCount = codesCount + DHT_Tables[DHT_index].DHT_CodesCount[i];
	}
	//Serial.println("END COUNT CODES");
	// read codes
	//Serial.println(" SPI CODES");

	unsigned long address, workAddress;


	for (unsigned char i = 0; i < DHT_CODE_MAX_LENGTH; i++)
	{
		address = SPIRAMOrganization.calculateSPIRamOffset(DHT_index);  // base address of block in RAM

		for (unsigned char j = 0; j < DHT_Tables[DHT_index].DHT_CodesCount[i]; j++)
		{
			workAddress = address + DHT_Tables[DHT_index].DHT_CodesOffset[i] + j;
			//Serial.print("SPI adresa ");
			//Serial.print(workAddress, DEC);

			sRAM.writeByte(workAddress, inputJPEGFile.read());
			//Serial.print(" Test ");
			//Serial.println(sRAM.readByte(workAddress), HEX);
			
		}
	}
	//Serial.println("\nEND CODES");

	//DHT_Tables[DHT_index].printDHT();

	DHT_index++;
	return RETURN_CODE_OK;
}


unsigned char JPEG::loadSOS()
{
	SOS_Data.SOS_Length = inputJPEGFile.read() << 8 | inputJPEGFile.read();
	SOS_Data.SOS_scanComponentsCount = inputJPEGFile.read();
	for (unsigned char i = 0; i < SOS_Data.SOS_scanComponentsCount; i++)
	{
		SOS_Data.components[i].componentId = inputJPEGFile.read();
		unsigned char data = inputJPEGFile.read();
		SOS_Data.components[i].ACHuffmanTable = data & 0b00001111;
		SOS_Data.components[i].DCHuffmanTable = data >> 4;
	}
	
	inputJPEGFile.seek(inputJPEGFile.position() + SOS_SKIP_BYTES); // skip bytes;

	return RETURN_CODE_OK;
}

unsigned char JPEG::loadImage()
{
	unsigned long address;

	if (SOF0_Data.SOF0_NumberOfColorComponents == 1){// Grayscale picture
		for (unsigned int i = 0; i < ((SOF0_Data.SOF0_ImageWidth / 8) * (SOF0_Data.SOF0_ImageWidth / 8)); i++)
		{
			readMCUBlock((int *)intArrayY0, JPEG_COLOR_Y, JPEG_DHT_Y, JPEG_DQT_Y);
		}
	}
	else{
		// color picture not downsample
		if ((SOF0_Data.components[0].samplingFactor == 0x11) && (SOF0_Data.components[1].samplingFactor == 0x11) && (SOF0_Data.components[2].samplingFactor == 0x11)){
			//calculate new size by multiply 8
			//Serial.print("OLD size ");
			//Serial.print(SOF0_Data.SOF0_ImageWidth);
			//Serial.print("x");
			//Serial.println(SOF0_Data.SOF0_ImageHeight);

			SOF0_Data.SOF0_ImageWidth = calculateNewImageSize(SOF0_Data.SOF0_ImageWidth, 8);
			SOF0_Data.SOF0_ImageHeight = calculateNewImageSize(SOF0_Data.SOF0_ImageHeight, 8);

			//Serial.print("NEW size ");
			//Serial.print(SOF0_Data.SOF0_ImageWidth);
			//Serial.print("x");
			//Serial.println(SOF0_Data.SOF0_ImageHeight);


			File exportImage = ExportFile.createFileWithHeaderInfo(inputJPEGFile.name(), SOF0_Data.SOF0_ImageWidth, SOF0_Data.SOF0_ImageHeight, EXPORT_COLOR_RGB);

			for (unsigned int l = 0; l < (SOF0_Data.SOF0_ImageHeight / 8); l++){
				for (unsigned int mcu = 0; mcu < (SOF0_Data.SOF0_ImageWidth / 8); mcu++)
				{
					readMCUBlock((int *)intArrayY0, JPEG_COLOR_Y, JPEG_DHT_Y, JPEG_DQT_Y);
					readMCUBlock((int *)intArrayCb, JPEG_COLOR_CB, JPEG_DHT_CB_CR, JPEG_DQT_CB_CR);
					readMCUBlock((int *)intArrayCr, JPEG_COLOR_CR, JPEG_DHT_CB_CR, JPEG_DQT_CB_CR);
					transformColorToRGB((int *)intArrayY0, (int *)intArrayCb, (int *)intArrayCr);
					//Serial.println("RED");



					for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){
						address = SPIRAMOrganization.calculateSPIRamColorOffset(JPEG_COLOR_Y, false);
						address += i*SOF0_Data.SOF0_ImageWidth; // line offset
						address += mcu*JPEG_MCU_LENGTH; // row offset

						for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
						{
							/*
							Serial.print(intArrayY0[i][j], DEC);
							Serial.print(" ");
							Serial.print(address + j);
							*/
							sRAM.writeByte(address + j, (unsigned char)intArrayY0[i][j]);
							//Serial.print(" ");
						}
						//Serial.println(" ");
					}

					//Serial.println("GREEN");
					for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){
						address = SPIRAMOrganization.calculateSPIRamColorOffset(JPEG_COLOR_CB, false);
						address += i*SOF0_Data.SOF0_ImageWidth; // line offset
						address += mcu*JPEG_MCU_LENGTH; // row offset

						for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
						{
							//Serial.print(intArrayCb[i][j], DEC);
							//Serial.print(" ");
							//Serial.print(address + j);

							sRAM.writeByte(address + j, (unsigned char)intArrayCb[i][j]);
							//Serial.print(" ");
						}
						//Serial.println(" ");
					}

					//Serial.println("BLUE");
					for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){

						address = SPIRAMOrganization.calculateSPIRamColorOffset(JPEG_COLOR_CR, false);
						address += i*SOF0_Data.SOF0_ImageWidth; // line offset
						address += mcu*JPEG_MCU_LENGTH; // row offset

						for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
						{
							//Serial.print(intArrayCr[i][j], DEC);
							//Serial.print(" ");
							//Serial.print(address + j);

							sRAM.writeByte(address + j, (unsigned char)intArrayCr[i][j]);
							//Serial.print(" ");
						}
						//Serial.println(" ");
					}

					
				}
					// WRITE RGB to FILE
					
					dumbColorDataToFile(exportImage, SOF0_Data.SOF0_ImageWidth, JPEG_COLOR_FORMAT_RGB);
					


				}
				exportImage.close();
			}
		}
		// color picture downsampled
		if ((SOF0_Data.components[0].samplingFactor == 0x22) && (SOF0_Data.components[1].samplingFactor == 0x11) && (SOF0_Data.components[2].samplingFactor == 0x11)){
			
			//calculate new size by multiply 16
			/*
			Serial.print("OLD size ");
			Serial.print(SOF0_Data.SOF0_ImageWidth);
			Serial.print("x");
			Serial.println(SOF0_Data.SOF0_ImageHeight);
			*/

			SOF0_Data.SOF0_ImageWidth = calculateNewImageSize(SOF0_Data.SOF0_ImageWidth, 16);
			SOF0_Data.SOF0_ImageHeight = calculateNewImageSize(SOF0_Data.SOF0_ImageHeight, 16);
			
			/*
			Serial.print("NEW size ");
			Serial.print(SOF0_Data.SOF0_ImageWidth);
			Serial.print("x");
			Serial.println(SOF0_Data.SOF0_ImageHeight);
			*/

			File exportImage = ExportFile.createFileWithHeaderInfo(inputJPEGFile.name(), SOF0_Data.SOF0_ImageWidth, SOF0_Data.SOF0_ImageHeight, EXPORT_COLOR_RGB);
			
			for (unsigned int l = 0; l < (SOF0_Data.SOF0_ImageHeight / 16); l=l+1){

				/*
				Serial.print("NEW LINE ");
				Serial.println(l * 16,DEC);
				*/

				for (unsigned int mcu = 0; mcu < (SOF0_Data.SOF0_ImageWidth / 16); mcu=mcu+1)
				{
					readMCUBlock((int *)intArrayY0, JPEG_COLOR_Y, JPEG_DHT_Y, JPEG_DQT_Y);
					readMCUBlock((int *)intArrayY1, JPEG_COLOR_Y, JPEG_DHT_Y, JPEG_DQT_Y);
					readMCUBlock((int *)intArrayY2, JPEG_COLOR_Y, JPEG_DHT_Y, JPEG_DQT_Y);
					readMCUBlock((int *)intArrayY3, JPEG_COLOR_Y, JPEG_DHT_Y, JPEG_DQT_Y);
					readMCUBlock((int *)intArrayCb, JPEG_COLOR_CB, JPEG_DHT_CB_CR, JPEG_DQT_CB_CR);
					readMCUBlock((int *)intArrayCr, JPEG_COLOR_CR, JPEG_DHT_CB_CR, JPEG_DQT_CB_CR);
					

					//Y0 to SRAM

					for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){
						address = SPIRAMOrganization.calculateSPIRamColorOffset(JPEG_COLOR_Y, false);
						address += i*SOF0_Data.SOF0_ImageWidth; // line offset
						address += 2 * mcu*JPEG_MCU_LENGTH; // row offset

						//Serial.print("adr ");
						//Serial.println(address);

						for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
						{
							//Serial.print(intArrayY0[i][j], DEC);
							//Serial.print(" ");
							//Serial.print(address + j);

							sRAM.writeByte(address + j, (unsigned char)intArrayY0[i][j]);
							//Serial.print(" ");
						}
						//Serial.println(" ");
					}

					//Y1 to SRAM

					for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){
						address = SPIRAMOrganization.calculateSPIRamColorOffset(JPEG_COLOR_Y, false);
						address += i*SOF0_Data.SOF0_ImageWidth; // line offset
						address += (2*mcu + 1)*JPEG_MCU_LENGTH; // row offset

						//Serial.print("adr ");
						//Serial.println(address);

						for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
						{
							//Serial.print(intArrayY1[i][j], DEC);
							//Serial.print(" ");
							//Serial.print(address + j);

							sRAM.writeByte(address + j, (unsigned char)intArrayY1[i][j]);
							//Serial.print(" ");
						}
						//Serial.println(" ");
					}

					//Y2 to SRAM

					for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){
						address = SPIRAMOrganization.calculateSPIRamColorOffset(JPEG_COLOR_Y, false);
						address += (i + JPEG_MCU_LENGTH)*SOF0_Data.SOF0_ImageWidth; // line offset
						address += 2 * mcu*JPEG_MCU_LENGTH; // row offset

						//Serial.print("adr ");
						//Serial.println(address);

						for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
						{
							//Serial.print(intArrayY2[i][j], DEC);
							//Serial.print(" ");
							//Serial.print(address + j);

							sRAM.writeByte(address + j, (unsigned char)intArrayY2[i][j]);
							//Serial.print(" ");
						}
						//Serial.println(" ");
					}

					//Y3 to SRAM

					

					for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){
						address = SPIRAMOrganization.calculateSPIRamColorOffset(JPEG_COLOR_Y, false);
						address += (i + JPEG_MCU_LENGTH)*SOF0_Data.SOF0_ImageWidth; // line offset
						address += (2 * mcu + 1)*JPEG_MCU_LENGTH; // row offset

						//Serial.print("adr ");
						//Serial.println(address);

						for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
						{
							//Serial.print(intArrayY3[i][j], DEC);
							//Serial.print(" ");
							//Serial.print(address + j);

							sRAM.writeByte(address + j, (unsigned char)intArrayY3[i][j]);
							//Serial.print(" ");
						}
						//Serial.println(" ");
					}

					//Cb to SRAM
					for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){
						address = SPIRAMOrganization.calculateSPIRamColorOffset(JPEG_COLOR_CB, true);
						address += i*SOF0_Data.SOF0_ImageWidth/2; // line offset
						address += mcu*JPEG_MCU_LENGTH; // row offset

						//Serial.print("adr ");
						//Serial.println(address);

						for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
						{
							//Serial.print(intArrayCb[i][j], DEC);
							//Serial.print(" ");
							//Serial.print(address + j);

							sRAM.writeByte(address + j, (unsigned char)intArrayCb[i][j]);
							//Serial.print(" ");
						}
						//Serial.println(" ");
					}

					//Cr to SRAM
					for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){
						address = SPIRAMOrganization.calculateSPIRamColorOffset(JPEG_COLOR_CR, true);
						address += i*SOF0_Data.SOF0_ImageWidth/2; // line offset
						address += mcu*JPEG_MCU_LENGTH; // row offset

						//Serial.print("adr ");
						//Serial.println(address);

						for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
						{
							//Serial.print(intArrayCr[i][j], DEC);
							//Serial.print(" ");
							//Serial.print(address + j);

							sRAM.writeByte(address + j, (unsigned char)intArrayCr[i][j]);
							//Serial.print(" ");
						}
						//Serial.println(" ");
					}
				}

				// WRITE RGB to FILE

				dumbColorDataToFile(exportImage, SOF0_Data.SOF0_ImageWidth, JPEG_COLOR_FORMAT_RGB_DOWNSAMPLED);

			}

			exportImage.close();
		}
			
	
	return RETURN_CODE_OK;
}

unsigned char JPEG::readMCUBlock(int* outputArray, unsigned char color, unsigned char DHTTable, unsigned char DQT_TableIndex){
	//previsousDCvalue[color] = 0; // nulled previous dc value
	unsigned int value = 0;
	unsigned char length = loadCodeFromDHT(DHTTable);
	value = readValue(length);

	

	lineArray64[0] = previsousDCvalue[color] + HuffmanCoding.decodeFromHuffman(value, length); // first value is DC value, decode code to DPCM difference and calculate real value
	previsousDCvalue[color] = lineArray64[0];


	for (unsigned char i = 1; i < JPEG_MCU_COUNT; i++) // write 63 AC values
	{
		length = loadCodeFromDHT(DHTTable+1); // run zeros and length of code
		//Serial.println("Read from AC DHT ");
		//Serial.println(length, HEX);

		if (length == 0) // EOB code, no data
		{
			//Serial.println("EOB Zeros array i index ");
			while (i < JPEG_MCU_COUNT)
			{
				//Serial.print(i, DEC);
				//Serial.print(" ");
				lineArray64[i] = 0; // write zero
				i++;
			}
			//Serial.println("\nEnd EOB Zeros array i index ");
		}

		else{
			//Serial.println("Zeros array i index ");
			for (unsigned char j = 0; j < (length >> 4); j++)
			{
				//Serial.print(i, DEC);
				//Serial.print(" ");
				lineArray64[i] = 0; // write zero
				i++;
			}
			//Serial.println("\nEnd array i index ");

			length = length & 0b00001111; // length off data
			value = readValue(length);
			lineArray64[i] = HuffmanCoding.decodeFromHuffman(value, length);

		}
	}
	/*
	Serial.println("Line Array print");
	for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++)
	{
		Serial.print(lineArray64[i], DEC);
		Serial.print(" ");
	}
	Serial.println("\nEnd Array print");
	*/
	ZigZag.doInverseZigZag((int *)lineArray64, outputArray);
	/*
	Serial.println("Inverse ZIG");
	for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++)
	{
		for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
		{
			Serial.print((*((outputArray + i * JPEG_MCU_LENGTH) + j)), DEC);
			Serial.print(" ");
		}
		Serial.println(" ");
	}
	Serial.println("\nEnd Array print");
	*/
	Quantization.deQuantization(outputArray, (int *)intArray, (unsigned char *)DQT_Table[DQT_TableIndex].DQT_Table);
	/*
	Serial.println("Before IDCT");
	for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++)
	{
		for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
		{
			Serial.print(intArray[i][j], DEC);
			Serial.print(" ");
		}
		Serial.println(" ");
	}
	Serial.println("\nEnd Array print");
	*/
	DCT.doIDCT((int *)intArray, outputArray);
	/*
	Serial.println("Inverse DCT");
	for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++)
	{
		for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
		{
			Serial.print((*((outputArray + i * JPEG_MCU_LENGTH) + j)), DEC);
			Serial.print(" ");
		}
		Serial.println(" ");
	}
	Serial.println("\nEnd Array print");
	*/

}


unsigned int JPEG::readValue(unsigned char bitsCount){
	unsigned int valReaded = 0;
	unsigned char data;

	for (unsigned char i = 0; i < bitsCount; i++)
	{
		valReaded = valReaded << 1; // shift 1 bit to left
		
		data = bitReadData.readBit();

		if (data == 1){
			bitSet(valReaded, 0); // set last bit at 1
		}


		//Serial.print("readValue Loaded Val ");
		//Serial.println(valReaded, BIN);
	}
	

	return valReaded;
}


unsigned char JPEG::loadCodeFromDHT(unsigned char DHTTableIndex){ // Index in DHTTables array
	unsigned int generatedCodes = 0;
	unsigned int loadedVal = 0;
	unsigned char readedBitsCount = 1;
	unsigned char code;
	unsigned char data;

	while (1){
		data = bitReadData.readBit();
		if (data == 1){
			//Serial.println("BIT is 1");
			bitSet(loadedVal, 0); // set last bit at 1
		}else{
			//Serial.println("BIT is 0");
			bitWrite(loadedVal, 0, bitRead(data, 0));
		}
		
		//Serial.print("Loaded Value ");
		//Serial.println(loadedVal, BIN);

		if (DHT_Tables[DHTTableIndex].DHT_CodesCount[readedBitsCount - 1] > 0){ // if exist codes of length readedBitsCount
			//Serial.print("Found entry length: ");
			//Serial.println(readedBitsCount, DEC);

			// try find code in table,if found, return value of code
			for (struct { unsigned int genCode; unsigned int codeIndex; }v = {generatedCodes, 0}; v.codeIndex < DHT_Tables[DHTTableIndex].DHT_CodesCount[readedBitsCount - 1]; v.genCode++, v.codeIndex++)
			{
				//Serial.print("Gen code ");
				//Serial.println(v.genCode, BIN);

				if (loadedVal == v.genCode){ // if loaded code is the same as generated
					unsigned long address = SPIRAMOrganization.calculateSPIRamOffset(DHTTableIndex) + DHT_Tables[DHTTableIndex].DHT_CodesOffset[readedBitsCount - 1];
					address = address + v.codeIndex;
					//Serial.print("Address ");
					//Serial.print(address, DEC);
					//Serial.print(" Index ");
					//Serial.print(v.codeIndex, DEC);

					code = sRAM.readByte(address);
					//Serial.print(" Code from RAM ");
					//Serial.println(code, HEX);

					return code;
				}	
			}


		}


		// faster count of Huffman min value of code;
		if (readedBitsCount == 1){
			generatedCodes = DHT_Tables[DHTTableIndex].DHT_CodesCount[0] << 1;
		}
		else{
			generatedCodes = generatedCodes  + DHT_Tables[DHTTableIndex].DHT_CodesCount[readedBitsCount - 1] ;
			generatedCodes = generatedCodes << 1;
		}
		//Serial.print("Generated code ");
		//Serial.println(generatedCodes, DEC);


		loadedVal = loadedVal << 1; // shift readed value 1 bit left
		//Serial.print("After shift ");
		//Serial.println(loadedVal, BIN);
		readedBitsCount++; // increment number of readed bits
	}

	return code;
}

unsigned char JPEG::transformColorToRGB(int* YArray, int* CbArray, int* CrArray){
	
	unsigned char y, cb, cr;
	
	
	
	for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++)
	{
		for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
		{
			y = (*((YArray + i * JPEG_MCU_LENGTH) + j));
			cb = (*((CbArray + i * JPEG_MCU_LENGTH) + j));
			cr = (*((CrArray + i * JPEG_MCU_LENGTH) + j));
			
			RGB rgb = ColorTransform.YCbCrToRGB(y, cb, cr);

			(*((YArray + i * JPEG_MCU_LENGTH) + j)) = rgb.r;
			(*((CbArray + i * JPEG_MCU_LENGTH) + j)) = rgb.g;
			(*((CrArray + i * JPEG_MCU_LENGTH) + j)) = rgb.b;
		}

	}

	return RETURN_CODE_OK;
}

unsigned char JPEG::transformColorToYCbCr(int* RArray, int* GArray, int* BArray, int* YArray, int* CbArray, int* CrArray){

	RGB rgb;
	
	for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++)
	{
		for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++)
		{
			rgb.r = (*((RArray + i * JPEG_MCU_LENGTH) + j));
			rgb.g = (*((GArray + i * JPEG_MCU_LENGTH) + j));
			rgb.b = (*((BArray + i * JPEG_MCU_LENGTH) + j));

			YCbCr YCbCrColor= ColorTransform.RGBToYCbCr(rgb.r, rgb.g, rgb.b);

			(*((YArray + i * JPEG_MCU_LENGTH) + j)) = YCbCrColor.y;
			(*((CbArray + i * JPEG_MCU_LENGTH) + j)) = YCbCrColor.cb;
			(*((CrArray + i * JPEG_MCU_LENGTH) + j)) = YCbCrColor.cr;
		}

	}

	return RETURN_CODE_OK;
}

unsigned char JPEG::overSampleMatrix(int* input, int* output, unsigned char quad){
	/*
	QUADRANT
	-- | --
	| 0 | 1 |
	| 3 | 2 |
	-- | --
	*/

	int copyArray[4][4];

	int value;
	unsigned char i, j;
	switch (quad)
	{
	case 0:

		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){

				copyArray[i][j] = (*((input + i * JPEG_MCU_LENGTH) + j));
				//Serial.println(copyArray[i][j]);
			}
		}




		/*
		for (unsigned char i = 0; i < 4; i++){
		Serial.print("i: ");
		Serial.println(i);
		for (unsigned char j = 0; j < 4; j++){
		Serial.print("j: ");
		Serial.println(j);

		value = (*((input + i * JPEG_MCU_LENGTH) + j ));
		Serial.print("Val: ");
		Serial.println(value);

		(*((output + (2*i) * JPEG_MCU_LENGTH) + (2*j))) = value;
		(*((output + (2*i) * JPEG_MCU_LENGTH) + (2*j+1))) = value;
		(*((output + (2 * i + 1) * JPEG_MCU_LENGTH) + (2*j))) = value;
		(*((output + (2 * i + 1) * JPEG_MCU_LENGTH) + (2*j+1))) = value;
		}
		}
		*/
		break;

	case 1:

		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){

				copyArray[i][j] = (*((input + (i)* JPEG_MCU_LENGTH) + (j + 4)));
				//Serial.println(copyArray[i][j]);
			}
		}

		break;

	case 2:

		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){

				copyArray[i][j] = (*((input + (i + 4)* JPEG_MCU_LENGTH) + (j + 4)));
				//Serial.println(copyArray[i][j]);
			}
		}

		break;

	case 3:

		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){

				copyArray[i][j] = (*((input + (i + 4)* JPEG_MCU_LENGTH) + (j)));
				//Serial.println(copyArray[i][j]);
			}
		}

		break;
	}

	//expand copyArray to 8x8
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){

			(*((output + (2 * i) * JPEG_MCU_LENGTH) + (2 * j))) = copyArray[i][j];
			(*((output + (2 * i) * JPEG_MCU_LENGTH) + (2 * j + 1))) = copyArray[i][j];
			(*((output + (2 * i + 1) * JPEG_MCU_LENGTH) + (2 * j))) = copyArray[i][j];
			(*((output + (2 * i + 1) * JPEG_MCU_LENGTH) + (2 * j + 1))) = copyArray[i][j];
		}
	}


}

unsigned char JPEG::downSampleMatrix(int* input, int* output, unsigned char quad){
	/*
	QUADRANT
	-- | --
	| 0 | 1 |
	| 2 | 3 |
	-- | --
	*/

	int copyArray[4][4];
	int sum;


	int value;
	unsigned char i, j;

	// reduce 8x8 to 4x4
	for ( i = 0; i < JPEG_MCU_LENGTH ; i= i + 2)
	{
		sum = 0;

		for (j = 0; j < JPEG_MCU_LENGTH; j = j + 2)
		{
			sum = (*((input + i * JPEG_MCU_LENGTH) + j)) + (*((input + (i + 1) * JPEG_MCU_LENGTH) + j)) +
				(*((input + i * JPEG_MCU_LENGTH) + j + 1)) + (*((input + (i + 1) * JPEG_MCU_LENGTH) + j + 1));

			sum /= 4;
			copyArray[i / 2 ][ j / 2] = sum;
		}
	}



	switch (quad)
	{
	case 0:

		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				(*((output + (i) * JPEG_MCU_LENGTH) + (j))) = copyArray[i][j];
				
			}
		}

		break;

	case 1:

		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				(*((output + (i)* JPEG_MCU_LENGTH) + (j + 4))) = copyArray[i][j];
			}
		}

		break;

	case 2:

		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				(*((output + (i + 4)* JPEG_MCU_LENGTH) + (j))) = copyArray[i][j];
			}
		}

		break;

	case 3:

		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				(*((output + (i + 4)* JPEG_MCU_LENGTH) + (j + 4))) = copyArray[i][j];
			}
		}

		break;


	}
}

unsigned char JPEG::dumbColorDataToFile(File imageFile, unsigned int imageWidth, unsigned char colorDataFormat){
	if (imageFile)
	{
		switch (colorDataFormat)
		{
		case JPEG_COLOR_FORMAT_RGB:


			for (unsigned int i = 0; i < (imageWidth * JPEG_MCU_LENGTH); i++)
			{

				imageFile.write(sRAM.readByte(R_COLOR_OFFSET + i)); // R color
				imageFile.write(sRAM.readByte(G_COLOR_OFFSET_NOT_DOWNSAMPLE + i)); // G color
				imageFile.write(sRAM.readByte(B_COLOR_OFFSET_NOT_DOWNSAMPLE + i)); // B color
			}
			break;

		case JPEG_COLOR_FORMAT_RGB_DOWNSAMPLED:
			//Serial.println("DumpColorToFIleDOWNSAMLE");
			int pixCount;
			pixCount = 0;
			// 16 lines of Y
			int imgOffset;
			int CbCroffset;
			CbCroffset = 0;
			unsigned int i;

			for (unsigned line = 0; line < 2*JPEG_MCU_LENGTH; line++)
			{
				

				if (!(line % 2)){
					CbCroffset = line * imageWidth/4;
					//Serial.print("Second line ");
					//Serial.println(CbCroffset, DEC);
				}

				imgOffset = line * imageWidth;
				//Serial.print("New Line ");
				//Serial.println(imgOffset, DEC);

				// one line of picture
				for (i = 0; i < imageWidth ; i++)
				{
					unsigned char y, cb, cr;
					y = sRAM.readByte(Y_COLOR_OFFSET + imgOffset + i);

					cb = sRAM.readByte(CB_COLOR_OFFSET_DOWNSAMPLE + CbCroffset + i/2);

					cr = sRAM.readByte(CR_COLOR_OFFSET_DOWNSAMPLE + CbCroffset + i/2);

					RGB rgb = ColorTransform.YCbCrToRGB(y, cb, cr);

					//Serial.print("RGB ");
					imageFile.write(rgb.r); // R color
					//Serial.print(rgb.r, DEC);
					//Serial.print(" ");
					imageFile.write(rgb.g); // G color
					//Serial.print(rgb.g, DEC);
					//Serial.print(" ");
					imageFile.write(rgb.b); // B color
					//Serial.print(rgb.b, DEC);
					//Serial.println(" ");
					pixCount++;
				}
			}
			//Serial.print("PixCount ");
			//Serial.print(pixCount);
			break;

		default:
			break;
		}
	}
	else{
		return RETURN_CODE_ERROR;
	}
}

unsigned int  JPEG::calculateNewImageSize(unsigned int oldSize, unsigned char multiplier){
	unsigned int ret;

	if ((oldSize%multiplier) != 0){// calculate new size
		ret = oldSize / multiplier;
		ret++;
		ret *= multiplier;
	
	}
	else{
		ret = oldSize;
	}


	return ret;

}


unsigned char JPEG::writeJPEG(char* inputFile){



	unsigned int width, height, workWidth, workHeight;
	unsigned long addressR, addressG, addressB, offset;

	RGB colorRGB;

	previsousDCvalue[0] = 0;
	previsousDCvalue[1] = 0;
	previsousDCvalue[2] = 0;

	exportFile = ExportFile.createFileForJPEG(inputFile);
	bitWriteData = BitWrite(exportFile);

	// APP0 to SOF0 segment load from file
	headerFile = SD.open(JPEG_HEADER_FILE1);

	while (headerFile.available()) {
		exportFile.write(headerFile.read());
	}

	headerFile.close();

	importFile = SD.open(inputFile, FILE_READ);

	width = importFile.read() << 8 | importFile.read();
	//Serial.print("Width: ");
	//Serial.println(width, DEC);

	height = importFile.read() << 8 | importFile.read();
	//Serial.print("height: ");
	//Serial.println(height, DEC);

	importFile.read();
//
	// SOF0 SEGMENT
	exportFile.write(0xFF);
	exportFile.write(0xC0);

	exportFile.write((unsigned char)0); //length
	exportFile.write(0x11); // SOF0 length 17

	exportFile.write(0x08); // precission 8bit

	exportFile.write(height >> 8); // image height
	exportFile.write((unsigned char)height);

	exportFile.write(width >> 8); // image width
	exportFile.write((unsigned char)width);

	exportFile.write(0x03); // color channels

	//color channel infos
	exportFile.write(0x01);
	exportFile.write(0x22);
	exportFile.write((unsigned char)0);

	exportFile.write(0x02);
	exportFile.write(0x11);
	exportFile.write(0x01);

	exportFile.write(0x03);
	exportFile.write(0x11);
	exportFile.write(0x01);

	// after SOF0 fo huffman table from file
	headerFile = SD.open(JPEG_HEADER_FILE2);

	while (headerFile.available()) {
		exportFile.write(headerFile.read());
	}

	headerFile.close();


	/*
	// SOS SEGMENT
	exportFile.write(0xFF);
	exportFile.write(0xDA);
	*/
//

	//calculate size by multiply 16
	workWidth = calculateNewImageSize(width, 16);
	workHeight = calculateNewImageSize(height, 16);

	/*
	Serial.print("workW ");
	Serial.println(workWidth, DEC);
	Serial.print("workH ");
	Serial.println(workHeight, DEC);
	*/

	unsigned int standard16LinesBlock = height / 16; // standard lines without copying to 16lines
	unsigned int copyLines = height%16; // last lines to copy lines

	//Serial.print("std16Lines ");
	//Serial.println(standard16LinesBlock, DEC);
	//Serial.print("copyLines ");
	//Serial.println(copyLines, DEC);

	for (unsigned int lines = 0; lines < standard16LinesBlock; lines++)
	{
		//Serial.println("STD LINE ");
		//Serial.println(lines, DEC);

		// standard 16lines
		for (unsigned char line = 0; line < 16; line++) // load 16 lines of R, G, B
		{
			offset = line*workWidth;
			loadLineToSRAM(width, workWidth, offset);
		}

		//WORK JPEG operation

		processDataInRAM(workWidth);

	}

	if (height != workHeight)
	{
		// copy 16lines
		for (unsigned char line = 0; line < copyLines; line++) // load last lines of R, G, B
		{
			//Serial.println("LAST STD LINE");
			offset = line*workWidth;
			loadLineToSRAM(width, workWidth, offset);
		}

		for (unsigned char line = copyLines; line < 16; line++) // copy lines of R, G, B
		{
			//Serial.println("COPY LINE");

			offset = line*workWidth;

			addressR = SPIRAMOrganization.calculateSPIRamExportOffset(R_COLOR) + offset;
			addressG = SPIRAMOrganization.calculateSPIRamExportOffset(G_COLOR) + offset;
			addressB = SPIRAMOrganization.calculateSPIRamExportOffset(B_COLOR) + offset;
			/*
			Serial.println("COPY WRITE SRAM ");
			Serial.print(addressR, DEC);
			Serial.print(" ");
			Serial.print(addressG, DEC);
			Serial.print(" ");
			Serial.println(addressB, DEC);
			*/
			for (unsigned int i = 0; i < workWidth; i++)
			{

				sRAM.writeByte(addressR + i, sRAM.readByte(addressR + i - workWidth));
				sRAM.writeByte(addressG + i, sRAM.readByte(addressG + i - workWidth));
				sRAM.writeByte(addressB + i, sRAM.readByte(addressB + i - workWidth));
			}
		}

		//WORK JPEG operation
		processDataInRAM(workWidth);
	}




	bitWriteData.writeLast();
	// END FILE SEGMENT

	exportFile.write(0xFF);
	exportFile.write(0xD9);
	exportFile.close();

	return RETURN_CODE_OK;
}


unsigned char JPEG::loadLineToSRAM(unsigned int &width, unsigned int &workWidth, unsigned long &offset){
	unsigned long addressR, addressG, addressB;

	RGB colorRGB;

	addressR = SPIRAMOrganization.calculateSPIRamExportOffset(R_COLOR) + offset;
	addressG = SPIRAMOrganization.calculateSPIRamExportOffset(G_COLOR) + offset;
	addressB = SPIRAMOrganization.calculateSPIRamExportOffset(B_COLOR) + offset;
	
	/*
	Serial.println("WRITE SRAM ");
	Serial.print(addressR, DEC);
	Serial.print(" ");
	Serial.print(addressG, DEC);
	Serial.print(" ");
	Serial.println(addressB, DEC);
	*/

	for (unsigned int i = 0; i < width; i++)
	{
		colorRGB.r = importFile.read();
		colorRGB.g = importFile.read();
		colorRGB.b = importFile.read();

		/*
		Serial.print(colorRGB.r, DEC);
		Serial.print(" ");
		Serial.print(colorRGB.g, DEC);
		Serial.print(" ");
		Serial.print(colorRGB.b, DEC);
		Serial.print(" ");
		*/

		sRAM.writeByte(addressR + i, colorRGB.r);
		sRAM.writeByte(addressG + i, colorRGB.g);
		sRAM.writeByte(addressB + i, colorRGB.b);
		
		/*
		Serial.print(sRAM.readByte(addressR + i), DEC);
		Serial.print(" ");
		Serial.print(sRAM.readByte(addressG + i), DEC);
		Serial.print(" ");
		Serial.println(sRAM.readByte(addressB + i), DEC);
		*/
	}

	//fill line by multiply 16
	if (width != workWidth)
	{
		for (unsigned int i = width; i < workWidth; i++)
		{
			sRAM.writeByte(addressR + i, colorRGB.r);
			sRAM.writeByte(addressG + i, colorRGB.g);
			sRAM.writeByte(addressB + i, colorRGB.b);
		}
	}

}

unsigned char JPEG::DCValueToFile(int* inputLineArray, unsigned char color){

		
	ValidateData.validateData(inputLineArray, -1023, 1023);
	int prev = inputLineArray[0]; // backup

	unsigned int code, codeVal;
	unsigned char codeLen, codeValLen;

	//Write DC VALUE
	switch (color)
	{
	case JPEG_HUFFMAN_COLOR_Y :
		
		previsousDCvalue[0] = inputLineArray[0] - previsousDCvalue[0];

		inputLineArray[0] = previsousDCvalue[0];

		HuffmanCoding.codeToHuffman(0, previsousDCvalue[0], code, codeLen, codeVal, codeValLen, JPEG_HUFFMAN_DC, JPEG_HUFFMAN_COLOR_Y);

		
		previsousDCvalue[0] = prev;
		
		

		break;
	case JPEG_HUFFMAN_COLOR_CB:
		previsousDCvalue[1] = inputLineArray[0] - previsousDCvalue[1];

		inputLineArray[0] = previsousDCvalue[1];

		HuffmanCoding.codeToHuffman(0, previsousDCvalue[1], code, codeLen, codeVal, codeValLen, JPEG_HUFFMAN_DC, JPEG_HUFFMAN_COLOR_CB_CR);

		previsousDCvalue[1] = prev;

		break;

	case JPEG_HUFFMAN_COLOR_CR:

		previsousDCvalue[2] = inputLineArray[0] - previsousDCvalue[2];

		inputLineArray[0] = previsousDCvalue[2];

		HuffmanCoding.codeToHuffman(0, previsousDCvalue[2], code, codeLen, codeVal, codeValLen, JPEG_HUFFMAN_DC, JPEG_HUFFMAN_COLOR_CB_CR);

		previsousDCvalue[2] = prev;

		break;


	}

	//code
	bitWriteData.writeValue(code, codeLen);
	//value
	bitWriteData.writeValue(codeVal, codeValLen);

	

	return RETURN_CODE_OK;
}

unsigned char JPEG::ZigZagArrayToFile(int* inputLineArray, unsigned char color){
	
	
	unsigned int code, codeVal;
	unsigned char codeLen, codeValLen;
	unsigned char zeros = 0;

	/*
	//Write DC VALUE
	HuffmanCoding.codeToHuffman(0, inputLineArray[0], code, codeLen, codeVal, codeValLen, JPEG_HUFFMAN_DC, color);
	//code
	bitWriteData.writeValue(code, codeLen);
	//value
	bitWriteData.writeValue(codeVal, codeValLen);

	*/

	for (char i = 1; i < 64; i++)
	{
		if (lineArray64[i] == 0){
			zeros++;
		}
		else
		{
			
			if (zeros > 15){ // ZRL code
				HuffmanCoding.codeToHuffman(15, 0, code, codeLen, codeVal, codeValLen, JPEG_HUFFMAN_AC, color);
				zeros = zeros - 16; 
				bitWriteData.writeValue(code, codeLen);
			}

			HuffmanCoding.codeToHuffman(zeros, lineArray64[i], code, codeLen, codeVal, codeValLen, JPEG_HUFFMAN_AC, color);
			bitWriteData.writeValue(code, codeLen);
			bitWriteData.writeValue(codeVal, codeValLen);
			zeros = 0;
		}
	}

	//Write EOB if is write less then 64 values
	if(zeros > 0)
	{
		HuffmanCoding.codeToHuffman(0, 0, code, codeLen, codeVal, codeValLen, JPEG_HUFFMAN_AC, color);
		bitWriteData.writeValue(code, codeLen);
	}
	return RETURN_CODE_OK;
}

unsigned char JPEG::processDataInRAM(int workWidth){
	unsigned int mcu;
	unsigned int cycle = workWidth / 16;

	unsigned long addressR, addressG, addressB, offset;


	for (mcu = 0; mcu < cycle; mcu++) // do JPEG operation with SRAM data 
	{

		for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){ // lines
			offset = i * workWidth; // line offset
			offset += 2 * mcu *JPEG_MCU_LENGTH; // row offset

			addressR = SPIRAMOrganization.calculateSPIRamExportOffset(R_COLOR) + offset;
			addressG = SPIRAMOrganization.calculateSPIRamExportOffset(G_COLOR) + offset;
			addressB = SPIRAMOrganization.calculateSPIRamExportOffset(B_COLOR) + offset;

			/*
			Serial.println("ARRAY ADR ");
			Serial.print(addressR, DEC);
			Serial.print(" ");
			Serial.print(addressG, DEC);
			Serial.print(" ");
			Serial.println(addressB, DEC);
			*/

			for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++) // rows
			{
				//Serial.print(intArrayCr[i][j], DEC);
				//Serial.print(" ");
				//Serial.print(address + j);
				intArray[i][j] = sRAM.readByte(addressR + j);
				intArray1[i][j] = sRAM.readByte(addressG + j);
				intArray2[i][j] = sRAM.readByte(addressB + j);

			}



		}

		/*
		Serial.println("RED");
		printMatrix((int *)intArray);
		Serial.println("GREEN");
		printMatrix((int *)intArray1);
		Serial.println("BLUE");
		printMatrix((int *)intArray2);

		*/

		//trasnform rgb to ycbcr and copy y to aditional block
		transformColorToYCbCr((int *)intArray, (int *)intArray1, (int *)intArray2, (int *)intArrayY0, (int *)intArray1, (int *)intArray2);
		//downsample cb and cr

		downSampleMatrix((int *)intArray1, (int *)intArrayCb, 0);
		downSampleMatrix((int *)intArray2, (int *)intArrayCr, 0);

		/*
		Serial.println("Y0");
		printMatrix((int *)intArrayY0);
		Serial.println("Cb0");
		printMatrix((int *)intArrayCb);
		Serial.println("Cr0");
		printMatrix((int *)intArrayCr);
		*/

		for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){ // lines
			offset = i * workWidth; // line offset
			offset += (2 * mcu + 1) *JPEG_MCU_LENGTH; // row offset

			addressR = SPIRAMOrganization.calculateSPIRamExportOffset(R_COLOR) + offset;
			addressG = SPIRAMOrganization.calculateSPIRamExportOffset(G_COLOR) + offset;
			addressB = SPIRAMOrganization.calculateSPIRamExportOffset(B_COLOR) + offset;
			/*
			Serial.println("ARRAY ADR ");
			Serial.print(addressR, DEC);
			Serial.print(" ");
			Serial.print(addressG, DEC);
			Serial.print(" ");
			Serial.println(addressB, DEC);
			*/

			for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++) // rows
			{
				//Serial.print(intArrayCr[i][j], DEC);
				//Serial.print(" ");
				//Serial.print(address + j);
				intArray[i][j] = sRAM.readByte(addressR + j);
				intArray1[i][j] = sRAM.readByte(addressG + j);
				intArray2[i][j] = sRAM.readByte(addressB + j);

				//Serial.print(" ");
			}



		}



		//trasnform rgb to ycbcr and copy y to aditional block
		transformColorToYCbCr((int *)intArray, (int *)intArray1, (int *)intArray2, (int *)intArrayY1, (int *)intArray1, (int *)intArray2);
		//downsample cb and cr

		downSampleMatrix((int *)intArray1, (int *)intArrayCb, 1);
		downSampleMatrix((int *)intArray2, (int *)intArrayCr, 1);

		/*
		Serial.println("Y1");
		printMatrix((int *)intArrayY1);
		Serial.println("Cb0");
		printMatrix((int *)intArrayCb);
		Serial.println("Cr0");
		printMatrix((int *)intArrayCr);
		*/

		for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){ // lines
			offset = (i + JPEG_MCU_LENGTH)* workWidth; // line offset
			offset += 2 * mcu *JPEG_MCU_LENGTH; // row offset

			addressR = SPIRAMOrganization.calculateSPIRamExportOffset(R_COLOR) + offset;
			addressG = SPIRAMOrganization.calculateSPIRamExportOffset(G_COLOR) + offset;
			addressB = SPIRAMOrganization.calculateSPIRamExportOffset(B_COLOR) + offset;

			/*
			Serial.println("ARRAY ADR ");
			Serial.print(addressR, DEC);
			Serial.print(" ");
			Serial.print(addressG, DEC);
			Serial.print(" ");
			Serial.println(addressB, DEC);
			*/

			for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++) // rows
			{
				//Serial.print(intArrayCr[i][j], DEC);
				//Serial.print(" ");
				//Serial.print(address + j);
				intArray[i][j] = sRAM.readByte(addressR + j);
				intArray1[i][j] = sRAM.readByte(addressG + j);
				intArray2[i][j] = sRAM.readByte(addressB + j);

				//Serial.print(" ");
			}



		}

		//trasnform rgb to ycbcr and copy y to aditional block
		transformColorToYCbCr((int *)intArray, (int *)intArray1, (int *)intArray2, (int *)intArrayY2, (int *)intArray1, (int *)intArray2);
		//downsample cb and cr

		downSampleMatrix((int *)intArray1, (int *)intArrayCb, 2);
		downSampleMatrix((int *)intArray2, (int *)intArrayCr, 2);

		/*
		Serial.println("Y2");
		printMatrix((int *)intArrayY2);
		Serial.println("Cb0");
		printMatrix((int *)intArrayCb);
		Serial.println("Cr0");
		printMatrix((int *)intArrayCr);
		*/

		for (unsigned char i = 0; i < JPEG_MCU_LENGTH; i++){ // lines
			offset = (i + JPEG_MCU_LENGTH) * workWidth; // line offset
			offset += (2 * mcu + 1) *JPEG_MCU_LENGTH; // row offset

			addressR = SPIRAMOrganization.calculateSPIRamExportOffset(R_COLOR) + offset;
			addressG = SPIRAMOrganization.calculateSPIRamExportOffset(G_COLOR) + offset;
			addressB = SPIRAMOrganization.calculateSPIRamExportOffset(B_COLOR) + offset;

			/*
			Serial.println("ARRAY ADR ");
			Serial.print(addressR, DEC);
			Serial.print(" ");
			Serial.print(addressG, DEC);
			Serial.print(" ");
			Serial.println(addressB, DEC);
			*/

			for (unsigned char j = 0; j < JPEG_MCU_LENGTH; j++) // rows
			{
				//Serial.print(intArrayCr[i][j], DEC);
				//Serial.print(" ");
				//Serial.print(address + j);
				intArray[i][j] = sRAM.readByte(addressR + j);
				intArray1[i][j] = sRAM.readByte(addressG + j);
				intArray2[i][j] = sRAM.readByte(addressB + j);

				//Serial.print(" ");
			}



		}

		//trasnform rgb to ycbcr and copy y to aditional block
		transformColorToYCbCr((int *)intArray, (int *)intArray1, (int *)intArray2, (int *)intArrayY3, (int *)intArray1, (int *)intArray2);
		//downsample cb and cr

		downSampleMatrix((int *)intArray1, (int *)intArrayCb, 3);
		downSampleMatrix((int *)intArray2, (int *)intArrayCr, 3);

		//Serial.print("BLCK ");
		//Serial.println(mcu,DEC);

		/*
		Serial.println("Y3");
		printMatrix((int *)intArrayY3);
		Serial.println("Cb0");
		printMatrix((int *)intArrayCb);
		Serial.println("Cr0");
		printMatrix((int *)intArrayCr);
		*/
		//printMatrix((int *)intArrayCb);


		// DCT OPERATION
		DCT.doFDCT((int *)intArrayY0, (int *)intArray);
		//Serial.println("Y0");
		//printMatrix((int *)intArray);
		Quantization.quantization((int *)intArray, (int *)intArrayY0, (unsigned char *)quantizitonTableY);
		

		DCT.doFDCT((int *)intArrayY1, (int *)intArray);
		//Serial.println("Y1");
		//printMatrix((int *)intArray);
		Quantization.quantization((int *)intArray, (int *)intArrayY1, (unsigned char *)quantizitonTableY);

		DCT.doFDCT((int *)intArrayY2, (int *)intArray);
		//Serial.println("Y2");
		//printMatrix((int *)intArray);
		Quantization.quantization((int *)intArray, (int *)intArrayY2, (unsigned char *)quantizitonTableY);

		DCT.doFDCT((int *)intArrayY3, (int *)intArray);
		//Serial.println("Y3");
		//printMatrix((int *)intArray);
		Quantization.quantization((int *)intArray, (int *)intArrayY3, (unsigned char *)quantizitonTableY);

		DCT.doFDCT((int *)intArrayCb, (int *)intArray);
		//Serial.println("Cb");
		//printMatrix((int *)intArray);
		Quantization.quantization((int *)intArray, (int *)intArrayCb, (unsigned char *)quantizitonTableCbCr);

		DCT.doFDCT((int *)intArrayCr, (int *)intArray);
		//Serial.println("Cr");
		//printMatrix((int *)intArray);
		Quantization.quantization((int *)intArray, (int *)intArrayCr, (unsigned char *)quantizitonTableCbCr);

		/*
		printMatrix((int *)intArrayY0);
		printMatrix((int *)intArrayY1);
		printMatrix((int *)intArrayY2);
		printMatrix((int *)intArrayY3);

		printMatrix((int *)intArrayCb);
		printMatrix((int *)intArrayCr);
		*/

		ZigZag.doZigZag((int *)intArrayY0, (int *)lineArray64);
		DCValueToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_Y);
		ZigZagArrayToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_Y);
		//TEST
		/*
		for (char i = 0; i < 64; i++)
		{
			Serial.print(lineArray64[i], DEC);
			Serial.print(" ");
		}
		Serial.println(" ");
		*/
		//END TEST

		ZigZag.doZigZag((int *)intArrayY1, (int *)lineArray64);
		DCValueToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_Y);
		ZigZagArrayToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_Y);
		//TEST
		/*
		for (char i = 0; i < 64; i++)
		{
			Serial.print(lineArray64[i], DEC);
			Serial.print(" ");
		}
		Serial.println(" ");
		*/
		//END TEST


		ZigZag.doZigZag((int *)intArrayY2, (int *)lineArray64);
		DCValueToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_Y);
		ZigZagArrayToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_Y);
		//TEST
		/*
		for (char i = 0; i < 64; i++)
		{
			Serial.print(lineArray64[i], DEC);
			Serial.print(" ");
		}
		Serial.println(" ");
		*/
		//END TEST

		ZigZag.doZigZag((int *)intArrayY3, (int *)lineArray64);
		DCValueToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_Y);
		ZigZagArrayToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_Y);
		//TEST
		/*
		for (char i = 0; i < 64; i++)
		{
			Serial.print(lineArray64[i], DEC);
			Serial.print(" ");
		}
		Serial.println(" ");
		*/
		//END TEST


		ZigZag.doZigZag((int *)intArrayCb, (int *)lineArray64);
		DCValueToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_CB);
		ZigZagArrayToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_CB_CR);
		//TEST
		/*
		for (char i = 0; i < 64; i++)
		{
			Serial.print(lineArray64[i], DEC);
			Serial.print(" ");
		}
		Serial.println(" ");
		*/
		//END TEST

		ZigZag.doZigZag((int *)intArrayCr, (int *)lineArray64);
		DCValueToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_CR);
		ZigZagArrayToFile((int *)lineArray64, JPEG_HUFFMAN_COLOR_CB_CR);
		//TEST
		/*
		for (char i = 0; i < 64; i++)
		{
			Serial.print(lineArray64[i], DEC);
			Serial.print(" ");
		}
		Serial.println(" ");
		*/
		//END TEST
	}
}

void JPEG::printMatrix(int *inputData){
	for (unsigned char i = 0; i < 8; i++)
	{
		for (unsigned char j = 0; j < 8; j++)
		{
			Serial.print((int)(*((inputData + i * 8) + j)));
			Serial.print(" ");
		}
		Serial.println("");
	}

}