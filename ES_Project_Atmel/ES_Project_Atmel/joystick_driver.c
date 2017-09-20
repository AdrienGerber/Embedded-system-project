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

/*
joyposition getAnalogPosition(float horizontal_voltage, float vertical_voltage){
	joyposition AnalogPosition = {0.0, 0.0};
	
	AnalogPosition.x = (horizontal_voltage / (float)MAX_VOLTAGE_HORIZONTAL) * (float)100;
	AnalogPosition.y = (vertical_voltage / (float)MAX_VOLTAGE_VERTICAL) * (float)100;
	
	return AnalogPosition;
} */
joyposition getAnalogPosition(){
	/* Function using data from ADC
	*/
	float horizontal_voltage = (float)ADC_read(0x4); // return values from 0 (left) to 255 (right)
	float vertical_voltage = (float)ADC_read(0x5);
	joyposition AnalogPosition;
	
	// ADC raw data
	//printf("%d et %d\n", (int)horizontal_voltage, (int)vertical_voltage);
	
	AnalogPosition.x = ((horizontal_voltage - 127)*100) / 127;
	AnalogPosition.y = ((vertical_voltage - 127)*100) / 127;
	
	return AnalogPosition;
}

int getJoystickDirection2(){
	/* Arguments are horizontal and vertical voltages at 2 close but different timing.
	Then we check the direction of the joystick by subtraction.
	Finally we assume that the direction is the biggest move value.
	If the direction is 70 degrees (north = 0) then we consider it goes RIGHT.
	*/
	
	directions direction = NEUTRAL;
	
	//char direction[7]; 
	int horizontal_direction = 0;
	int vertical_direction = 0;

	joyposition Position1 = getAnalogPosition();
	_delay_ms(10);
	joyposition Position2 = getAnalogPosition();
	
	//printf("P1X: %f, P1Y: %f, P2X: %f, P2Y: %f \n", Position1.x, Position1.y, Position2.x, Position2.y);
	
	float horizontal_diff = 100.0 + Position2.x - Position1.x;
	float vertical_diff = 100.0 + Position2.y - Position1.y;
	int bNeutral=0; //Equal 1 if we didnt move
	
	if(Position1.x == Position2.x && Position1.y == Position2.y){
		bNeutral=1;
	}
	
	if (horizontal_diff > 100.0) // means we go right
		{horizontal_direction = 1;} 
	if (vertical_diff > 100.0) // means we go up
		{vertical_direction = 1;}
	
	//strcpy(direction, "NEUTRAL");
	
	if(horizontal_direction==0){
		if (fabs(horizontal_diff-100.0) >= fabs(vertical_diff-100.0) && bNeutral==0){ // priority given to horizontal movement
			//strcpy(direction, "LEFT");
			direction = LEFT;
		}
	}
	if(horizontal_direction==1){
		if (fabs(horizontal_diff-100.0) >= fabs(vertical_diff-100.0) && bNeutral==0){ // priority given to horizontal movement
			//strcpy(direction, "RIGHT");
			direction = RIGHT;
		}
	}
	if(vertical_direction==0){
		if (fabs(horizontal_diff-100.0) < fabs(vertical_diff-100.0)){ 
			//strcpy(direction, "DOWN");
			direction = DOWN;
		}
	}
	if(vertical_direction==1){
		if (fabs(horizontal_diff-100.0) < fabs(vertical_diff-100.0)){ 
			//strcpy(direction, "UP");
			direction = UP;
		}
	}
	
	if (direction==LEFT){return 0;}
	else if (direction==RIGHT){return 1;}
	else if (direction==DOWN){return 2;}
	else if (direction==UP){return 3;}
	else {return 4;}
	
	//return direction; 
}

directions getJoystickDirection(){
	directions direction = NEUTRAL;
	
	int horizontal_direction = 0;
	int vertical_direction = 0;
	
	joyposition Position1 = getAnalogPosition();
	_delay_ms(10); //Wait for a certain amount of time to get the second position
	joyposition Position2 = getAnalogPosition();
	
	
	float horizontal_diff = Position2.x - Position1.x;
	float vertical_diff = Position2.y - Position1.y;
	int bNeutral=0; //Equal 1 if we didnt move
	
	if(Position2.x > (Position1.x-(float)SENSITIVITY) && Position2.x < (Position1.x+(float)SENSITIVITY) && Position2.y > (Position1.y-(float)SENSITIVITY) && Position2.y < (Position1.y+(float)SENSITIVITY)){
		bNeutral=1;
	}
	
	if (horizontal_diff > 0.0) // means we go right
		{horizontal_direction = 1;} 
	if (vertical_diff > 0.0) // means we go up
		{vertical_direction = 1;}
	
	
	if (fabs(horizontal_diff) >= (fabs(vertical_diff)+(float)SENSITIVITY) && bNeutral==0){
		if(horizontal_direction==0){
			direction=LEFT;
		}
		if(horizontal_direction==1){
			direction=RIGHT;
		}
	}
	else if(bNeutral==0){
		if(vertical_direction==0){
			direction=DOWN;
		}
		if(vertical_direction==1){
			direction=UP;
		}
	}
	
	return direction;
	
}

int left_button(){
	/*
	uint8_t pin_value;
	pin_value = PINB & (1 <<PINB2);
	
	if (pin_value == 0) {
				
	} else {
		
	}*/
	
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

