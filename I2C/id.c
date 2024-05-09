#include<stdio.h>
#include<avr/io.h>
#include<util/delay.h>
#define CPU 8000000UL
#define SCL 1000000UL
#define TT (((CPU/SCL)-16)/2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))
#include"uart.h"
void i2c_init(){
	TWBR = TT;
	//	TWCR = (1<<TWEN);
}

void i2c_start(){
	TWCR|= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);// int, strat ,en
	while(!(TWCR&(1<<TWINT))); //wait start flage with int
}


void i2c_add(uint8_t add){
	TWDR=add;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT))); //ack hav been resive tx sLA +W transimi
} 

void i2c_TX(uint8_t data){
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN); //load data , twint bit clear strat transimisuin

}

char i2c_ack(){
	TWCR = (1<<TWINT) | (1<<TWEN)|(1<<TWEA);//ack ok site
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

char i2c_nack(){
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

void i2c_stop(){
	TWCR=(TWINT)|(1<<TWEN)|(1<<TWSTO);

	//    while ((TWCR & (1 << TWSTO)));

}

int main(void){
	uint8_t d;
	char s[20];
	UART_init();

	i2c_init();
	while(1){
		i2c_start();
		i2c_add(0x1D<<1);// Send device address  to write oo
		

		i2c_TX(0x00);
	      i2c_stop();
	
  _delay_ms(100);		
		//read data 
          i2c_start();
		

		i2c_add((0x1D<<1)|1);//read data
		d= i2c_nack();
		i2c_stop();
		sprintf(s,"id : %d\n",d);
		sendstring(s);


	}
	return 0;
}
