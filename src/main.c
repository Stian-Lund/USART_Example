/*
 * USART Example for ATMEGA168
 * 
 * Functions for initializing, sending, and receiving data with the USART interface.
 * 
 * Created 27. April 2021
 * by Stian Østhus Lund
 * 
 */

#define F_CPU 8000000

#include <util/delay.h>
#include "avr/io.h"

#define BAUD 9600
#define MYUBRR 51		//UBRR = 51 for 9600 Baud at 8MHz clock

void USART_init(unsigned int ubrr) {
	/* Set the baud rate */
	UBRR0H = (unsigned char) (MYUBRR>>8);
	UBRR0L = (unsigned char) MYUBRR;
	
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	// Set frame formate: 8data, 2stop bit
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

unsigned char USART_Receive(void) {
	/* Wait for incomming data */
	while (!(UCSR0A & (1<<RXC0)))
	;
	/* Return the data */
	return UDR0;
}

void USART_Transmit (unsigned char data) {
	// Wait for empty transmitt buffer
	while ( !(UCSR0A & (1<<UDRE0)) ) {	}
	
	// Put data into buffer, sends the data
	UDR0 = data;
}

int main()
{
	USART_init(MYUBRR);
	while(1)
	{
		USART_Transmit('H');
		USART_Transmit('e');
		USART_Transmit('l');
		USART_Transmit('l');
		USART_Transmit('o');
		USART_Transmit(',');
		
		USART_Transmit(0xA);		// New Line
		
		USART_Transmit('W');
		USART_Transmit('o');
		USART_Transmit('r');
		USART_Transmit('l');
		USART_Transmit('d');
		USART_Transmit('!');
		
		USART_Transmit(0xA);		// New Line
		USART_Transmit(0xA);		// New Line
		
		_delay_ms(1000);			// Delay 1000ms
	}

	return 0;
}
