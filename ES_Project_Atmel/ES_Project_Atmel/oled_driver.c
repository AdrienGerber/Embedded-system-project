#include "oled_driver.h"
#include "oled_fonts.h"

#define F_CPU 16000000 //clock frequency at 16MHz
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <util/delay.h>
#include <avr/io.h>
#include "uart_driver.h"
#include <stdio.h>
#include <string.h>

uint8_t current_line;
uint8_t current_column;

void OLED_init() {

	MCUCR |= (1<<SRE); // enable external memory interface
	SFIOR |= (1<<XMM2); // release PC7-PC4 (needed for JTAG)
	
	OLED_command(0xae); // display off
	OLED_command(0xa1); //segment remap
	OLED_command(0xda); //common pads hardware: alternative
	OLED_command(0x12);
	OLED_command(0xc8); //common output scan direction:com63~com0
	OLED_command(0xa8); //multiplex ration mode:63
	OLED_command(0x3f);
	OLED_command(0xd5); //display divide ratio/osc. freq. mode
	OLED_command(0x80);
	OLED_command(0x81); //contrast control
	OLED_command(0x50);
	OLED_command(0xd9); //set pre-charge period
	OLED_command(0x21);
	OLED_command(0x20); //Set Memory Addressing Mode -> Page adressing mode
	OLED_command(0x02);
	OLED_command(0xdb); //VCOM deselect level mode
	OLED_command(0x30);
	OLED_command(0xad); //master configuration
	OLED_command(0x00);
	OLED_command(0xa4); //out follows RAM content
	OLED_command(0xa6); //set normal display
	OLED_command(0xaf); // display on
}

void OLED_reset() {
	for(uint8_t i = 0; i < 8; i++){
		OLED_clear_line(i);
	}
}

void OLED_set() {
	for(uint8_t i = 0; i < 8; i++){
		for(uint8_t j = 0; j<128; j++){
			OLED_set_segment(i,j,0xFF);
		}
	}
}

void OLED_home() {
	OLED_goto_line(0);
	OLED_goto_column(0);
}	

void OLED_command(uint8_t cmd) {
	volatile uint8_t* OLED_cmd = (uint8_t*) 0x1000;
	*OLED_cmd = cmd;	
}

void OLED_data(uint8_t data) {
	volatile uint8_t* OLED_data = (uint8_t*) 0x1200;
	*OLED_data = data;
}

void OLED_goto_line(uint8_t line) {
	OLED_command(0xB0 + line);
	current_line = line;
}

void OLED_goto_column(uint8_t column) {

	OLED_command(0xB0+current_line);
	OLED_command(0x21); //Set column adress command
	OLED_command(column);
	OLED_command(127);
}	

void OLED_clear_column(uint8_t column) {
	
	OLED_goto_column(column);
	
	for(uint8_t i = 0; i < 8; i++){
		OLED_goto_line(i);
		OLED_data(0x00);
		//SCREEN[i][column]=0x00;
	}
}

void OLED_clear_line(uint8_t line) {
	
	//OLED_goto_line(line);
	OLED_pos(line,0);
	for(uint8_t i = 0; i < 128; i++){
		
		OLED_data(0x00);
		//SCREEN[line][i]=0x00;
	}
}

void OLED_clear_all() {
	for(uint8_t i=0; i<128; i++){
		OLED_clear_column(i);
	}
}

void OLED_erase_arrow(uint8_t row, uint8_t column) {
	OLED_pos(row, column);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
}


void OLED_set_segment(uint8_t line, uint8_t column, uint8_t data){
	OLED_pos(line, column);
	OLED_data(data);
	//SCREEN[line][column]=data;
}
/*
void OLED_set_pixel(uint8_t x, uint8_t y){
	uint8_t line=x/8;
	uint8_t bit=x-8*line; //We want to know which bit we have to set
	SCREEN[line][y]|=1<<bit; //Is this the right sign?
	OLED_set_segment(line, y, SCREEN[line][y]);
}

void OLED_clr_pixel(uint8_t x, uint8_t y){
	uint8_t line=x/8;
	uint8_t bit=x-8*line; //We want to know which bit we have to set
	SCREEN[line][y] &= 0xFF - 2**bit;
	OLED_set_segment(line, y, SCREEN[line][y]);
}
*/
void OLED_pos(uint8_t row, uint8_t column) {
	OLED_goto_line(row);
	OLED_goto_column(column);
}	

