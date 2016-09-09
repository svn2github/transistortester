###############################################################################
# Makefile for the project TransistorTester
###############################################################################

## General Flags
MKFILES = Makefile
CC = avr-gcc

CPP = avr-g++

CFLAGS = -Wall

BAUD_RATE ?= 115200

t84: PARTNO := t84
t84: MCU := attiny84
ifndef F_CPU
t84: F_CPU := 16000000
endif
t84: upload

m8: PARTNO := m8
m8: MCU = atmega8
ifndef F_CPU
m8: F_CPU := 16000000
endif
m8: upload

m88: PARTNO := m88
m88: MCU = atmega88
ifndef F_CPU
m88: F_CPU := 16000000
endif
m88: upload

m16: PARTNO := m16
m16: MCU = atmega16
ifndef F_CPU
m16: F_CPU := 16000000
endif
m16: upload

m168: PARTNO := m168
m168: MCU = atmega168
ifndef F_CPU
m168: F_CPU := 16000000
endif
m168: upload

m168p: PARTNO := m168p
m168p: MCU = atmega168p
ifndef F_CPU
m168p: F_CPU := 16000000
endif
m168p: upload

m32: PARTNO := m32
m32: MCU = atmega32
ifndef F_CPU
m32: F_CPU := 16000000
endif
m32: upload

m328: PARTNO := m328
m328: MCU := atmega328
ifndef F_CPU
m328: F_CPU := 16000000
endif
m328: upload

m328p: PARTNO := m328p
m328p: MCU := atmega328p
ifndef F_CPU
m328p: F_CPU := 16000000
endif
m328p: upload

m644p: PARTNO := m644p
m644p: MCU := atmega644p
ifndef F_CPU
m644p: F_CPU := 16000000
endif
m644p: upload

m1284p: PARTNO := m1284p
m1284p: MCU := atmega1284p
ifndef F_CPU
m1284p: F_CPU := 16000000
endif
m1284p: upload

m1284: PARTNO := m1284
m1284: MCU := atmega1284
ifndef F_CPU
m1284: F_CPU := 16000000
endif
m1284: upload

m1280: PARTNO := m1280
m1280: MCU := atmega1280
ifndef F_CPU
m1280: F_CPU := 16000000
endif
m1280: upload


# Select your programmer type, speed and port, if you wish to use avrdude.
# setting for DIAMEX ALL_AVR, Atmel AVRISP-mkII
#PROGRAMMER=avrisp2
#BitClock=5.0
#PORT=usb
# setting for USBasp
#PROGRAMMER=usbasp
#BitClock=20
#PORT=usb
# setting for ARDUINO MEGA, requires bootloader
#PROGRAMMER=wiring
#PORT = /dev/ttyACM0
#BitClock=5.0
#AVRDUDE_BAUD = -b 115200 -D
# setting for ARDUINO MEGA, requires bootloader
PROGRAMMER=arduino

ifndef PARTNO
PARTNO = m328p
endif

ifndef PORT
PORT = /dev/ttyACM0
endif


BitClock=5.0
#AVRDUDE_BAUD = -b 115200 -D
AVRDUDE_BAUD = -b $(BAUD_RATE) -D
# ********************** end of selectable options

CFLAGS += -mcall-prologues
# you can set the EFUSE_VAL to 0xfc or to 0x04, if your avrdude mask out the unused bits


CFLAGS += -DBAUD_RATE=$(BAUD_RATE)

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS += $(COMMON)
ifdef SOFT_UART
 CFLAGS += -DSOFT_UART=$(SOFT_UART)
endif
ifdef UART
 CFLAGS += -DUART=$(UART)
endif
CFLAGS += -gdwarf-2 -std=gnu99 -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
# CFLAGS += -maccumulate-args
CFLAGS += -MD -MP -MT $(*F).o  

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
#LDFLAGS +=  -Wl,--relax,-Map=$(PARTNO)_test.map
LDFLAGS +=  -Wl,-Map=$(PARTNO)_test.map

## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature
#HEX_FLASH_FLAGS += -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = main.o wait1000ms.o soft_uart.o

