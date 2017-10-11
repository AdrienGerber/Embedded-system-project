typedef struct JoyPos {
	float x;
	float y;
}joyposition;

void JOY_init(void);

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL,
	R_N
} directions;

typedef enum {
	L_B,
	R_B,
	U_B,
	D_B,
	N_B
} directionsButton;


joyposition getAnalogPosition(void);

directions getJoystickDirection();

directionsButton getJoystickDirectionButton();

//direction_button getJoystickDirectionButton(void);

int left_button(void);
int right_button(void);

uint8_t right_slider(void);
uint8_t left_slider(void);

