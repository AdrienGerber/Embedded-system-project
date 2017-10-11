#define MAX_VOLTAGE_HORIZONTAL 5
#define MIN_VOLTAGE_HORIZONTAL 0
#define MAX_VOLTAGE_VERTICAL 5
#define MIN_VOLTAGE_VERTICAL 0
#define SENSITIVITY 5 //Sensitivity in percent
#define F_CPU 16000000 //clock frequency at 16MHz

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "joystick_driver.h"
#include "ADC_driver.h"
#include <util/delay.h>
#include <avr/io.h>


uint8_t direction_state; // 0-neutral, 1-down, 2-up, 3-right, 4-left
uint8_t state;	// 0-neutral, 1-down, 2-up, 3-right, 4-left 

joyposition getAnalogPosition(){
	/* Function using data from ADC
	*/
	float horizontal_voltage = (float)ADC_read(0x4); // return values from 0 (left) to 255 (right)
	float vertical_voltage = (float)ADC_read(0x5);
	joyposition AnalogPosition;
	
	// ADC raw data
	//printf("%d et %d\n", (int)horizontal_voltage, (int)vertical_voltage);
	
	AnalogPosition.x = ((horizontal_voltage - 127)*100) / 127; // -100 to 100
	AnalogPosition.y = ((vertical_voltage - 127)*100) / 127; // -100 to 100
	
/*	if (AnalogPosition.x < -80 ) {
		PORTB ^= (1<<PB0);
	}*/
	
	return AnalogPosition;
}


directions getJoystickDirection(){
	directions direction = NEUTRAL;
	

	
	int horizontal_direction = 0;
	int vertical_direction = 0;
	
	joyposition Position1 = getAnalogPosition();
	_delay_us(10); //Wait for a certain amount of time to get the second position
	joyposition Position2 = getAnalogPosition();
	
	
	float horizontal_diff = Position2.x - Position1.x;
	float vertical_diff = Position2.y - Position1.y;
	int bNeutral=0; //Equal 1 if we don't move
	
	if(Position2.x > (Position1.x-(float)SENSITIVITY) && Position2.x < (Position1.x+(float)SENSITIVITY) && Position2.y > (Position1.y-(float)SENSITIVITY) && Position2.y < (Position1.y+(float)SENSITIVITY)){
		bNeutral=1;
		direction_state =0;
		//PORTB ^= (1<<PB0);
		direction = R_N;
		
	}
	if (vertical_diff == 0) {
		
		//	PORTB ^= (1<<PB0);
			//direction_state = 0;
			//direction = R_N;
	}	
	
	/*
	if (Position1.x == 0 && Position2.x == 0) {
		direction = R_N;
		direction_state = 0;
	}*/
	
	if (horizontal_diff > 0.0) // means we go right
		{horizontal_direction = 1;} 
	if (vertical_diff > 0.0) // means we go up
		{vertical_direction = 1;}
	
	
	if (fabs(horizontal_diff) >= (fabs(vertical_diff)+(float)SENSITIVITY) && bNeutral==0){
		if(horizontal_direction==0){
				direction=LEFT;

		}
		if(horizontal_direction==1){
			if (direction_state != 4) {
				direction=RIGHT;
				direction_state = 3;
			}
		}
	}
	else if(bNeutral==0){
		if(vertical_direction==0){
			if (direction_state == 0) {
				direction=DOWN;				
				direction_state = 1;
				//_delay_ms(5);
			}
		}
		if(vertical_direction==1){
			if (direction_state == 0) {
				direction=UP;
				direction_state = 2;
				//_delay_ms(5);
			}
		}
	}
	
	return direction;
	
}

int left_button(){
	return (PINB & (1 << PINB1)) >> PINB1;
}

int right_button(){
	return (PINB & (1 << PINB2)) >> PINB2;
}


uint8_t right_slider(void){				
	_delay_us(10);
	return (uint8_t)(ADC_read(0x7));
}

uint8_t left_slider(void){
	_delay_us(10);
	return (uint8_t)(ADC_read(0x6));
}

/*
direction_button getJoystickDirectionButton(void) {
	if ( direction == UP && direction_button == N_B) {
			direction_button = U_B;
	} else if ( direction == DOWN && direction_button == N_B ) {
		direction_button = D_B;
	} else if ( direction == NEUTRAL) {
		direction_button == N_B;
	}
	
}*/

directionsButton getJoystickDirectionButton() {
	
	joyposition Position1 = getAnalogPosition();
	directionsButton direction;
	
		if ( (Position1.x >= -2) && (Position1.x <= 2) && (Position1.y >= -2) && (Position1.y <= 2)) {
			direction = N_B;
			state = 0;
			//PORTB ^= (1<<PB0);
		}			
				
		if ((Position1.y < -80) && (state == 0)) {
			PORTB ^= (1<<PB0);	
			direction = D_B;
			state = 1;
		}
		
		if ((Position1.y > 80) && (state == 0)) {
			PORTB ^= (1<<PB0);	
			direction = U_B;
			state = 2;
		}

		if (Position1.x > 80 && state == 0) {
			PORTB ^= (1<<PB0);	
			direction = R_B;
			state = 3;
		}		
		if (Position1.x < -80 && state == 0) {
			PORTB ^= (1<<PB0);	
			direction = L_B;	
			state = 4;	
		} 
		return direction;
}