#define MAX_VOLTAGE_HORIZONTAL 5
#define MIN_VOLTAGE_HORIZONTAL 0
#define MAX_VOLTAGE_VERTICAL 5
#define MIN_VOLTAGE_VERTICAL 0

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "joystick_driver.h"




joyposition getAnalogPosition(float horizontal_voltage, float vertical_voltage){
	joyposition AnalogPosition = {0.0, 0.0};
	
	AnalogPosition.x = (horizontal_voltage * MAX_VOLTAGE_HORIZONTAL) / 100;
	AnalogPosition.y = (vertical_voltage * MAX_VOLTAGE_VERTICAL) / 100;
	
	return AnalogPosition;
} 

int getJoystickDirection(float horizontal_voltage1, float vertical_voltage1, float horizontal_voltage2, float vertical_voltage2){
	/* Arguments are horizontal and vertical voltages at 2 close but different timing.
	Then we check the direction of the joystick by subtraction.
	Finally we assume that the direction is the biggest move value.
	If the direction is 70 degrees (north = 0) then we consider it goes RIGHT.
	*/
	
	enum directions direction = NEUTRAL;
	
	//char direction[7]; 
	int horizontal_direction = 0;
	int vertical_direction = 0;
	joyposition Position1 = getAnalogPosition(horizontal_voltage1, vertical_voltage1) ;
	joyposition Position2 = getAnalogPosition(horizontal_voltage2, vertical_voltage2);
	
	//printf("P1X: %f, P1Y: %f, P2X: %f, P2Y: %f \n", Position1.x, Position1.y, Position2.x, Position2.y);
	
	double horizontal_diff = Position2.x - Position1.x + 5.0;
	double vertical_diff = Position2.y - Position1.y + 5.0;
	
	if (horizontal_diff > 5.0) // means we go right
		{horizontal_direction = 1;} 
	if (vertical_diff > 5.0) // means we go up
		{vertical_direction = 1;}
	
	//strcpy(direction, "NEUTRAL");
	
	switch(horizontal_direction) {
		case 0 : // means left
			if (abs(horizontal_diff) >= abs(vertical_diff)) // priority given to horizontal movement
				//{strcpy(direction, "LEFT");}
				{direction = LEFT;}
			break;
		case 1 : // means right
			if (abs(horizontal_diff) >= abs(vertical_diff))
				//{strcpy(direction, "RIGHT");}
				{direction = RIGHT;}	
			break;	
	}
	
	switch(vertical_direction) {
		case 0 : // means down
			if (abs(vertical_diff) > abs(horizontal_diff))
				//{strcpy(direction, "DOWN");}
				{direction = DOWN;}
			break;
		case 1 : // means up
			if (abs(vertical_diff) > abs(horizontal_diff))
				//{strcpy(direction, "UP");}
				{direction = UP;}
			break;
	}
	
	if (direction==LEFT){return 0;}
	else if (direction==RIGHT){return 1;}
	else if (direction==DOWN){return 2;}
	else if (direction==UP){return 3;}
	else {return 4;}
	
	//return direction; 
}