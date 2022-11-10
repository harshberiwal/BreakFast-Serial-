/*
 * Implementing a SerialBreakfast on the terminal that allows the user to interact with
 * the FRDM board in real-time. Check the hex values at any address, plus info about the
 * build.
 *
 * main.c - application entry point
 * 
 * Author: Howdy Pierce, howdy.pierce@colorado.edu
 * 		   Harsh Beriwal, harsh.beriwal@colorado.edu
 * Modified by: Harsh Beriwal
 *
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 * No leveraged code in this file.
 */

#include "sysclock.h"
#include "uart.h"
#include "string.h"
#include "hexdump.h"
#include "command_processor.h"
#include "test_cbfifo.h"

#define BAUD_RATE 38400

int main(void)
{
	char *input_str;
	sysclock_init();
	Init_UART0(BAUD_RATE);
#ifdef DEBUG
	int success = test_cbfifo();
	if(!success)
	printf("\n\rCircular buffer Tests Failed\n\r");
#endif
	printf("\n\rWelcome to BreakfastSerial!\n\r");
	while (1) {
	  printf("? ");
	  input_str = accumulate_line();
	  process_command(input_str);
	}
	return 0;
}
