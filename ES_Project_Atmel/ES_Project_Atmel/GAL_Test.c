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


int main() {
	
	// D-Latch Test
   // DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);
    DDRC |= 0x0F;    //A8-A11
  	
    while(1){
		
		// OLED Command
        PORTC |= 0x01;
        _delay_ms(100);		
        
		// OLED Data
        PORTC |= 0x03;
        _delay_ms(100);

		// ADC
        PORTC |= 0x04;
        _delay_ms(100);
		
		// SRAM
		PORTC |= 0x08;
		_delay_ms(100);
	}           
        return 0;
}