void OLED_print(char* c) {
	int index = (int)c - 32;
	for(uint8_t i = 0; i < 4; i++){
		OLED_data(pgm_read_byte(&(font4[index][i])));
	}	
}


void OLED_print_string(char* string) {
	int i=0;
	while(string[i]!='\0' && i < 32)
	{
		OLED_print(string[i]);
		i++;
	}
}

void OLED_print_arrow(uint8_t row, uint8_t column) {
	
	OLED_pos(row, column);
	OLED_data(0b00010000);
	OLED_data(0b00010000);
	OLED_data(0b00010000);
	OLED_data(0b00010000);
	OLED_data(0b01111100);
	OLED_data(0b00111000);
	OLED_data(0b00010000);
}

void OLED_print_arrow_down(uint8_t row, uint8_t column) {
	
	OLED_pos(row, column);
	OLED_data(0b0000000);
	OLED_data(0b00100000);
	OLED_data(0b01100000);
	OLED_data(0b11111110);
	OLED_data(0b01100000);
	OLED_data(0b00100000);
	OLED_data(0b00000000);
}

void OLED_print_arrow_left(uint8_t row, uint8_t column) {
	
		OLED_pos(row, column);
		OLED_data(0b0001000);
		OLED_data(0b00111000);
		OLED_data(0b01111100);
		OLED_data(0b00010000);
		OLED_data(0b00010000);
		OLED_data(0b00010000);
		OLED_data(0b00010000);
}

void OLED_draw_line_v(uint8_t i, uint8_t j, uint8_t length){
	
	uint8_t start_line = i/8;
	uint8_t last_line = (i+length)/8;
	
	OLED_pos(start_line, j);
	
	uint8_t mini_line = i-8*start_line;
	uint8_t last_mini_line = (i+length)-8*last_line;


	uint8_t dataFirst=0x00;
	for(uint8_t l=7;l>mini_line;l--){
		dataFirst += (1<<l);
	}
	OLED_data(dataFirst);
	
	for (uint8_t k=start_line+1;k<last_line;k++)
	{
		OLED_pos(k,j);
		OLED_data(0xFF);
	}
	
	OLED_pos(last_line,j);
	uint8_t dataLast=0x00;
	for(uint8_t l=0;l<last_mini_line;l++){
		dataLast += (1<<l);
	}
	OLED_data(dataLast);
}

void OLED_draw_line_h(uint8_t i, uint8_t j, uint8_t length){
	uint8_t start_line = i/8;
	uint8_t mini_line = i-8*start_line;
	OLED_pos(start_line, j);
	
	for (int k=0; k < length; k++)
	{
		OLED_data(1 << (mini_line-1));
	}
}

void OLED_draw_rectangle(uint8_t x, uint8_t y, uint8_t height, uint8_t weight){
	OLED_draw_line_h(x+2,y,weight);
	OLED_draw_line_h(x+height,y,weight);
	OLED_draw_line_v(x,y,height);
	OLED_draw_line_v(x,y+weight,height);
}

void OLED_set_brightness(uint8_t lvl){
	OLED_command(0x81);
	OLED_command(lvl);
}

void OLED_teub(){
	OLED_draw_rectangle(10,10,20,20);
	OLED_draw_rectangle(30,10,20,20);
	OLED_draw_rectangle(15,30,10,50);
}

void OLED_animation(){ //fill in the screen with set dot
	uint8_t i,j;
	for(i=0;i<32;i++){
		for(j=0;j<64;j++){
			OLED_set_pixel(2*i,2*j);
		}
	}
	_delay_ms(500); //Don't forget time library, pause of 500ms
	
	for(i=0;i<32;i++){
		for(j=0;j<64;j++){
			OLED_set_pixel(2*i+1,2*j);
		}
	}
	
	_delay_ms(500);
	
	for(i=0;i<32;i++){
		for(j=0;j<64;j++){
			OLED_set_pixel(2*i,2*j+1);
		}
	}
	
	_delay_ms(500);
	
	for(i=0;i<32;i++){
		for(j=0;j<64;j++){
			OLED_set_pixel(2*i+1,2*j+1);
		}
	}
	
	_delay_ms(500);
}



