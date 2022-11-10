/*
 * hexdump.c includes the Production code to print the hexdump of the data in the address
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 * No leveraged code in this file.
 *
 */

#include "hexdump.h"

#define DIVIDE_BY_16 	15
#define MSB_TWO_BYTE(x) (((x)>>16)&0xFFFF)		//Returns the Most significant 16 bits
#define LSB_TWO_BYTE(x) ((x)&0xFFFF)			//Returns the least significant 16 bits

void hexdump(char *start_add, int length)
{
	int start=0;
	char *end_address = 0;
	printf("\n\r");
	start = (int)start_add;						//copies the pointer add into an integer
	printf("%04X_%04X", MSB_TWO_BYTE(start), LSB_TWO_BYTE(start));
	//******************PRINTS HEXDUMP UNTIL THE REQUIRED LENGTH**********************
	for(int byte =0; byte<(length);byte++)
	{
		if(!(byte&DIVIDE_BY_16) && byte!=0){	//printing only 16 chars in one line
			printf("\n\r");
			end_address = start_add+byte;
			start = (int)end_address;
			printf("%04X_%04X", MSB_TWO_BYTE(start), LSB_TWO_BYTE(start));
		}
		printf(" %02X", *(start_add+byte));		//Actual Hex implementation of the value
	}
	printf("\n\r");
}
