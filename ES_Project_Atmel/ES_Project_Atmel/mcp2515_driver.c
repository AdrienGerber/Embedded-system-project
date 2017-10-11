#define F_CPU 16000000

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "mcp2515_driver.h"
#include "spi_driver.h"


void mcp2515_init(){
	/*uint8_t value;
	
	SPI_init(); //Initialize SPI	
	mcp2515_reset();
	
	mcp2515_bit_modify(MCP_CANSTAT, 0xE0, 0x80); //Set configuration mode
	//Self-test
	mcp2515_read(MCP_CANSTAT);
	if((value && MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset! \n");
		return 1;
	}
	
	return 0;*/
	
	SPI_init();
	mcp2515_reset();
	
	//Interruption when message received on RX0 and RX1
	mcp2515_bit_modify(MCP_CANINTE, 0xFF,0x00); 
	mcp2515_bit_modify(MCP_CANINTE, 0x03,0xFF);
	
	//Set mode normal
	//mcp2515_bit_modify(MCP_CANCTRL, 0XE0, MODE_NORMAL);
	
	//Set loopback mode
	mcp2515_bit_modify(MCP_CANCTRL, 0XE0, MODE_LOOPBACK);
}

uint8_t mcp2515_read(uint8_t address){
	uint8_t data;
	
	SPI_enable(); //Select the CAN-controller by lowering CS
	SPI_write(MCP_READ); //READ instruction
	SPI_write(address); //Send address
	data=SPI_read();
	
	SPI_disable(); //Unselect the CAN-controller by uppering CS
	
	return data;
}

void mcp2515_write(uint8_t address, uint8_t data){
	SPI_enable(); //Select the CAN-controller by lowering CS
	SPI_write(MCP_WRITE); //WRITE instruction
	SPI_write(address); //Send address
	SPI_write(data); //Send data
	
	SPI_disable(); //Unselect the CAN-controller by uppering CS
}

void mcp2515_request_to_send(char tx_addr){ //INPUT are 0 or 1
		
	SPI_enable(); //Select the CAN-controller by lowering CS
	
	SPI_write(tx_addr);
	
	SPI_disable(); //Unselect the CAN-controller by uppering CS
	
}

void mcp2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data){
	
	SPI_enable(); //Select the CAN-controller by lowering CS
	SPI_write(MCP_BITMOD); //Bit modify instruction
	SPI_write(adress);
	SPI_write(mask);
	SPI_write(data);
	SPI_disable(); //Unselect the CAN-controller by uppering CS
	
}

void mcp2515_reset(){
	SPI_enable(); //Select the CAN-controller by lowering CS
	
	SPI_write(MCP_RESET); //RESET instruction
	
	SPI_disable(); //Unselect the CAN-controller by uppering CS
}

uint8_t mcp2515_read_status(){
	uint8_t data;
	
	SPI_enable(); //Select the CAN-controller by lowering CS
	
	SPI_write(MCP_READ_STATUS); //Read status instruction
	data=SPI_read();
	
	SPI_disable(); //Unselect the CAN-controller by uppering CS
	
	return data;
}
