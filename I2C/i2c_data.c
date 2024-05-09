#include <avr/io.h>
#include<util/twi.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "i2c.h"



int main(void)
{
	PORTC =0xFF;	
   i2c_init();

   UART_init();
   i2c_start();
       TX_ch('m');
   i2c_TX(0xA6);
   i2c_TX(0x31);
   i2c_read(0x0B);
   i2c_stop();
   
   i2c_start();
   i2c_TX(0xA6);
   i2c_TX(0x2D);
   i2c_read(0x08);
   i2c_stop();
   
   i2c_start();
   i2c_TX(0xA6);
   i2c_TX(0x2E);
   i2c_read(0x80);
   i2c_stop();
   TX_ch('e');

   // Read Device ID
    char ID[50];
    char ss[20];
    char Y[50];
    char Z[50];
   uint8_t d;
  char s[50];
    while (1) {

	    
i2c_start();
	    i2c_TX(0xA6);
 	    i2c_TX(0x00);
	    i2c_stop();
             
            i2c_start();
            i2c_TX(0xA7);
            d= i2c_read();
           sprintf(s,"id:%d\n",d);
          sendstring(s);
             i2c_stop();
i2c_start();
i2c_TX(0xA6);
i2c_TX(0x32);
i2c_stop();

i2c_start();
i2c_TX(0xA7);
int8_t x0 = i2c_read();
	    int8_t x1 = i2c_read();
	    int8_t y0 = i2c_read();
	    int8_t y1 = i2c_read();
	    int8_t z0 = i2c_read();
	    int8_t z1 = i2c_nread();
int16_t x = x0 | (x1 <<8);
int16_t y = y0 | (y1 <<8);
int16_t z = z0 | (z1 <<8);

sprintf(ss,"x- axi :%d\n",x);
sprintf(Y,"y- axi :%d\n",y);
sprintf(Z,"z- axi :%d\n",z);

sendstring(ss);
sendstring(Y);
sendstring(Z);

}

    return 0;
}


