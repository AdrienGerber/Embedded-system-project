typedef struct JoyPos {
	float x;
	float y;
}joyposition;

void JOY_init(void);
typedef enum{LEFT, RIGHT, UP, DOWN, NEUTRAL}directions;
//joyposition getAnalogPosition(float horizontal_voltage, float vertical_voltage);
joyposition getAnalogPosition(void);
int getJoystickDirection2(void); //0.Left 1.Right 2.Down 3.Up 4.Neutral
directions getJoystickDirection(void);
int left_button(void);
int right_button(void);
uint8_t right_slider(void);
uint8_t left_slider(void);