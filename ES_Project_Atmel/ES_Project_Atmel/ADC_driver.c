#define F_CPU 16000000
#include "ADC_driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>

uint8_t ADC_read(uint8_t channel){
	
	volatile char *readValue = (char *)0x1400;
	readValue[0] = channel;
	
	_delay_ms(5); // timing for conversion
	
	return readValue[0];
	
	/*
	//Used to read joystick, so we need to put a11=0(PC3) and a10=1(PC2)
	DDRC |= 0x0C; //Enable pins PC3 and PC2
	PORTC|= 0x04; //a10=1
	PORTC &= 0xF7; //a11=0
	*/
	
}