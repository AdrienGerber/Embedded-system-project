typedef struct JoyPos {
	float x;
	float y;
}joyposition;

enum directions {LEFT, RIGHT, UP, DOWN, NEUTRAL};
joyposition getAnalogPosition(float horizontal_voltage, float vertical_voltage);
int getJoystickDirection(float horizontal_voltage1, float vertical_voltage1, float horizontal_voltage2, float vertical_voltage2); //0.Left 1.Right 2.Down 3.Up 4.Neutral