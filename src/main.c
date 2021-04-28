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
#include <avr/io.h>

/* Set baud rate register for baud rate 9600, at 8MHz */
#define BAUD_UBRR 51

void USART_init(unsigned int ubrr) {
	/* Set the baud rate */
	UBRR0H = (unsigned char) (BAUD_UBRR>>8);
	UBRR0L = (unsigned char) BAUD_UBRR;
	
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	/* Set frame formate: 8data, 2stop bit */
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

unsigned char USART_Receive(void) {
	/* Wait for incoming data */
	while (!(UCSR0A & (1<<RXC0)))
	;
	/* Return the data */
	return UDR0;
}

void USART_Transmit (unsigned char data) {
	/* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1<<UDRE0)) ) {	}
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

int main()
{
	USART_init(BAUD_UBRR);
	while(1)
	{
		USART_Transmit('H');
		USART_Transmit('e');
		USART_Transmit('l');
		USART_Transmit('l');
		USART_Transmit('o');
		USART_Transmit(',');
		USART_Transmit(' ');
		USART_Transmit('W');
		USART_Transmit('o');
		USART_Transmit('r');
		USART_Transmit('l');
		USART_Transmit('d');
		USART_Transmit('!');
		
		//Newline
		USART_Transmit(0x0D);
		USART_Transmit(0x0A);
		
		_delay_ms(1000);			// Delay 1000ms
	}

	return 0;
}