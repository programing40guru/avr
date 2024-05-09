#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
int main(void)
{
    	DDRA=0xff;
        DDRC=0x00;
	while (1)
	{
		
	 
	PORTC = 0x02;	
                 if(!(PINC & 0x02)) // chake pin c( notes --) jampar chanhet portd to port c then c pin chake 

		{
			PORTA=0x0f;
		}
		else
		{
			PORTA = 0Xf0;
                                                                                                                       
		}
	}
}
