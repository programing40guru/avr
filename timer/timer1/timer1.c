#include<avr/io.h>

#include<avr/interrupt.h>
int tot_over;
//every 2 s frquin .5 hz xtal of 16 Mhz
void timer1_init(){
	TCCR1B|=(1<<CS10)|(1<<CS12);//set upprescale 8 
	TCNT1=65514;
	TIMSK|=(1<<TOIE1);
	sei();

}

ISR(TIMER1_OVF_vect){

	TCNT1=65513;

	tot_over++;

	static int i=0;
	if(tot_over==20){

		if(i<7){
			PORTB=~(1<<i);
                        PORTD=(1<<i);
			tot_over=0;
			i++;
		}
		else if(i==7){
			PORTB=(1<<i);
                       PORTD=(1<<i);
			tot_over=0;
			i=0;
		}
	}

}

int main(void){
	DDRB=0xff;
         DDRD=0xff;
	//    PORTB=0x00;
	//  TCNT1=216;
	timer1_init();

	while(1){
	}
}
