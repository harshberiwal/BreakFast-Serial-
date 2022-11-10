/*
 * cbfifo.c includes the Production code with all the functions for implementing
 * Circular buffer Queue
 * The details of each function is given in the respective cbfifo.h file.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 * No leveraged code or files
 */

#include "cbfifo.h"
#include <stdio.h>
#include <stdint.h>

#define DIVIDE_BY_SIZE (SIZE-1)
#define OUT_OF_RANGE -1
#define ZERO 0
#define INCREMENT(x) ((x)+1)
#define ERROR -1

void cbfifo_init(cbfifo_s * buf)
{
	//*******************INITIALIZING ALL ELEMENTS OF FIFO TO 0********************
	for (int i=0; i<SIZE; i++)
		buf->queue[i] = '_';
	buf->head =0;
	buf->tail =0;
	buf->length =0;
}

int cbfifo_enqueue(char nbyte, cbfifo_s* buf)
{
	uint32_t masking_state;
	if(buf ==NULL)
		return 0;
	//***********************IF FIFO IS FULL DON"T ENQUEUE************************
	else if(cbfifo_full(buf))
		return 0;
	//**********************IF THERE IS SPACE, JUST ENQUEUE***********************
	else {
		buf->queue[buf->tail] = nbyte;
		masking_state = __get_PRIMASK();

		//**********DISABLIBNG INTERRUPT AS IT IS CALLED BY INT. HANDLER**********
		__disable_irq();
		buf->tail = (INCREMENT(buf->tail))&DIVIDE_BY_SIZE;
		buf->length++;
		__set_PRIMASK(masking_state);
		return 1;
	}
}

int cbfifo_dequeue(cbfifo_s *buf)
{
	uint32_t masking_state;
	uint8_t dequeued_byte =0;
	if(buf == NULL)
		return 0;
	//***********************IF FIFO IS EMPTY CAN'T ENQUEUE***********************
	else if(!cbfifo_empty(buf))
	{
		dequeued_byte = buf->queue[buf->head];
		masking_state = __get_PRIMASK();
		//**********DISABLIBNG INTERRUPT AS IT IS CALLED BY INT. HANDLER**********
		__disable_irq();
		buf->head = INCREMENT(buf->head)&DIVIDE_BY_SIZE;
		buf ->length--;
		__set_PRIMASK(masking_state);
	}
	return dequeued_byte;
}

size_t cbfifo_length(cbfifo_s * buf)
{
	 return buf->length;
}

int cbfifo_full(cbfifo_s * buf)
{
	return buf->length == SIZE;
}

int cbfifo_empty(cbfifo_s * buf)
{
	return buf->length == 0;
}







