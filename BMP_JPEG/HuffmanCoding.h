// HuffmanCoding.h

#ifndef _HUFFMANCODING_h
#define _HUFFMANCODING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "JPEG_Macros.h"

class HuffmanCodingClass
{
private:
	/*
	unsigned int dcLuminance[12] = {
		0b0000000000000000, 0b0000000000000010, 0b0000000000000011, 0b0000000000000100, 0b0000000000000101, 0b0000000000000110, 0b0000000000001110, 0b0000000000011110, 0b0000000000111110, 0b0000000001111110,
		0b0000000011111110, 0b0000000111111110
	};

	unsigned int dcChrominance[12] = {
		0b0000000000000000, 0b0000000000000001, 0b0000000000000010, 0b0000000000000110, 0b0000000000001110, 0b0000000000011110, 0b0000000000111110, 0b0000000001111110, 0b0000000011111110, 0b0000000111111110,
		0b0000001111111110, 0b0000011111111110
	};

	unsigned int acLuminance[16][10] = {
			{ 0b0000000000000000, 0b0000000000000001, 0b0000000000000100, 0b0000000000001011, 0b0000000000011010, 0b0000000001111000, 0b0000000011111000, 0b0000001111110110, 0b1111111110000010, 0b1111111110000011 },
			{ 0b0000000000001100, 0b0000000000011011, 0b0000000001111001, 0b0000000111110110, 0b0000011111110110, 0b1111111110000100, 0b1111111110000101, 0b1111111110000110, 0b1111111110000111, 0b1111111110001000 },
			{ 0b0000000000011100, 0b0000000011111001, 0b0000001111110111, 0b0000111111110100, 0b1111111110001001, 0b1111111110001010, 0b1111111110001011, 0b1111111110001100, 0b1111111110001101, 0b1111111110001110 },
			{ 0b0000000000111010, 0b0000000111110111, 0b0000111111110101, 0b1111111110001111, 0b1111111110010000, 0b1111111110010001, 0b1111111110010010, 0b1111111110010011, 0b1111111110010100, 0b1111111110010101 },
			{ 0b0000000000111011, 0b0000001111111000, 0b1111111110010110, 0b1111111110010111, 0b1111111110011000, 0b1111111110011001, 0b1111111110011010, 0b1111111110011011, 0b1111111110011100, 0b1111111110011101 },
			{ 0b0000000001111010, 0b0000011111110111, 0b1111111110011110, 0b1111111110011111, 0b1111111110100000, 0b1111111110100001, 0b1111111110100010, 0b1111111110100011, 0b1111111110100100, 0b1111111110100101 },
			{ 0b0000000001111011, 0b0000111111110110, 0b1111111110100110, 0b1111111110100111, 0b1111111110101000, 0b1111111110101001, 0b1111111110101010, 0b1111111110101011, 0b1111111110101100, 0b1111111110101101 },
			{ 0b0000000011111010, 0b0000111111110111, 0b1111111110101110, 0b1111111110101111, 0b1111111110110000, 0b1111111110110001, 0b1111111110110010, 0b1111111110110011, 0b1111111110110100, 0b1111111110110101 },
			{ 0b0000000111111000, 0b0001111111100000, 0b1111111110110110, 0b1111111110110111, 0b1111111110111000, 0b1111111110111001, 0b1111111110111010, 0b1111111110111011, 0b1111111110111100, 0b1111111110111101 },
			{ 0b0000000111111001, 0b1111111110111110, 0b1111111110111111, 0b1111111111000000, 0b1111111111000001, 0b1111111111000010, 0b1111111111000011, 0b1111111111000100, 0b1111111111000101, 0b1111111111000110 },
			{ 0b0000000111111010, 0b1111111111000111, 0b1111111111001000, 0b1111111111001001, 0b1111111111001010, 0b1111111111001011, 0b1111111111001100, 0b1111111111001101, 0b1111111111001110, 0b1111111111001111 },
			{ 0b0000001111111001, 0b1111111111010000, 0b1111111111010001, 0b1111111111010010, 0b1111111111010011, 0b1111111111010100, 0b1111111111010101, 0b1111111111010110, 0b1111111111010111, 0b1111111111011000 },
			{ 0b0000001111111010, 0b1111111111011001, 0b1111111111011010, 0b1111111111011011, 0b1111111111011100, 0b1111111111011101, 0b1111111111011110, 0b1111111111011111, 0b1111111111100000, 0b1111111111100001 },
			{ 0b0000011111111000, 0b1111111111100010, 0b1111111111100011, 0b1111111111100100, 0b1111111111100101, 0b1111111111100110, 0b1111111111100111, 0b1111111111101000, 0b1111111111101001, 0b1111111111101010 },
			{ 0b1111111111101011, 0b1111111111101100, 0b1111111111101101, 0b1111111111101110, 0b1111111111101111, 0b1111111111110000, 0b1111111111110001, 0b1111111111110010, 0b1111111111110011, 0b1111111111110100 },
			{ 0b1111111111110101, 0b1111111111110110, 0b1111111111110111, 0b1111111111111000, 0b1111111111111001, 0b1111111111111010, 0b1111111111111011, 0b1111111111111100, 0b1111111111111101, 0b1111111111111110 } };

	unsigned int acChrominance[16][10] = {
			{ 0b0000000000000001, 0b0000000000000100, 0b0000000000001010, 0b0000000000011000, 0b0000000000011001, 0b0000000000111000, 0b0000000000111100, 0b0000000111110100, 0b0000001111110110, 0b0000111111110100 },
			{ 0b0000000000001011, 0b0000000000111001, 0b0000000011110110, 0b0000000111110101, 0b0000011111110110, 0b0000111111110101, 0b1111111110001000, 0b1111111110001001, 0b1111111110001010, 0b1111111110001011 },
			{ 0b0000000000011010, 0b0000000011110111, 0b0000001111110111, 0b0000111111110110, 0b0111111111000010, 0b1111111110001100, 0b1111111110001101, 0b1111111110001110, 0b1111111110001111, 0b1111111110010000 },
			{ 0b0000000000011011, 0b0000000011111000, 0b0000001111111000, 0b0000111111110111, 0b1111111110010001, 0b1111111110010010, 0b1111111110010011, 0b1111111110010100, 0b1111111110010101, 0b1111111110010110 },
			{ 0b0000000000111010, 0b0000000111110110, 0b1111111110010111, 0b1111111110011000, 0b1111111110011001, 0b1111111110011010, 0b1111111110011011, 0b1111111110011100, 0b1111111110011101, 0b1111111110011110 },
			{ 0b0000000000111011, 0b0000001111111001, 0b1111111110011111, 0b1111111110100000, 0b1111111110100001, 0b1111111110100010, 0b1111111110100011, 0b1111111110100100, 0b1111111110100101, 0b1111111110100110 },
			{ 0b0000000001111001, 0b0000011111110111, 0b1111111110100111, 0b1111111110101000, 0b1111111110101001, 0b1111111110101010, 0b1111111110101011, 0b1111111110101100, 0b1111111110101101, 0b1111111110101110 },
			{ 0b0000000001111010, 0b0000011111111000, 0b1111111110101111, 0b1111111110110000, 0b1111111110110001, 0b1111111110110010, 0b1111111110110011, 0b1111111110110100, 0b1111111110110101, 0b1111111110110110 },
			{ 0b0000000011111001, 0b1111111110110111, 0b1111111110111000, 0b1111111110111001, 0b1111111110111010, 0b1111111110111011, 0b1111111110111100, 0b1111111110111101, 0b1111111110111110, 0b1111111110111111 },
			{ 0b0000000111110111, 0b1111111111000000, 0b1111111111000001, 0b1111111111000010, 0b1111111111000011, 0b1111111111000100, 0b1111111111000101, 0b1111111111000110, 0b1111111111000111, 0b1111111111001000 },
			{ 0b0000000111111000, 0b1111111111001001, 0b1111111111001011, 0b1111111111001011, 0b1111111111001100, 0b1111111111001101, 0b1111111111001110, 0b1111111111001111, 0b1111111111010000, 0b1111111111010001 },
			{ 0b0000000111111001, 0b1111111111010010, 0b1111111111010011, 0b1111111111010100, 0b1111111111010101, 0b1111111111010110, 0b1111111111010111, 0b1111111111011000, 0b1111111111011001, 0b1111111111011010 },
			{ 0b0000000111111010, 0b1111111111011011, 0b1111111111011100, 0b1111111111011101, 0b1111111111011110, 0b1111111111011111, 0b1111111111100000, 0b1111111111100001, 0b1111111111100010, 0b1111111111100011 },
			{ 0b0000011111111001, 0b1111111111100100, 0b1111111111100101, 0b1111111111100110, 0b1111111111100111, 0b1111111111101000, 0b1111111111101001, 0b1111111111101010, 0b1111111111101011, 0b1111111111101100 },
			{ 0b0011111111100000, 0b1111111111101101, 0b1111111111101110, 0b1111111111101111, 0b1111111111110000, 0b1111111111110001, 0b1111111111110010, 0b1111111111110011, 0b1111111111110100, 0b1111111111110101 },
			{ 0b0111111111000011, 0b1111111111110110, 0b1111111111110111, 0b1111111111111000, 0b1111111111111001, 0b1111111111111010, 0b1111111111111011, 0b1111111111111100, 0b1111111111111101, 0b1111111111111110 } };

	*/
public:
	//To JPEG
	static unsigned int codeToHuffman(unsigned char zeros, signed int value, unsigned int &returnCode, unsigned char &returnCodeLength,
		unsigned int &returnCodeforValue, unsigned char &returnCodeforValueLength,
		unsigned char type, unsigned char color); // type DC/AC color Luma/Chroma
	static unsigned int codeForValue(signed int value, unsigned char &retLength);
	static unsigned int powBy2(unsigned char exponent);
	static unsigned char lengthOfCode(unsigned int code, unsigned char type, unsigned char color);
	static unsigned char standardCodeLength(unsigned int code);
	static signed int validateValue(signed int value, unsigned char type);
	
	//from JPEG
	static int decodeFromHuffman(unsigned int value, unsigned char length);
	static unsigned char getLengthOfValue(int value);	
};

extern HuffmanCodingClass HuffmanCoding;

#endif
