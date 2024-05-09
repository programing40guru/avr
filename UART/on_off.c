#include<avr/io.h>
#define cpu 8000000UL
#define baud ((cpu/(16UL*9600))-1)

void init(unsigned int uab){
	UCSRB|= (1<<RXEN)|(1<<TXEN);
	UCSRC|=(1<<UCSZ0)|(1<<UCSZ1);
	UBRRL= baud;
	UBRRH= (baud>>8);

}

void TX(char data){
	while(!(UCSRA&(1<<UDRE))) ;// data registe emty buster waite
	UDR= data;

}

unsigned char  RX(){
	while((UCSRA & (1<<RXC))==0); // wait data rx complert 
	return (UDR);
}

void sendstring(char *str)
{
	unsigned char j=0;

	while (str[j]!=0)	
	{
		TX(str[j]);	
		j++;
	}
}

int main(void){
	DDRB= 0xff;
	//PORTB= 0xff;
	init(9600);
	while(1){
		unsigned char c[2];
		
		for(int i=0;i<2;i++){
			c[i]= RX();


		}
                   
		for(int i=0;i<2;i++){
                       TX(c[i]);
                         TX('\n');

			if((c[0]=='o')&&(c[1]=='n')){

				PORTB=0xff;
				//TX(c[i]);
			}
			else if ((c[0]=='o')&&(c[1]=='f')){

				PORTB= 0x00;
				//TX(c[i]);
			}


		}
	}
}

