#include<avr/io.h>
#include<avr/interrupt.h>
#define F_CPU 8000000

ISR(TIMER0_OVF_vect){

PORTB=~(PORTB);
TCNT0=0;

}
void timer_init(){

	//set up prescaler = 1024
	TCCR0|= (0<<CS01)|(1<<CS00)|(1<<CS02);
	//initialize couter
	TCNT0=0;
}

int main(void){
	DDRB= 0x03 ; 
         PORTB=0x03;//connect led to pin pc0
	timer_init();  // initilize timer callerd
	while(1){

		if(TCNT0>=240){

			sei();//PORTB=~PORTB;// ^=(1<<0);
			//TCNT0=0;
		}

	}


}