## Objects explicitly added by the user
LINKONLYOBJECTS = 


## Build
#all: $(PARTNO)_test.elf $(PARTNO)_test.hex $(PARTNO)_test.eep $(PARTNO)_test.lst size

FORCE:

########### Compile only Assembler source available 

wait1000ms.o: wait1000ms.S $(MKFILES) FORCE
	$(CC) $(INCLUDES) $(CFLAGS) -DF_CPU=$(F_CPU) -c  -o $@ $<

soft_uart.o: soft_uart.S $(MKFILES) FORCE
	$(CC) $(INCLUDES) $(CFLAGS) -DF_CPU=$(F_CPU) -c -o $@  $<


########### Compile C source only 
main.o: main.c $(MKFILES) FORCE
	$(CC) $(INCLUDES) $(CFLAGS) -DF_CPU=$(F_CPU) -c -o $@  $<


##Link
$(PARTNO)_test.elf: $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(PARTNO)_test.elf

$(PARTNO)_test.hex: $(PARTNO)_test.elf
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $(PARTNO)_test.elf $(PARTNO)_test.hex

$(PARTNO)_test.eep: $(PARTNO)_test.elf
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $(PARTNO)_test.elf $(PARTNO)_test.eep || exit 0

$(PARTNO)_test.lst: $(PARTNO)_test.elf
	avr-objdump -h -S $(PARTNO)_test.elf > $(PARTNO)_test.lst

size: ${PARTNO}_test.elf
	@echo
	@echo $(F_CPU) Hz operation with Baudrate $(BAUD_RATE) configured.
	@avr-size -C --mcu=${MCU} ${PARTNO}_test.elf

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) *.elf  *.hex *.eep *.lst *.map main.d soft_uart.d wait1000ms.d


## Other dependencies


# device programming
# make fuses  call if you don't have installed a crystal

# make upload  additionally calls make to compile the software for selected target
upload: $(PARTNO)_test.hex $(PARTNO)_test.eep $(PARTNO)_test.lst size
	avrdude -c $(PROGRAMMER) -B $(BitClock) $(AVRDUDE_BAUD) -p $(PARTNO) -P $(PORT) -U flash:w:./$(PARTNO)_test.hex:a \
	-U eeprom:w:./$(PARTNO)_test.eep:a
#	avrdude -vvvv -c $(PROGRAMMER) -B $(BitClock) $(AVRDUDE_BAUD) -p $(PARTNO) -P $(PORT) -U flash:w:./$(PARTNO)_test.hex:a 
program: $(PARTNO)_test.hex
	avrdude -c $(PROGRAMMER) -B $(BitClock) $(AVRDUDE_BAUD) -p $(PARTNO) -P $(PORT) -U flash:w:./$(PARTNO)_test.hex:a \
	-U eeprom:w:./$(PARTNO)_test.eep:a
flash: $(PARTNO)_test.hex
	avrdude -c $(PROGRAMMER) -B $(BitClock) $(AVRDUDE_BAUD) -p $(PARTNO) -P $(PORT) -U flash:w:./$(PARTNO)_test.hex:a 
eeprom: $(PARTNO)_test.eep
	avrdude -c $(PROGRAMMER) -B $(BitClock) $(AVRDUDE_BAUD) -p $(PARTNO) -P $(PORT) \
	-U eeprom:w:./$(PARTNO)_test.eep:a
eeread:
	avrdude -c $(PROGRAMMER) -B $(BitClock) $(AVRDUDE_BAUD) -p $(PARTNO) -P $(PORT) \
	-U eeprom:r:./TTactual.eep:i
read:
	avrdude -c $(PROGRAMMER) -B $(BitClock) $(AVRDUDE_BAUD) -p $(PARTNO) -P $(PORT) \
	-U flash:r:./TTactual.hex:i
verify: $(PARTNO)_test.hex $(PARTNO)_test.eep
	avrdude -D -c $(PROGRAMMER) -B $(BitClock) $(AVRDUDE_BAUD) -p $(PARTNO) -P $(PORT) -U flash:v:./$(PARTNO)_test.hex:a \
	-U eeprom:v:./$(PARTNO)_test.eep:a -v
