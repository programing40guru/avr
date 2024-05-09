#include <avr/io.h>
 
#define F_CPU 8000000
#include <util/delay.h>
 
 
int main(void)
{
       DDRB = 0Xff;     //0000 0111
        while (1)
        {
               // hhh:x
                LED on/off    
#if 1
                PORTB = 0x01; // 0000 0001
                _delay_ms(1000);
                PORTB =  0X03; // //0000 0010
                _delay_ms(1000);
                PORTB = 0X7;
                _delay_ms(1000);
                PORTB=0X0f;
                _delay_ms(1000);
                 PORTB = 0X1f; // 0000 0001
                  _delay_ms(1000);
                  PORTB =  0X3f; // //0000 0010
                  _delay_ms(1000);
                 PORTB = 0X7f;
                  _delay_ms(1000);
                  PORTB=0Xff;
                  _delay_ms(1000);
                  PORTB=0X00;
                  _delay_ms(1000);
#else
                        // Switch iNput
                if (!(PINA & 0x80)) //  PINA & 1000 000==0
                {
                        PORTA |= 0X02;
                }
                else
                {
                        PORTA = 0X00;
                }
#endif
        }
}
