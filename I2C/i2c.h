#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define F_SCL 100000UL
void i2c_init() {
	TWBR = ((F_CPU/F_SCL)-16)/2; 
}

void i2c_start() {
	TWCR = (1<<TWSTA) | (1<<TWEN) | (1<<TWINT); // Send start condition
	while (!(TWCR & (1<<TWINT)));  
}

void i2c_stop() {
	TWCR = (1<<TWSTO) | (1<<TWEN) | (1<<TWINT); // Send stop condition
}

void i2c_TX(uint8_t data) {
	TWDR = data;  
	TWCR = (1<<TWEN) | (1<<TWINT);  
	while (!(TWCR & (1<<TWINT)));  
}
uint8_t i2c_read()
{
    TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);

    while (!(TWCR & (1 << TWINT)));

    return TWDR;
}

uint8_t i2c_nread()
{
    TWCR = (1<<TWEN) | (1<<TWINT);

    while (!(TWCR & (1 << TWINT)));

    return TWDR;
}
