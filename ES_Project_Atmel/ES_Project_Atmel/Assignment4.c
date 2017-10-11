/*
 * ES_Project_2.c
 *
 * Created: 06.09.2017 09:11:29
 *  Author: asgerber
 */ 

 // Header
// current_state button_neutra
// neue funktionen 

#define F_CPU 16000000 //clock frequency at 16MHz
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#define stdout
#define UART_BAUD_REGISTERS (((F_CPU / (BAUD * 16UL))) - 1)

#include <util/delay.h>
#include <avr/io.h>
#include "uart_driver.h"
/*#include "joystick_driver.h"
#include "ADC_driver.h"
#include "oled_driver.h"*/
#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>


uint8_t current_arrow_pos = 2;
uint8_t directionNumb = 0; // 0-neutral, 1-Down, 2-UP, 3-right, 4-left


ISR(INT0_vect){
	
	}

void INIT(){
	//Initiation of all components
	//uart_init();
	//JOY_init();
	//OLED_init();
	
	//Initialization of interruption
	//----- External Interrupt request 1 and 2 Enable
	GICR |= (1 << INT0) | (1 << INT1) | (1 << INT2);
	//----- Global Interrupt Enable
	SREG |= (1 << 7);
	
	//----- INT1 - rising edge INT0 - rising edge
	MCUCR |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC01);
	//EMCUCR &= (0 << ISC2);
	sei();
}
int main(void){
	directionsButton direction;
	menu currentMenuMain = m_menu;
	//Initialisation
	//INIT();
	
	// Init
	MCUCR |= (1<<SRE); //Enable SRE of MCUCR to use SRAM
	fdevopen(&uart_sending, &uart_receiving);
	uart_init(31);
	//SRAM_test();
	
	
		
	OLED_init();
	OLED_reset();
	
	// LED Test
	DDRB |= (1<<PB0);
	
	//menu_welcome();
	//_delay_ms(1000);
	
	menu_main();
	
	while(1){		
		direction = getJoystickDirectionButton();
		
		if (currentMenuMain == m_menu) {
			//PORTB |= (1<<PB0);
			currentMenuMain = menu_main_handler(direction);
			//PORTB ^= (1<<PB0);
		} else if (currentMenuMain == m_start_game) {
			currentMenuMain = menu_StartGame_handler(direction);
			
			//PORTB ^= (1<<PB0);
		} else if (currentMenuMain == m_select_player) {
			currentMenuMain = menu_SelPlayer_handler(direction);
			//PORTB ^= (1<<PB0);
		} else if (currentMenuMain == m_set_brigthness) {
			currentMenuMain = menu_SetBrightness_handler(direction);
			//PORTB ^= (1<<PB0);
		} else {
			//PORTB ^= (1<<PB0);
		}
		/*
		
		// current_state und button_neutral rausnehmen
		if (direction == N_B) {
			//button_neutral_position = 0;
			//PORTB ^= (1<<PB0);
		}
		if ((direction == D_B) ) {
		//	PORTB ^= (1<<PB0);
			OLED_erase_arrow(current_arrow_pos,0);
			if (current_arrow_pos == 4) {
				current_arrow_pos = 2;
				} else {
				current_arrow_pos++;
			}			
			OLED_print_arrow(current_arrow_pos,0);
		} else if ((direction == U_B)) {
				OLED_erase_arrow(current_arrow_pos,0);
				if (current_arrow_pos == 2) {
					current_arrow_pos = 4;
				} else {
					current_arrow_pos--;
			}
			OLED_print_arrow(current_arrow_pos,0);
		} else if ((direction == R_B)) {
			//OLED_reset();
			//menu = getMenu(current_arrow_pos);			
		} else if ((direction == L_B)) {
			menu_main();
		}*/
	}	
}


ISR(INT2_vect) {
	
	PORTB ^= (1<<PB0);
}