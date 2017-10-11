#include <stdio.h>

#include "joystick_driver.h"
#include "ADC_driver.h"
#include "oled_driver.h"

typedef enum {
	m_menu,
	m_start_game,
	m_select_player,
	m_set_brigthness
} menu;

// Different states of the menu
void menu_welcome();

void menu_main();

menu menu_main_handler(directionsButton direct);

menu menu_SelPlayer_handler(directionsButton direct);

menu menu_StartGame_handler(directionsButton direct);

menu menu_SetBrightness_handler(directionsButton direct);

void menu_main_draw();

// return submenu state
menu getMenu(uint8_t menu_row);

void menu_start_game();
void menu_select_player();
void menu_set_brigthness();




//Useful functions
int menu_give_new_state(); //Return the new state after a click