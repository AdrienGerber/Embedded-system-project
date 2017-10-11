#define F_CPU 16000000

#include <avr/io.h>
#include "uart_driver.h"
/*#include "joystick_driver.h"
#include "ADC_driver.h"
#include "oled_driver.h"*/
#include "spi_driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>


void SPI_init(){
	DDRB = (1<<PB5) | (1<<PB7) | (1<<PB4); //Set MOSI(AVR Master) and SCK as OUTPUT and Chip Select SS/
	DDRB &= ~(1<<PB6); // declare MISO as Input
	PORTB |= (1<<4); //Turn the SPI OFF
	//PORTB &= ~(1<<PB4);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0); //Enable SPI, Master and use a clock rate at fck/16*/
}

void SPI_write(uint8_t data){
	SPDR=data;
	
	// we check SPDR whereas we thought we had to check SPSR!!!!?????????
	while(!(SPSR & (1<<SPIF))){;} //Wait until the data is sent correctly

}

uint8_t SPI_read(){
	SPDR=0x00; //Dummy byte
	while(!(SPSR & (1<<SPIF))){;} //Wait until the data can be received, SPSR or SPDR?
	return SPDR; //Return the data
}

//Turn the SPI ON
void SPI_enable() {
	PORTB &= ~(1<<PB4);
}
//Turn the SPI OFF
void SPI_disable() {
	PORTB |= (1<<4);	
}