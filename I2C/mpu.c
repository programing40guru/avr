#include<avr/io.h>
#include<util/delay.h>
#include"uart.h"
#include"i2c.h"
#include<stdio.h>
int main() {
	PORTC =0xFF;	
	UART_init();
	i2c_init();
	uint8_t id;
	char s[20];
	char s1[20];
	uint16_t x;
	uint8_t hx;
	uint8_t lx ; // congiger..... start.........
	i2c_start();
	i2c_TX(0xD0);
	i2c_TX(0x19);
	i2c_TX(0x07);
	i2c_stop();



	// gyro.............
	i2c_start();
	i2c_TX(0xD0);
	i2c_TX(0x6B);
	i2c_TX(0x01);
	i2c_stop();

	// gyro.... congi.........
	i2c_start();
	i2c_TX(0xD0);
	i2c_TX(0x1A);
	i2c_TX(0x00);

	i2c_stop();
i2c_start();
	i2c_TX(0xD0);
	i2c_TX(0x1B);
	i2c_TX(0x18);

	i2c_stop();

	// init enabale.........
	i2c_start();
	i2c_TX(0xD0);
	i2c_TX(0x38);
	i2c_TX(0x01);

	i2c_stop();
	while(1){
		
		   i2c_start();
		   i2c_TX(0xD0);
		   i2c_TX(0x75);
		   i2c_stop();

		   i2c_start();
		   i2c_TX(0xD1);
		   id= i2c_nread();
		   i2c_stop();
		   sprintf(s,"Id :0x%x\n",id);
		   sendstring(s);
	//	_delay_ms(100);
                 i2c_start();

		i2c_TX(0xD0);
		i2c_TX(0x43);
		i2c_stop();
		i2c_start();
		i2c_TX((0xD1));

		hx= i2c_read();
		lx= i2c_nread();
		i2c_stop();              
		x= ((lx<<8)|hx);
		sprintf(s1,"x:%d\n",x);
		sendstring(s1);




	}
return 0;
}



