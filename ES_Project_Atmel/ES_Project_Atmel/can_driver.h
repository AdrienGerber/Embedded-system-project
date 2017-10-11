typedef struct can_message{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
}can_message;

void CAN_init();
void CAN_send(can_message* message);
can_message CAN_receive();
uint8_t CAN_transmit_complete(void);