/*
 * ES_Project_Atmel.c
 *
 * Created: 30.08.2017 09:16:45
 *  Author: asgerber
 * 30/08/17 - 9h40 - Test program Ex1 Q6, square signal on PA5
 */ 

#define F_CPU 16000000 //clock frequency at 16MHz
#include <util/delay.h> //Lib for using time delay
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

//#include "uart_driver.h"

int main(void)
{
	// DDRA |= (1<<DDA5); //6th bit of PORTA(PA5) = OUTPUT
	DDRA = 0xFF;
	//DDRA = (1<<PA5);
	
    while(1)
    {
		
		PORTA |= (1<<1);
		
		_delay_ms(500);
		PORTA &=~(1<<1);
		_delay_ms(500);
		
		
		
	//	PORTA |= (1<<PA0);
		//_delay_ms(500);
        /*PORTA |= 0x20; //Pin5 ON
		_delay_ms(500); //Wait for 0.5s
		//PORTA &= 0xDF; //Pin5 OFF
		PORTA |= 0x00; //Pin5 OFF
		_delay_ms(500); //Wait for 0.5s*/
    }
	return 0;
}