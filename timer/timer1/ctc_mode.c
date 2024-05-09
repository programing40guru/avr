#include<avr/io.h>
void timer1_init(){

	TCCR1B= (1<<WGM12)|(1<<CS10)|(1<<CS12); //enavale ctc mode and 1024 prescaler
	TCNT1=0; //initial couter
	OCR1B=7812; //1 secound 8 mhz 


}

int main(){
	DDRB=0xff;

	timer1_init();
	while(1){
		if(TIFR & (1<<OCF1B))
		{	
			TCNT1 = 0;
			PORTB=~(PORTB);
			//clear flage
			TIFR|= (1<<OCF1B); //clear flag
		}

		}
	}
