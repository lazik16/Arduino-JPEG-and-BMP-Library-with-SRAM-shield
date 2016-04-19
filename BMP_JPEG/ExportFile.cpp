// 
// 
// 

#include "ExportFile.h"

File ExportFileClass::createFileWithHeaderInfo(char* imageName ,unsigned int imageWidth, unsigned int imageHeight, unsigned char colorFormat)
{
	File exportFile;
	if (!SD.exists(EXPORT_FOLDER)){
		//Serial.println(SD.mkdir(EXPORT_FOLDER));
	}
	else{
		Serial.println("Folder exist");
	}

	char path[PATH_MAX_LENGTH] = EXPORT_PATH;
	strcat(path, imageName);

	unsigned char length = strlen(path);
	path[length - 3] = '\0';

	strcat(path, EXPORT_FILE_ENDING);

	Serial.println(path);

	
	exportFile = SD.open(path, FILE_WRITE);
	if (exportFile){
		Serial.println("File created");
		exportFile.seek(0);
		/*
		Serial.println(exportFile.position(), DEC);
		Serial.println(imageWidth >> 8, DEC);
		Serial.println((unsigned char)imageWidth, DEC);
		*/

		exportFile.write(imageWidth >> 8);
		exportFile.write((unsigned char)imageWidth);

		exportFile.write(imageHeight >> 8);
		exportFile.write((unsigned char)imageHeight);

		exportFile.write(colorFormat);

	}
	else{
		Serial.println("File not created");
	}
	

	return exportFile;
}

File ExportFileClass::createFileForJPEG(char* imageName)
{
	File exportFile;
	if (!SD.exists(EXPORT_FOLDER)){
		Serial.println(SD.mkdir(EXPORT_FOLDER));
	}
	else{
		Serial.println("Folder exist");
	}

	
	char path[PATH_MAX_LENGTH] = "";
	strcat(path, imageName);
	

	unsigned char length = strlen(path);
	path[length - 3] = '\0';

	strcat(path, JPEG_EXPORT_FILE_ENDING);

	Serial.println(path);


	exportFile = SD.open(path, FILE_WRITE);
	if (exportFile){
		Serial.println("File JPEG created");
		exportFile.seek(0);
	}
	else{
		Serial.println("File JPEG not created");
	}


	return exportFile;
}

File ExportFileClass::createFileForBMP(char* imageName)
{
	File exportFile;
	if (!SD.exists(EXPORT_FOLDER)){
		Serial.println(SD.mkdir(EXPORT_FOLDER));
	}
	else{
		Serial.println("Folder exist");
	}


	char path[PATH_MAX_LENGTH] = "";
	strcat(path, imageName);


	unsigned char length = strlen(path);
	path[length - 3] = '\0';

	strcat(path, BMP_EXPORT_FILE_ENDING);

	Serial.println(path);


	exportFile = SD.open(path, FILE_WRITE);
	if (exportFile){
		Serial.println("File BMP created");
		exportFile.seek(0);
	}
	else{
		Serial.println("File BMP not created");
	}


	return exportFile;
}


ExportFileClass ExportFile;

