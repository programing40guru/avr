#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#define F_CPU 8000000

ISR(INT1_vect){
	PORTB=0x03;
	_delay_ms(1000);
        PORTB=0x00;
}
ISR(INT0_vect){
	PORTB=0x0f;
	_delay_ms(1000);//deddde:x
        PORTB=0x00;
       
}
int main(){
	DDRB=0XFF; //output port

    PORTD=0XFF; // pull up 
     //	PORTB=0x55;  //1010101010  output
     //	DDRA=0x00; //input port

cli(); //disable  global interrupt
GICR|=1<<INT1| 1<<INT0;
MCUCR|= (1<<ISC11 | 1<<ISC10)|(1<<ISC01|1<<ISC00); // rising INT0 and INT! 
sei();
while(1);		}
