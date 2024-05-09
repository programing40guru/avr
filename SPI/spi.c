#include<avr/io.h>
#include<stdio.h>
#include<util/delay.h>
//#define cpu 8000000UL
//#define baud_pre ((cpu/(9600*16UL))-1)
#include"uart.h"
#define SS PB4

void enable()
{
	PORTB&=~(1<<SS);// desable 
}
void disable()
{
	PORTB|=(1<<SS);  

}
void SPI_init(){

	DDRB= (1<<DDB5)|(1<<DDB7)|(1<<DDB4);// make mosi ,sck,ss output other input 
					    //	DDRB&= ~(1<<MISO);// miso make input

	SPCR = (1<<SPE)|(1<<MSTR)|(1<SPR0); //enaBLE spi enabal and master silect bit (enbale) 
					    // spi clock rate 0 cpu/4;
}

void SPI_TX(char data){


	SPDR = data; //start transmiting bye spi data register
	while(!(SPSR&(1<<SPIF)));// waite status register interrupt falg

}


char SPI_RX(){

	SPDR= 0xFF;
	while(!(SPSR&(1<<SPIF)));

	return SPDR;
}


void x0_x1(){
	uint8_t x0l;
	uint8_t x0m;
	uint16_t x;
	

	char s0[20];
	
	enable();	
	SPI_TX(0xF2);
	x0l= SPI_RX();
	x0m= SPI_RX();

	x= (x0m<<8)|x0l;
 disable();



	sprintf(s0 ,"x: %d\n",x);
	sendstring(s0);


}


void y0_y1(){
	uint8_t y0l;
	uint8_t y0m;
	uint16_t y;
	


	char s1[20];
	
	enable();	
	SPI_TX(0xF4);
	y0l= SPI_RX();
	y0m= SPI_RX();


	y= (y0m<<8)|y0l;

	disable();


	sprintf(s1 ,"y: %d\n",y);
	sendstring(s1);


}


void z0_z1(){
	uint8_t z0l;
	uint8_t z0m;
	uint16_t z;



	char s3[20];


	enable();	
	SPI_TX(0xF6);
	z0l= SPI_RX();
	z0m= SPI_RX();

	z= (z0m<<8)|(z0l);
    disable();

	sprintf(s3 ,"z: %d\n",z);
	sendstring(s3);


}

int main(){
	UART_init();

	SPI_init();

	SPCR|= (1<<CPOL)|(1<<CPHA);
	uint8_t data;

	char s[20];


	enable();	
	SPI_TX(0x31);
	SPI_TX(0x0B);
	disable();

	enable();	
	SPI_TX(0x2D);
	SPI_TX(0x08);
	disable();

	enable();	
	SPI_TX(0x2E);
	SPI_TX(0x80);
	disable();



	while(1){


		enable();	
		SPI_TX(0x80);
		data= SPI_RX();
		disable();

		sprintf(s ,"id-%d\n",data);
		sendstring(s);
     
		// x0 
		x0_x1() ;
 

		// y
	y0_y1() ;

		// z 
  z0_z1() ;
_delay_ms(300);


	}

	return 0;

}
