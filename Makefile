PRG            = incubator
OBJ            = main.o test.o lcd.o hardware.o state.o delay.o init.o dht22.o
MCU_TARGET     = atmega2560
OPTIMIZE       = -O2

DEFS           =
LIBS           =  test.h lcd.h hardware.h state.h delay.h init.h dht22.h

# You should not have to change anything below here.
CC             = avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS        =   -g -std=c99 -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)  -v -v -v
override LDFLAGS       = -Wl,-Map,$(PRG).map

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all: $(PRG).elf lst text eeprom

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# dependency:
main.o: 	main.c
init.o: 	init.c
state.o: 	state.c
hardware.o: 	hardware.c types.h
lcd.o: 		lcd.c types.h
delay.o:  	delay.c
dth22.o: 	dht22.c
test.o:		test.c

AVRDUDE_PROGRAMMER = wiring
AVRDUDE_PORT=/dev/ttyACM0
AVRDUDE_WRITE_FLASH = -U flash:w:$(PRG).hex
AVRDUDE_VERBOSE= -v -v
AVRDUDE_BASIC= -p $(MCU_TARGET) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -D
AVRDUDE_FLAGS= $(AVRDUDE_BASIC) $(AVRDUDE_VERBOSE) 
AVRDUDE= avrdude


clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak 
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

eeprom: ehex ebin esrec

ehex:  $(PRG)_eeprom.hex
ebin:  $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ \
	|| { echo empty $@ not generated; exit 0; }

%_eeprom.srec: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@ \
	|| { echo empty $@ not generated; exit 0; }

%_eeprom.bin: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@ \
	|| { echo empty $@ not generated; exit 0; }

# Every thing below here is used by avr-libc's build system and can be ignored
# by the casual user.

FIG2DEV                 = fig2dev
EXTRA_CLEAN_FILES       = *.hex *.bin *.srec

dox: eps png pdf

eps: $(PRG).eps
png: $(PRG).png
pdf: $(PRG).pdf

%.eps: %.fig
	$(FIG2DEV) -L eps $< $@

%.pdf: %.fig
	$(FIG2DEV) -L pdf $< $@

%.png: %.fig
	$(FIG2DEV) -L png $< $@

#Program the device
#install: $(PRG).hex  $(AVRDUDE) $(AVRDUDE_FLAGS)  $(AVRDUDE_WRITE_FLASH)