void OLED_draw_pikachu(uint8_t row, uint8_t column) { //PIKACHU
	
	OLED_pos(row,column);
	OLED_data(0b00000001);
	OLED_data(0b00000111);
	OLED_data(0b00001111);
	OLED_data(0b00011110);
	OLED_data(0b00110010);
	OLED_data(0b01100100);
	OLED_data(0b10000100);
	OLED_data(0b00001000);
	OLED_data(0b00001000);
	OLED_data(0b00010000);
	OLED_data(0b00010000);
	OLED_data(0b00100000);
	
	OLED_data(0b01000000);
	OLED_data(0b01000000);
	OLED_data(0b01000000);
	OLED_data(0b01000000);
	OLED_data(0b01000000);
	OLED_data(0b01000000);
	OLED_data(0b01000000);
	OLED_data(0b01000000);
	OLED_data(0b01000000);
	OLED_data(0b01000000);
	
	OLED_data(0b00100000);
	OLED_data(0b00010000);
	OLED_data(0b00010000);
	OLED_data(0b00001000);
	OLED_data(0b00001000);
	OLED_data(0b10000100);
	OLED_data(0b01100100);
	OLED_data(0b00110010);
	OLED_data(0b00011110);
	OLED_data(0b00001111);
	OLED_data(0b00000111);
	OLED_data(0b00000001);
	
	
	
	OLED_pos(row+1,column);
	OLED_data(0b11000000);
	OLED_data(0b00111000);
	OLED_data(0b00001000);
	OLED_data(0b00010000);
	OLED_data(0b00100000);
	OLED_data(0b01000000);
	OLED_data(0b10000000);
	OLED_data(0b00000001);
	OLED_data(0b11100010);
	OLED_data(0b00011110);
	OLED_data(0b10000001);
	
	OLED_data(0b10111000);
	OLED_data(0b00110000);
	OLED_data(0b00111000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00100000);
	OLED_data(0b00100000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00111000);
	OLED_data(0b00110000);
	OLED_data(0b10111000);
	
	OLED_data(0b10000001);
	OLED_data(0b00011110);
	OLED_data(0b11100010);
	OLED_data(0b00000001);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	
	
	OLED_pos(row+2,column);
	OLED_data(0b00000011);
	OLED_data(0b00000010);
	OLED_data(0b00000100);
	OLED_data(0b10000100);
	OLED_data(0b01001000);
	OLED_data(0b00110000);
	OLED_data(0b00100000);
	
	OLED_data(0b10000001);
	OLED_data(0b01100111);
	OLED_data(0b00011000);
	OLED_data(0b00000001);
	OLED_data(0b00000001);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000010);
	OLED_data(0b00000010);
	OLED_data(0b00000001);
	
	OLED_data(0b00000001);
	OLED_data(0b00000010);
	OLED_data(0b00000010);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000001);
	OLED_data(0b00000001);
	OLED_data(0b00011000);
	OLED_data(0b01100111);
	OLED_data(0b10000000);
	
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	OLED_data(0b00000000);
	
	OLED_pos(row+3,column);
	OLED_data(0b0000);
	OLED_data(0b0000);
	OLED_data(0b0011);
	OLED_data(0b0100);
	OLED_data(0b1000);
	
	OLED_data(0b0000);
	OLED_data(0b1100);
	OLED_data(0b0011);
	OLED_data(0b0000);
	OLED_data(0b0000);
	OLED_data(0b1110);
	OLED_data(0b1000);
	OLED_data(0b0000);
	OLED_data(0b0000);
	OLED_data(0b1111);
	OLED_data(0b0000);
	OLED_data(0b0000);
	
	OLED_data(0b0000);
	OLED_data(0b0000);
	OLED_data(0b1111);
	OLED_data(0b0000);
	OLED_data(0b0000);
	OLED_data(0b1000);
	OLED_data(0b1110);
	OLED_data(0b0000);
	OLED_data(0b0000);
	OLED_data(0b0011);
	OLED_data(0b1100);
	OLED_data(0b0000);
	
	OLED_data(0b0000);
	OLED_data(0b0000);
	OLED_data(0b0000);
	OLED_data(0b0000);
	OLED_data(0b0000);
	
}

