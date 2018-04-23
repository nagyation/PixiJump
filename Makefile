MCU=atmega32
CFLAGS=-g -Wall -mcall-prologues -mmcu=$(MCU) -Os
LDFLAGS=-Wl,-gc-sections -Wl,-relax
CC=avr-gcc
SOURCES= lcd.c DIO.c mechanism.c map.c main.c 
OBJECTS=$(SOURCES:.c=.o)
ELF=$(SOURCES:.c=.elf)
HEX = main.hex

all: $(HEX)

clean:
	rm -f *.o *.elf *.hex

$(HEX): $(ELF)
	avr-objcopy -R .eeprom -O ihex $< $@

$(ELF): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS)  -o $@

upload: $(HEX)
	avrdude -c usbasp  -p $(MCU) -U flash:w:$<:i

