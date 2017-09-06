/*
 * uart_driver.c
 *
 * Created: 30.08.2017 09:16:45
 *  Author: asgerber
 * 30/08/17 - 10h00 - 
 */ 

#define F_CPU 16000000 //clock frequency at 16MHz
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include <util/delay.h>
#include <avr/io.h>
#include "uart_driver.h"
#include <stdio.h>

void uart_init(unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}

void uart_sending(unsigned char data){
	/* Sending frames with 5 to 8 Data Bits */
	
	/* wait for empty buffer 
	=> cannot send new data if the previous one is not sent. */
	while(!(UCSR0A & (1 << UDRE0)))
		;
	UDR0 = data;
}

unsigned char uart_receiving(void){
	/* Receiving frames with 5 to 8 Data Bits */

	// waiting for data
	while(!(UCSR0A & (1 << RXC0)))
		;
			
	/* b. App wants to be notified when new char is received (?) enable int*/
		
	return UDR0;
}



/* what could be the main function testing uart:*
void main(void){
	uart_init(31) // from BR formula in datasheet
	
	while(1)
	{
		uart_sending('Z');
		_delay_ms(2000);
	}
	
}*/

