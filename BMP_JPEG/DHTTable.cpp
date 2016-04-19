// 
// 
// 

#include "DHTTable.h"

void DHTTable::printDHT()
{
	Serial.println("DHT INFO");
	Serial.print("Length: ");
	Serial.print(DHT_Length);
	Serial.print("\nTable number: ");
	Serial.print(DHT_Number, DEC);
	Serial.print("\nType: ");
	Serial.println(DHT_Type, DEC);
	unsigned char i;
	unsigned long address;
	for (i = 0; i < DHT_CODE_MAX_LENGTH; i++)
	{
		Serial.print("Length ");
		Serial.print(i + 1);
		Serial.print(" : ");
		Serial.print(DHT_CodesCount[i], DEC);
		Serial.print(" Offset ");
		Serial.println(DHT_CodesOffset[i]);
	}
}





