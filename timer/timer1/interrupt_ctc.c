#include<avr/io.h>
#include<avr/interrupt.h>

ISR(TIMER1_COMPB_vect){
	OCR1B=3906;

	PORTB=~(PORTB);
	TCNT1=0;
}

void timer1_init(void){
	TCCR1B|=(1<<WGM12);//enabal mode ctc
	TCCR1B|= (1<<CS10)|(1<<CS12); //prescaler 1025
	TCNT1=0;
	OCR1B= 3906;
	//initial calue
	TIMSK|=(1<<OCIE1B);
	sei();
}

int main(){


	DDRB=0xff;
	timer1_init();
	while(1){
	}
}
