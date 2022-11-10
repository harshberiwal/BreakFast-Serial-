/*
 * uart.h includes the declaration to initialize the Serial Terminal
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 * THE UART_init was heavily taken from Alexander Dean Code as given below in his Github.
 *
 * https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/UART.c
 *
 */
#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <MKL25Z4.H>
#include "cbfifo.h"

/*
 * Initializes the SERIAL UART with the given BAUD RATE.
 *
 * Parameter:
 *  Baud rate desired.
 *
 *  Returns:
 *   None.
 */
void Init_UART0(uint32_t baud_rate);


#endif

