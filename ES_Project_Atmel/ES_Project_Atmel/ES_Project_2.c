/*
 * ES_Project_2.c
 *
 * Created: 06.09.2017 09:11:29
 *  Author: asgerber
 */ 


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



void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size= 0x800;
	uint16_t write_errors= 0;
	uint16_t retrieval_errors= 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			//printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			//printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with\n%4d errors in write phase and\n%4d errorsin retrieval phase\n\n", write_errors, retrieval_errors);
}





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
	
	/*D Latch test
	DDRA |= 0xFF;
	DDRE |= 0x02;
	while(1){
		PORTA &= 0x00;
		PORTA |= 0xF0;
		PORTE |= 0x02;
		_delay_ms(100);
		PORTE &= 0xFD;
		_delay_ms(100);
		PORTA &= 0x00;
		PORTA |= 0x0F;
		PORTE |= 0x02;
		_delay_ms(100);
		PORTE &= 0xFD;
		_delay_ms(100);} */

	fdevopen(&uart_sending, &uart_receiving);
	uart_init(31);
	
	//FILE uart_str = FDEV_SETUP_STREAM(uart_sending, NULL, _FDEV_SETUP_RW);
	//UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	//UCSR0C |= (1<<URSEL0) | (1<<UCSZ00) | (1 << UCSZ10);
	//UBRR0L = UART_BAUD_REGISTERS;
	
	//fprintf(&uart_str, "Hello\n");
	//stdout = &uart_str;
	//char chars[100];

	
	//SRAM_test();
	
	SRAM_test();
	while(1){
		//scanf("%s", chars);
		//printf("Hey: %s\n", chars);
		
	}
	
	return 0;
}




