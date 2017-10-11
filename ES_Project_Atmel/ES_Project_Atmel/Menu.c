#include "Menu.h"
//#include "oled_driver.h"
#include <stdlib.h>
#include <stdio.h>

uint8_t brightness=80;

uint8_t current_arrow_pos_m = 2;
uint8_t playerSelect = 0;

void menu_welcome() { //State 0
	OLED_reset();
	OLED_pos(3, 55);
	OLED_print_string("Welcome");	
	
	OLED_draw_pikachu(4,90);
	OLED_draw_pikachu(4,10);
}

void menu_main() { //State 1
	OLED_reset();
	OLED_pos(0,0);
	OLED_print_string("Main Menu");
	OLED_pos(2,15);
	OLED_print_string("Start Game"); //Position 0
	OLED_pos(3,15);
	OLED_print_string("Select Player"); //Position 1
	OLED_pos(4,15);
	OLED_print_string("Set brightness"); //Position 2
	OLED_draw_pikachu(4,90);		
}

menu menu_main_handler(directionsButton direct) {
	directionsButton Bdirect = direct;
	menu currentMenu;

	if ((Bdirect == D_B)) {
		OLED_erase_arrow(current_arrow_pos_m,0);
		//PORTB ^= (1<<PB0);
		if (current_arrow_pos_m >= 4) {
			current_arrow_pos_m = 2;
		} else {
			current_arrow_pos_m++;
		}			
		OLED_print_arrow(current_arrow_pos_m,0);
	} else if ((Bdirect == U_B)) {
			OLED_erase_arrow(current_arrow_pos_m,0);
			if (current_arrow_pos_m <= 2) {
				current_arrow_pos_m = 4;
			} else {
				current_arrow_pos_m--;
		}
		OLED_print_arrow(current_arrow_pos_m,0);
	} else if ((Bdirect == R_B)) {
		//PORTB ^= (1<<PB0);
		currentMenu = getMenu(current_arrow_pos_m);			
	} else if ((Bdirect == L_B)) {
		menu_main_draw();
		currentMenu = m_menu;
	}
	return currentMenu;
}
menu menu_SelPlayer_handler(directionsButton direct) {
		directionsButton Bdirect = direct;
		menu currentMenu = m_select_player;
			
		if ((Bdirect == D_B)) {
			OLED_erase_arrow(current_arrow_pos_m,0);
			if (current_arrow_pos_m >= 5) {
				current_arrow_pos_m = 3;
			} else {
				current_arrow_pos_m += 2;
			}
			OLED_print_arrow(current_arrow_pos_m,0);
		} else if ((Bdirect == U_B)) {
				OLED_erase_arrow(current_arrow_pos_m,0);
				if (current_arrow_pos_m <= 3) {
					current_arrow_pos_m = 5;
				} else {
					current_arrow_pos_m -= 2;
				}
			OLED_print_arrow(current_arrow_pos_m,0);
		} else if ((Bdirect == R_B)) {
			if (current_arrow_pos_m == 5) { // 2-Player Mode
				OLED_draw_pikachu(4,90);
				OLED_draw_pikachu(0,90);
				playerSelect = 2;
			} else {	// 1-Player Mode
				OLED_reset();
				menu_select_player();
				OLED_draw_pikachu(4,90);
				playerSelect = 1;
			}
			//currentMenu = m_menu;
		} else if ((Bdirect == L_B)) {
			menu_main_draw();
			if (playerSelect == 2) {
				OLED_draw_pikachu(0,90);
			}			
			currentMenu = m_menu;
		}
		return currentMenu;	
}

menu menu_StartGame_handler(directionsButton direct) {
		directionsButton Bdirect = direct;
		menu currentMenu = m_start_game;
		
		if ((Bdirect == D_B)) {
			OLED_erase_arrow(current_arrow_pos_m,0);
			if (current_arrow_pos_m >= 5) {
				current_arrow_pos_m = 3;
				} else {
				current_arrow_pos_m += 2;
			}
			OLED_print_arrow(current_arrow_pos_m,0);
			} else if ((Bdirect == U_B)) {
			OLED_erase_arrow(current_arrow_pos_m,0);
			if (current_arrow_pos_m <= 3) {
				current_arrow_pos_m = 5;
				} else {
				current_arrow_pos_m -= 2;
			}
			OLED_print_arrow(current_arrow_pos_m,0);
			} else if ((Bdirect == R_B)) {
			//currentMenu = getMenu(current_arrow_pos_m);
			} else if ((Bdirect == L_B)) {
			menu_main_draw();
			currentMenu = m_menu;
		}
		return currentMenu;
}

menu menu_SetBrightness_handler(directionsButton direct) {
		directionsButton Bdirect = direct;
		menu currentMenu = m_set_brigthness;
		
		if ((Bdirect == D_B)) {
			OLED_erase_arrow(current_arrow_pos_m,0);
			if (current_arrow_pos_m >= 5) {
				current_arrow_pos_m = 3;
				} else {
				current_arrow_pos_m += 2;
			}
			OLED_print_arrow(current_arrow_pos_m,0);
			} else if ((Bdirect == U_B)) {
			OLED_erase_arrow(current_arrow_pos_m,0);
			if (current_arrow_pos_m <= 3) {
				current_arrow_pos_m = 5;
				} else {
				current_arrow_pos_m -= 2;
			}
			OLED_print_arrow(current_arrow_pos_m,0);
			} else if ((Bdirect == R_B)) {
			//currentMenu = getMenu(current_arrow_pos_m);
			} else if ((Bdirect == L_B)) {
			menu_main_draw();
			currentMenu = m_menu;
		}
		return currentMenu;
}

void menu_main_draw() {
	OLED_reset();
	OLED_pos(0,0);
	OLED_print_string("Main Menu");
	OLED_pos(2,15);
	OLED_print_string("Start Game"); //Position 0
	OLED_pos(3,15);
	OLED_print_string("Select Player"); //Position 1
	OLED_pos(4,15);
	OLED_print_string("Set brightness"); //Position 2
	OLED_draw_pikachu(4,90);	
}

menu getMenu(uint8_t menu_row) {

	menu currentMenu1;
	if ( menu_row == 2) {
		menu_start_game();
		currentMenu1 = m_start_game;
	} else if ( menu_row == 3) {
		menu_select_player();
		currentMenu1 = m_select_player;
	} else if ( menu_row == 4) {
		menu_set_brigthness();
		currentMenu1 = m_set_brigthness;
	} else {
		menu_main();
		currentMenu1 = m_set_brigthness;
	}
	return currentMenu1;
}

void menu_set_brigthness() { //State 2
	OLED_reset();
	OLED_pos(0,0);
	OLED_print_string("Select Brightness");
	OLED_print_arrow_left(1,0);
	OLED_pos(1,10);
	OLED_print_string("Back to Main Menu");
}

void menu_select_player() { //State 3
	OLED_reset();
	OLED_pos(0,0);
	OLED_print_string("Select player");
	OLED_print_arrow_left(1,0);
	OLED_pos(1,10);
	OLED_print_string("Back to Main Menu");
	OLED_pos(3,15);
	OLED_print_string("1 Player");
	OLED_pos(5,15);
	OLED_print_string("2 Player");
}

void menu_start_game() { //State 4
	OLED_reset();
	OLED_pos(0,0);
	OLED_print_string("Play");
	OLED_print_arrow_left(1,0);
	OLED_pos(1,10);
	OLED_print_string("Back to Main Menu");
}



