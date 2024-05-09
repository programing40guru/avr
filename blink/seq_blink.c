#include<avr/io.h>
#include<util/delay.h>
#define F_CPU 8000000

int main(void)
{
DDRB = 0xff;

while(1)
{
	for(int i=0;i<9;i++)
	{
		PORTB|=(1<<i);
		_delay_ms(500);   
	}
       for(int i=9;i>0;i--)
{
    PORTB&=~(1<<i);
    _delay_ms(1000);
      
    }
PORTB=0x00;
_delay_ms(500);
}
}

