#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>
#include<stdlib.h>
#define F_CPU 8000000UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/((USART_BAUDRATE )*16UL)))-1)


void UART_init(unsigned int ubr){


	UCSRB|=(1<<RXEN)|(1<<TXEN); // enbale usart control status b enaale tx and rx
	UCSRC|= (1<<UCSZ1)|(1<<UCSZ0); // must URSEL register silect 8 bit size
	UBRRL=BAUD_PRESCALE;  // load  baud rate resister lower 8bit
	UBRRH= (BAUD_PRESCALE>>8);// load upper 8 bit

}

void UART_tx_char(unsigned char data){
	while(!(UCSRA&(1<<UDRE))); // wjaite data register empty
	UDR= data;
}

int main()
{
	UART_init(9600);
	while(1){
	
		UART_tx_char('M');
                
		UART_tx_char('\n');
                
		_delay_ms(1000);
	}
	return 0;
}
