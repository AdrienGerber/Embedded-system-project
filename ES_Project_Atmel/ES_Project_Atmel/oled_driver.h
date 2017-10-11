#include <avr/io.h>
#include <stdio.h>

#include  <avr/pgmspace.h>



void OLED_init(); 

void OLED_command(uint8_t cmd);

void OLED_data(uint8_t data);


// Clear display
void OLED_reset();
// Set displqy
void OLED_set(); 
// Clear
void OLED_clear_line(uint8_t line); 
void OLED_clear_column(uint8_t column); 
void OLED_erase_arrow(uint8_t row, uint8_t column);

// goto pos(0,0)
void OLED_home(); 
// GoTo 0-7 lines
void OLED_goto_line(uint8_t line); 
// GoTo 0-127-columns
void OLED_goto_column(uint8_t column); 
// GoTo Pos
void OLED_pos(uint8_t row, uint8_t column); 


// Print char
void OLED_print(char* c);
// Print string
void OLED_print_string(char* string);

// Print arrow
// right
void OLED_print_arrow(uint8_t row, uint8_t column);
// left
void OLED_print_arrow_left(uint8_t row, uint8_t column);
// down
void OLED_print_arrow_down(uint8_t row, uint8_t column);

// Print Brightness lvl
void OLED_print_br_lvl(uint8_t row, uint8_t column);
// Print segment
void OLED_set_segment(uint8_t line, uint8_t column, uint8_t data);
//Clear all
void OLED_clear_all(void);
// Set brightness
void OLED_set_brightness(uint8_t lvl);

// Draw
void OLED_draw_pikachu(uint8_t row, uint8_t column); 
void OLED_draw_line_v(uint8_t x, uint8_t y, uint8_t length);
void OLED_draw_line_h(uint8_t x, uint8_t y, uint8_t length);
void OLED_draw_rectangle(uint8_t x, uint8_t y, uint8_t height, uint8_t weight);
void OLED_teub();