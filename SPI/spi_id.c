//#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>			
#include <string.h>
#define MOSI PB5
#define SCK PB7
#define SS PB4
#define MISO PB6
#include"uart.h"
void SPI_init()					/* SPI Initialize function */
{

	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);	/* Make MOSI, SCK, SS 
						   as Output pin */
//	DDRB &= ~(1<<MISO);			/* Make MISO pin 
//	as input pin */
	//	PORTB |= (1<<SS);			/* Make high on SS pin */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	
}

void SPI_TX(char data){
	SPDR=data;

	while(!(SPSR&(1<<SPIF)));
}


char SPI_RX()				/* SPI read data function */
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}

int main(){
	UART_init();
	SPI_init();
	char s1[20];
	
	
	uint8_t i;

   SPCR |= (1<<CPHA)|(1<<CPOL);

	
	while(1){
		PORTB&=~(1<<SS);     
		SPI_TX(0x80);

		i= SPI_RX();
		sprintf(s1,"id : %d\n",i);
		sendstring(s1);
		PORTB|=(1<<SS);
	}
}

