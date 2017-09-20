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
#include "joystick_driver.h"
#include "ADC_driver.h"
#include <stdio.h>
#include <stdlib.h>


int main3(void){
	
	MCUCR |= (1<<SRE); //Enable SRE of MCUCR to use SRAM
	fdevopen(&uart_sending, &uart_receiving);
	uart_init(31);
	//SRAM_test();
	

	joyposition joystickPos = getAnalogPosition();
	joyposition joystickPrevPos = joystickPos;
	int left_button_input = 0;
	
	DDRB &= 0x0C;
	while(1){
		joystickPos = getAnalogPosition();
		//printf("\nx=%d%%   y=%d%%\n", (int)joystickPos.x, (int)joystickPos.y);
		
		//printf("Direction is: %d\n", getJoystickDirection());//Where 0.Left - 1.Right - 2.Up - 3.Down - 4.Neutral\n
		_delay_ms(100);
		joystickPrevPos = joystickPos;
		
		printf("Left: %d\n",left_button());
		printf("Right: %d\n\n",right_button());
	}

	
	return 0;
}





/*
int joystick_direction = getJoystickDirection(2.5, 2.5, 2.5, 2.5); // 4
printf("Direction: %d\n", joystick_direction);

joystick_direction = getJoystickDirection(2.5, 2.5, 0.0, 2.5); //Left = 0
printf("Direction: %d\n", joystick_direction);

joystick_direction = getJoystickDirection(2.5, 2.5, 5.0, 2.5); //Right = 1
printf("Direction: %d\n", joystick_direction);

joystick_direction = getJoystickDirection(2.5, 2.5, 2.5, 0.0); //Down = 2
printf("Direction: %d\n", joystick_direction);

joystick_direction = getJoystickDirection(2.5, 2.5, 2.5, 5.0); //Up = 3
printf("Direction: %d\n", joystick_direction);*/