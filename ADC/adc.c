
#include<avr/io.h>
#include"uart.h"
#include<util/delay.h>
void ADC_init(){

	DDRA= 0x00; // make adc portbinput
	ADCSRA=0x87; // 7 st bit 1 enabale adc , 111 = 128 pre claer + hezadesimal = 87 value 
	ADMUX= 0x40;//   (  1<<REFS0)= 5volt extenal camaitor 01000000
}

int ADC_read(char chanal){

	int AH,AL;
	ADMUX= ADMUX|(chanal&0x0f);
	ADCSRA|=(1<<ADSC); //start convezesion
	while(ADCSRA&(1<<ADSC)); //interrupt flag monitor end
    _delay_ms(100);			   //data ADC Conversion Complete Interrupt is activated.
	

	AL= (int)ADCL;//read lower bite
	AH= (int)ADCH*256; //read hoght bits and multiples
	AH=AH+AL;
 
	return (AH);
}

int main(void){
	UART_init();

	DDRB=0xff;
	int value ;
           int volt;
	ADC_init();
	char s[4];	
       char s1[4];
	while(1){

		TX_ch('\n');	
		value = ADC_read(0);
		sprintf(s,"%d",value);
              TX_ch('\n');
                sendstring(s);

                if(value>=10&&value<=40){
      
              PORTB=0x1;

}
 else if(value>40&&value<80) {
PORTB= 0x03;
}
else if(value>=80&&value<120) {     PORTB= 0x07;}
else if(value>=120&&value<150) {   PORTB= 0x0f;}

else if(value>=150&&value<180) { PORTB=0x1f; }


else if(value>=180&&value<220) { PORTB= 0x3f;}


else if(value>=220&&value<300) { PORTB= 0x7f;}


else if(value>=300&&value<500) { PORTB=0xff; }
else if(value>=500&&value<800) { PORTB=0x055; }
else if(value>=800&&value<1000) { PORTB=~(0x55); }
else if(value>=1000) { PORTB= 0xf0;}
else{

PORTB=0x86;
}
sendstring("\n---2.5: volt----:");
volt= (2.5*value)/5;
sprintf(s1,"%d",volt);
sendstring(s1);





	}
}
