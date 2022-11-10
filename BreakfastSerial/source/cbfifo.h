/*
 * cbfifo.h includes the declarations of all the functions for implementing
 * Circular buffer Queue
 *
 * Author: Harsh Beriwal & Howdy Pierce.
 * Edited by: Harsh Beriwal
 * 
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 */

#ifndef _CBFIFO_H_
#define _CBFIFO_H_

#include <stdlib.h>  // for size_t
#include <stdio.h>
#include <stddef.h>
#include <MKL25Z4.H>

#define SIZE 256

typedef struct {
	unsigned int head;
	unsigned int tail;
	unsigned int length;
	char queue[SIZE];
}volatile cbfifo_s;


/*
 * Initializes all the values in the cbfifo to 0
 *
 * Parameters:
 *   buf      current buffer
 *
 * Returns:
 *  None
 */
void cbfifo_init(cbfifo_s * buf);

/*
 * Checks if the circular buffer is empty or not.
 *
 * Parameters:
 *   buf      current buffer
 *
 * Returns:
 *   1 if full otherwise 0.
 *
 */
int cbfifo_empty(cbfifo_s * buf);


/*
 * Checks if the circular buffer is full or not.
 *
 * Parameters:
 *   buf      current buffer
 *
 * Returns:
 *   1 if full otherwise 0.
 *
 */
int cbfifo_full(cbfifo_s * buf);

/*
 * Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * Parameters:
 *   buf      Current Buffer to enqueue in
 *   nbyte    Byte to Enqueue
 * 
 * Returns:
 *  If enqueued passes 1, otherwise returns 0.
 */
int cbfifo_enqueue(char nbyte, cbfifo_s* buf);


/*
 * Attempts to remove ("dequeue") a byte of data from the
 * FIFO. Removed data will be returned
 *
 * Parameters:
 *   buf      Destination for the current buffer
 * 
 * Returns:
 *   The byte that is dequeued
 * 
 */
int cbfifo_dequeue(cbfifo_s *buf);


/*
 * Returns the number of bytes currently on the FIFO. 
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length(cbfifo_s * buf);


#endif // _CBFIFO_H_
