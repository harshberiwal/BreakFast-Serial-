/*
 * test_cbfifo.c includes all the functions used in test_cbfifo(). The details of each function
 * is given in test_cbfifo.h
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 * The below line was taken from the Internet - https://blog.hubspot.com/sales/famous-quotes
 *
 * "If you look at what you have in life, "
	"you'll always have more. If you look at what "
	"you don't have in life, you'll never have enough. "
	"-Oprah Winfrey";
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "test_cbfifo.h"
#include "cbfifo.h"

cbfifo_s Q1;

static int total_checks = 0;
static int test_failed = 0;
static int checks_passed =0;

char test_arr[128];

void test_cbfifo_compare_length(int val_1, int val_2)
{
	if(!test_failed){
		if(val_1 == val_2){
			checks_passed++;
		}
		else{
			test_failed =ONE;
		}
	}
}

void test_cbfifo_compare_capacity(int val_1, int val_2)
{
	if(!test_failed){
		if(val_1 == val_2){
			checks_passed++;
		}
		else{
			test_failed =ONE;
		}
	}
}

void test_cbfifo_compare_return(int val_1, int val_2)
{
	if(!test_failed){
		if(val_1 == val_2){
			checks_passed++;
		}
		else{
			test_failed =ONE;
		}
	}
}

void test_cbfifo_dequeued(int val1, int val2)
{
	if(!test_failed){
		if(val1 == val2){
			checks_passed++;
		}
		else{
			test_failed =ONE;
		}
	}
}

void test_dequeued_elements(int val1, int val2)
{
	if(!test_failed){
		if(val1 ==val2){
			checks_passed++;
		}
		else{
			test_failed =ONE;
		}
	}
}

int test_cbfifo()
{
	char str[]= "If you look at what you have in life, "
				"you'll always have more. If you look at what "
				"you don't have in life, you'll never have enough. "
				"-Oprah Winfrey "
				"If you set your goals ridiculously high and it's a failure, "
				"you will fail above everyone else's success. -James Cameron";

	//*******************CHECKING AFTER ENQUEUING 10 Bytes*********************
	for(int i=0; i<10;i++)
		test_cbfifo_compare_return(cbfifo_enqueue(str[i], &Q1), 1);
	total_checks++;
	CHECK;

	//***************CHECKING IF THE BYTES ARE ENQUEUED PROPERLY***************
	test_cbfifo_compare_length(cbfifo_length(&Q1),10);
	total_checks++;
	CHECK;

	//******************CHECKING BYTES ARE DEQUEUED PROPERLY*******************
	for(int i=0;i<10; i++)
	{
		test_cbfifo_dequeued(cbfifo_dequeue(&Q1), str[i]);
		test_cbfifo_compare_length(cbfifo_length(&Q1), 9-i);
		total_checks++;
	}
	CHECK;

	//*******************ENQUEUING UNTIL THE BUFFER IS FULL********************
	for(int i=0;i<SIZE; i++)
	{
		test_cbfifo_compare_return(cbfifo_enqueue(str[i], &Q1), 1);
		test_cbfifo_compare_length(cbfifo_length(&Q1), i+1);
		total_checks++;
	}
	CHECK;

	//****************ENQUEUING MORE WHEN THE BUFFER IF FULL********************
	test_cbfifo_compare_return(cbfifo_enqueue(str[0], &Q1), 0);
	test_cbfifo_compare_length(cbfifo_length(&Q1), SIZE);
	CHECK;

	//******************DEQUEUING ALL AND CHECKING THE BYTES********************
	for(int i=0;i<SIZE; i++)
	{
		test_cbfifo_dequeued(cbfifo_dequeue(&Q1), str[i]);
		test_cbfifo_compare_length(cbfifo_length(&Q1),SIZE-i-1);
		total_checks++;
	}
	CHECK;

	//*******************MAKING SURE IF THE LENGTH IS NULL**********************
	test_cbfifo_compare_length(cbfifo_length(&Q1), 0);
	total_checks++;
	CHECK;

	//*********************DEQUEUING WHEN THE BUFFER IS EMPTY*******************
	test_cbfifo_dequeued(cbfifo_dequeue(&Q1), 0);
	total_checks++;
	CHECK;

	printf("\n\rTotal Tests Passed for CBFIFO: %d/%d",total_checks,total_checks);
	printf("\n\rAll Tests cases passed for CBFIFO.C\n\r");
	return 1;
}






