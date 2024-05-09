PROJECT?=ctc_mode
SOURCES=$(PROJECT).c 
MMCU=atmega16
F_CPU = 8000000
 
CFLAGS=-mmcu=$(MMCU) -Wall -Os -DF_CPU=$(F_CPU)
 
$(PROJECT).hex: $(PROJECT).out
	avr-objcopy -O ihex $(PROJECT).out $(PROJECT).c.hex
	avr-size --mcu=$(MMCU) --format=avr $(PROJECT).out
 
$(PROJECT).out: $(SOURCES)
	avr-gcc $(CFLAGS) $(SOURCES) -o $(PROJECT).out
 
program-usbasp-fuses: $(PROJECT).hex
	avrdude -c usbasp -p m16 -U lfuse:w:0xe4:m -U hfuse:w:0x99:m
 
program-usbasp: $(PROJECT).hex
	avrdude -c usbasp-clone -p m16 -U flash:w:$(PROJECT).c.hex
