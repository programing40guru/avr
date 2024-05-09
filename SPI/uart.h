#include<avr/io.h>
#include<util/delay.h>
#define cpu 8000000UL
#define baud_prescale (((cpu/(16UL*9600)))-1)

void UART_init(){

        UCSRB|=(1<<RXEN)|(1<<TXEN); // enabel tx an rx
        UCSRC|= (1<<UCSZ0)|(1<<UCSZ1); // set bute 8 
        UBRRL= baud_prescale;   // loaf low 8 bit
        UBRRH= (baud_prescale>>8); //load hight 8 bit
}

void TX_ch(char data){

        while(!(UCSRA&(1<<UDRE))); // wait  data resister empty buffer
        UDR= data;
}

unsigned char RX_ch(){
        while((UCSRA&(1<<RXC))==0);
        return(UDR);

}

void sendstring(char *str){

        unsigned int i =0;
        while(str[i]!=0){


                TX_ch(str[i]);
                i++;
        }

}



