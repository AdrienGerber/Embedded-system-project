#define F_CPU 16000000

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "mcp2515_driver.h"
#include "spi_driver.h"
#include "can_driver.h"

/*

#define MCP_CANINTE	0x2B
#define MCP_CANINTF	0x2C*/


void CAN_init(){
	mcp2515_init();
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK); //NORMAL OR LOOPBACK
	mcp2515_bit_modify(MCP_CANINTE, 0x01, 0x01);
	
}

void CAN_send(can_message* message){
	// Wait while the previous message is not sent
	while(((1 << 0x3) & mcp2515_read(MCP_TXB0CTRL)));
	
	/*
	mcp2515_bit_modify(MCP_TXB0SIDL, 0xE0, (message->id & 0x07) << 5);
	mcp2515_write(MCP_TXB0SIDH, (message->id & 0xFFF8) >> 3);
	mcp2515_bit_modify(MCP_TXB0SIDL, 0xE0, (message->id & 0x07) << 5);
	*/
	
	mcp2515_write(MCP_TXB0CTRL + 1, message->id);
	mcp2515_write(MCP_TXB0CTRL + 2, 0x00);
	
	
	mcp2515_write(MCP_TXB0CTRL + 5, message->length);
	
	uint8_t i;
	for (i = 0; i < message->length; i++)
	{
		mcp2515_write(MCP_TXB0CTRL + 6 + i, message->data[i]);
	}
	
	mcp2515_request_to_send(MCP_RTS_TX0);
}


can_message CAN_receive()
{
	/* Check if there is a message */ 
	while(mcp2515_read(MCP_CANINTF) & 0x01 != 0x1){;}
		
	can_message message;
	message.id = ((mcp2515_read(MCP_RXB0SIDH) << 0) + ((mcp2515_read(MCP_RXB0SIDL) >> 5) & 0x7)) & 0xFF;
		
	message.length =  mcp2515_read(MCP_RXB0DLC) & 0x0F;
		
	for (int i=0; i < message.length || i < 8; i++)
	{
		message.data[i] = mcp2515_read(MCP_RXB0D0+i);
	}
		
	mcp2515_bit_modify(MCP_CANINTF,0x01,0x00);
		
	return message;

}

/*
can_message CAN_receive(){
	can_message message;
	uint8_t buffer_in_use = CAN_transmit_complete();
	
	// if there is no message to read we leave the function
	if(buffer_in_use == -1){return;}
	
	message.id = mcp2515_read(MCP_RXB0CTRL + buffer_in_use + 1);
	
	message.length = mcp2515_read(MCP_RXB0CTRL + buffer_in_use + 5);
	
	uint8_t i;
	for(i = 0; i < message.length; i++)
	{
		message.data[i] = mcp2515_read(MCP_RXB0CTRL + buffer_in_use + 6 + i);
	}
	
	// reset data for next transmission
	mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0x0);
	mcp2515_bit_modify(MCP_CANINTF, MCP_RX1IF, 0x0);
	
	return message;
}*/
	/*
uint8_t CAN_transmit_complete(void){

	volatile char currentdata = mcp2515_read(MCP_CANINTF);

	while((!((1 << MCP_RX0IF) & currentdata)) && (!((1 << MCP_RX1IF)& currentdata)))
	{currentdata = mcp2515_read(MCP_CANINTF);}
	
	if((1 << MCP_RX0IF) & currentdata)
	{return 0;}
	else if((1 << MCP_RX1IF) & currentdata)
	{return 16;}
	else
	{return -1;}
}*/

/*ISR(INT0_vect){
CAN_MESSAGE returnedMessage;

CAN_recieve(&returnedMessage);

if(returnedMessage.id == ID_GAME_OVER){
Game_setGameOverFlag();
}

if (returnedMessage.id == ID_GOT_NAME)
{
Game_setNameFlag();
Game_setPlayerName((char*) returnedMessage.data);
}


MCP_bitModify(MCP_CANINTF, 0xFF, 0x00);

}*/