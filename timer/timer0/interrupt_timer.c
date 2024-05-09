#include<avr/io.h>
#include<avr/interrupt.h>
#define f_CPU 8000000
#include<util/delay.h>

int count;
ISR(TIMER0_OVF_vect){
TCNT0=216;
count++;
if(count==100){
PORTB=~PORTB;
count =0;
}

}
int main(){
	DDRB=0xff; // output
	PORTB=0xff;
       
	PORTD=0xff; //ective hight pull up
	TCNT0=216;
	TCCR0|=(1<<CS02)|(1<<CS00); // set prescaler to 1024
	TIMSK|= (1<<TOIE0);// enabal timer0 overflow interupes
		//GICR=1<<INT0; //entrupt enabal int0
	MCUCR= (1<<ISC01)|(1<<ISC00);
  

        sei();
	while(1);	

}
