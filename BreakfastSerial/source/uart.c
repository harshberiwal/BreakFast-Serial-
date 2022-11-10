/*
 * uart.c includes the Production code to initialize the Serial Terminal.
 * It also includes the IRQ handler for UART and a stronger function that
 * is pointed to by getchar and printf when called.
 *
 * The Serial parameters can be easily changed by changing the following Macros.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 * THE UART_init and UART Handler was heavily taken from Alexander Dean Code
 * as given below.
 *
 * https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/UART.c
 *
 */

#include "UART.h"
#include <stdio.h>

#define UART_NINE_DATA_BIT  	0             	//For Nine Data Bits, change this to 1
#define UART_PARITY_ENABLE 		0			  	//For Even Parity, make it 1
#define UART_TWO_STOP_BIT   	1				//For one stop bit, change to 0
#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 				(24e6)
#define SYS_CLOCK				(24e6)

cbfifo_s RX_cbfifo, TX_cbfifo;

void Init_UART0(uint32_t baud_rate) {
	uint16_t sbr;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select one stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(UART_TWO_STOP_BIT) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(UART_NINE_DATA_BIT) | UART0_C1_PE(UART_PARITY_ENABLE);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
			| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Try it a different way
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
									UART0_S1_FE_MASK | UART0_S1_PF_MASK;

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);
	// Enable interrupts. Listing 8.11 on p. 234

	cbfifo_init(&RX_cbfifo);
	cbfifo_init(&TX_cbfifo);

	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	UART0->S1 &= ~UART0_S1_RDRF_MASK;
}


// UART0 IRQ Handler. Listing 8.12 on p. 235
void UART0_IRQHandler(void) {
	uint8_t ch;
	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
								UART0_S1_FE_MASK | UART0_S1_PF_MASK;
		// read the data register to clear RDRF
		ch = UART0->D;
	}
	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		// received a character
		ch = UART0->D;
		UART0 -> D = ch;   				 //Echoing the Characters to the terminal
		if(!cbfifo_full(&RX_cbfifo)){
			cbfifo_enqueue(ch, &RX_cbfifo);
		}
	}
	if ( (UART0->C2 & UART0_C2_TIE_MASK) && 	// transmitter interrupt enabled
			(UART0->S1 & UART0_S1_TDRE_MASK) ) {			 // tx buffer empty
		if(!cbfifo_empty(&TX_cbfifo)) {
			UART0->D = cbfifo_dequeue(&TX_cbfifo);
		}
		else {
			UART0->C2 &= ~UART0_C2_TIE_MASK; //Disabling TX interrupt if buffer is full
		}
	}
}


int __sys_write(int handle, char *buf, int size)
{
	int TX_buf_add = -1;
	while(*buf != '\0')
	{
		while(cbfifo_full(&TX_cbfifo));			//Waits until the buffer is dequeued
		cbfifo_enqueue(*buf++, &TX_cbfifo);		//Starts Enqueuing the string into the buffer
		TX_buf_add = 0;
	}
	if (!(UART0->C2 & UART0_C2_TIE_MASK)) {		//If interrupt is disabled, enable it.
		UART0->D = cbfifo_dequeue(&TX_cbfifo);
		UART0->C2 |= UART0_C2_TIE(1);
	}
	return TX_buf_add;
}

int __sys_readc(void)
{
	if(cbfifo_empty(&RX_cbfifo))				//If buffer is empty, can't dequeue
		return -1;
	else{
		return cbfifo_dequeue(&RX_cbfifo);		//Dequeues from the buffer and return
	}
}

