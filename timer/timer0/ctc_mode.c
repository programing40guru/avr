#include<avr/io.h>
#include<avr/interrupt.h>
volatile uint8_t tot_overflow;

void timer_init(void){
	// set up timer CtC mode enabal and prescaler
	TCCR0=(1<<WGM01); //enabal ctc 
	TCCR0|=(1<<CS00)|(1<<CS02); //prescanaler
	TCNT0=0; //initial value 
        
 tot_overflow++;
 if(tot_overflow>=10){
 OCR0=39;//50 ms timer output comaper register value set 39 eith math TCNT0
tot_overflow=0;
}
         

//	OCR0=39;//50 ms timer output comaper register value set 39 eith math TCNT0
	TIMSK|=(1<<OCIE0);// enavale global interup 
		sei();
}

ISR(TIMER0_COMP_vect){
	PORTB=~(PORTB);
}

int main(void){

	DDRB=0xff;
	timer_init();
	while(1)
	{}


}
