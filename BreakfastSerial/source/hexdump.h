/*
 * hexdump.c includes the declaration of the hexdump function
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 * No leveraged code in this file.
 */

#ifndef HEXDUMP_H_
#define HEXDUMP_H_

#include "uart.h"


/*
 * Prints the HexDump for a valid start addrress and length
 *
 * Parameters:
 *   start address - The start address to print from
 *   length - The number of bytes to print in hex
 *
 * Returns:
 *  None
 */
void hexdump(char *start_add, int length);

#endif /* HEXDUMP_H_ */
