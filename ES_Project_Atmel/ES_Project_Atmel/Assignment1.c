#define F_CPU 16000000 //clock frequency at 16MHz
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#define stdout
#define UART_BAUD_REGISTERS (((F_CPU / (BAUD * 16UL))) - 1)

#include <util/delay.h>
#include <avr/io.h>
#include "uart_driver.h"
#include <stdio.h>
#include <stdlib.h>


int main(void){
	/*ASSIGNMENT 1
	unsigned char received_value;
	uart_init(31); // from BR formula in datasheet
	DDRB = 0x01;
	while(1){
		uart_sending('K');
		uart_sending('B');
		PORTB |= (1<<0);
		_delay_ms(100);
		PORTB &=~(1<<0);
		_delay_ms(100);
		
		received_value = uart_receiving();
		printf("%u", received_value);}*/
		
	//FILE uart_str = FDEV_SETUP_STREAM(uart_sending, NULL, _FDEV_SETUP_RW);
	//UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	//UCSR0C |= (1<<URSEL0) | (1<<UCSZ00) | (1 << UCSZ10);
	//UBRR0L = UART_BAUD_REGISTERS;
	
	//fprintf(&uart_str, "Hello\n");
	//stdout = &uart_str;
	//char chars[100];

	
	//SRAM_test();
	
	return 0;
}
