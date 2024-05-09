#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>
#define SS PB4
#include"uart.h"

void SPI_init(){

	DDRB|= (1<<PB5)|(1<<PB7)|(1<<SS);//mosi,sck,ss
	SPCR|= (1<<SPE)|(1<<MSTR)|(1<<SPR0);

}

void SPI_TX(char data){

	SPDR= data;
	while(!(SPSR&(1<<SPIF)));// waite interrup
}
char SPI_RX(){

	SPDR=0xff;
	while(!(SPSR&(1<<SPIF)));// waite interrup
	return SPDR ;

}
void readFlashMemory(uint32_t address, uint8_t* data, uint16_t len) {
	// Select Flash memory chip
	PORTB &= ~(1 << SS);

	// Send READ command (opcode: 0x03) and 24-bit address
	SPI_TX(0x03);                      // READ command
	SPI_TX((address >> 16) & 0xFF);    // MSB of address
	SPI_TX((address >> 8) & 0xFF);     // Middle part of address
	SPI_TX(address & 0xFF);            // LSB of address

	// Read data
	for (uint16_t i = 0; i < len; i++) {
		data[i] = SPI_RX();
	}

	// Deselect Flash memory chip
	PORTB|= (1 << SS);
}


int main(void){



	UART_init();
	SPI_init();
	uint8_t idh;
	uint8_t idl;

	uint8_t idm;
	//uint8_t data[256];

	char s[20];
	char s1[20];
	char s2[20];

	char s4[20];


	uint16_t k;
	uint8_t data[256];
	SPCR|=(1<<CPOL)|(1<<CPHA);
	while(1){


		PORTB&=~(1<<SS);

		SPI_TX(0x9F);
		idh= SPI_RX();
		sendstring("Manufacturer id - ");
		sprintf(s,"id:%d\n",idh);
		sendstring(s);

		idm= SPI_RX();
		sendstring("Memory Type id - ");

		sprintf(s1,"id:%d\n",idm);
		sendstring(s1);

		idl= SPI_RX();

		sendstring("Capacity - ");


		sprintf(s2,"id:%d\n",idl);

		sendstring(s2);
		PORTB|=(1<<SS);

		sendstring("\n---clear page-------\n");
		PORTB&=~(1<<SS);

		SPI_TX(0x06);

		PORTB|=(1<<SS);


		PORTB&=~(1<<SS);
		SPI_TX(0xC7);

		PORTB|=(1<<SS);


		sendstring("\n---read data in function----\n");
		readFlashMemory(0x000000, data, sizeof(data));


		sprintf(s4,"data:%d\n",data[k]);

		sendstring(s4);
	}
	return 0;

}