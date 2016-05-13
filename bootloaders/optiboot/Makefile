# Makefile for ATmegaBOOT
# E.Lins, 18.7.2005
# $Id$
#
# Instructions
#
# To make bootloader .hex file:
# make diecimila
# make lilypad
# make ng
# etc...
#
# To burn bootloader .hex file:
# make diecimila_isp
# make lilypad_isp
# make ng_isp
# etc...
#
# Edit History
# 201605xx: kubi48: Makefile is changed for the assembler version of optiboot.
#                   All sample boards now fit to a 512 byte boot segment.
#                   You can now use the SUPPORT_EEPROM option with all configurations.
#                   The makeall script is changed for this feature.
#		    The size of the generated bootloader code is determined
#		    and the location of the bootloader and fuse options are set 
#		    set automatically by the Makefile.
#		    The command line tools bc, cat, cut, echo and  grep are
#		    required to run this automatic function.
#		    You can still select the C-source of optiboot with option
#                   C-SOURCE=1 .
# 201406xx: WestfW: More Makefile restructuring.
#                   Split off Makefile.1284, Makefile.extras, Makefile.custom
#                   So that in theory, the main Makefile contains only the
#                   official platforms, and does not need to be modified to
#                   add "less supported" chips and boards.
# 201303xx: WestfW: Major Makefile restructuring.
#                   Allows options on Make command line "make xx LED=B3"
#                   (see also pin_defs.h)
#                   Divide into "chip" targets and "board" targets.
#                   Most boards are (recursive) board targets with options.
#                   Move isp target to separate makefile (fixes m8 EFUSE)
#                   Some (many) targets will now be rebuilt when not
#                     strictly necessary, so that options will be included.
#                     (any "make" with options will always compile.)
#                   Set many variables with ?= so they can be overridden
#                   Use arduinoISP settings as default for ISP targets
#
#
# * Copyright 2013-2015 by Bill Westfield.  Part of Optiboot.
# * This software is licensed under version 2 of the Gnu Public Licence.
# * See optiboot.c for details.

#----------------------------------------------------------------------
#
# program name should not be changed...
PROGRAM    = optiboot

# The default behavior is to build using tools that are in the users
# current path variables, but we can also build using an installed
# Arduino user IDE setup, or the Arduino source tree.
# Uncomment this next lines to build within the arduino environment,
# using the arduino-included avrgcc toolset (mac and pc)
# ENV ?= arduino
# ENV ?= arduinodev
# OS ?= macosx
# OS ?= windows

# export symbols to recursive makes (for ISP)
export

# defaults
MCU_TARGET = atmega168

# Build environments
# Start of some ugly makefile-isms to allow optiboot to be built
# in several different environments.  See the README.TXT file for
# details.

# default
fixpath = $(1)

ifeq ($(ENV), arduino)
# For Arduino, we assume that we're connected to the optiboot directory
# included with the arduino distribution, which means that the full set
# of avr-tools are "right up there" in standard places.
# (except that in 1.5.x, there's an additional level of "up")
TESTDIR := $(firstword $(wildcard ../../../tools/*))
ifeq (,$(TESTDIR))
# Arduino 1.5.x tool location compared to optiboot dir
  TOOLROOT = ../../../../tools
else
# Arduino 1.0 (and earlier) tool location
  TOOLROOT = ../../../tools
endif
GCCROOT = $(TOOLROOT)/avr/bin/

ifeq ($(OS), windows)
# On windows, SOME of the tool paths will need to have backslashes instead
# of forward slashes (because they use windows cmd.exe for execution instead
# of a unix/mingw shell?)  We also have to ensure that a consistent shell
# is used even if a unix shell is installed (ie as part of WINAVR)
fixpath = $(subst /,\,$1)
SHELL = cmd.exe
SH = sh
endif

else ifeq ($(ENV), arduinodev)
# Arduino IDE source code environment.  Use the unpacked compilers created
# by the build (you'll need to do "ant build" first.)
ifeq ($(OS), macosx)
TOOLROOT = ../../../../build/macosx/work/Arduino.app/Contents/Resources/Java/hardware/tools
endif
ifeq ($(OS), windows)
TOOLROOT = ../../../../build/windows/work/hardware/tools
endif

GCCROOT = $(TOOLROOT)/avr/bin/
AVRDUDE_CONF = -C$(TOOLROOT)/avr/etc/avrdude.conf

else
GCCROOT =
AVRDUDE_CONF =
endif

STK500 = "C:\Program Files\Atmel\AVR Tools\STK500\Stk500.exe"
STK500-1 = $(STK500) -e -d$(MCU_TARGET) -pf -vf -if$(PROGRAM)_$(TARGET).hex \
           -lFF -LFF -f$(HFUSE)$(LFUSE) -EF8 -ms -q -cUSB -I200kHz -s -wt
STK500-2 = $(STK500) -d$(MCU_TARGET) -ms -q -lCF -LCF -cUSB -I200kHz -s -wt
#
# End of build environment code.

OBJ        = $(PROGRAM).o
OPTIMIZE = -Os -fno-split-wide-types -mrelax

DEFS       = 

COMMON_OPTIONS = $(BAUD_RATE_CMD) $(LED_START_FLASHES_CMD) $(BIGBOOT_CMD)
COMMON_OPTIONS += $(SOFT_UART_CMD) $(LED_DATA_FLASH_CMD) $(LED_CMD)

#
# Make command-line Options.
# Permit commands like "make atmega328 LED_START_FLASHES=10" to pass the
# appropriate parameters ("-DLED_START_FLASHES=10") to gcc
#

#default source type is Assembler (S).
# you can select a C source type with option "C_SOURCE=1"
SOURCE_TYPE = S
ifdef C_SOURCE
 ifneq ($(C_SOURCE),0)
  SOURCE_TYPE = c
 endif
endif

ifdef F_CPU
F_CPU_CMD = -DF_CPU=$(F_CPU)
else
F_CPU_CMD = -DF_CPU=$(AVR_FREQ)
endif

ifdef BAUD_RATE
BAUD_RATE_CMD = -DBAUD_RATE=$(BAUD_RATE)
else
BAUD_RATE_CMD = -DBAUD_RATE=115200
endif

ifdef LED_START_FLASHES
LED_START_FLASHES_CMD = -DLED_START_FLASHES=$(LED_START_FLASHES)
else
LED_START_FLASHES_CMD = -DLED_START_FLASHES=3
endif


# BIG_BOOT: Include extra features, up to 1K.
ifdef BIGBOOT
BIGBOOT_CMD = -DBIGBOOT=$(BIGBOOT)
endif

ifdef SOFT_UART
 ifneq ($(SOFT_UART),0)
  SOFT_UART_CMD = -DSOFT_UART=1
 endif
endif
ifdef UART_RX
  SOFT_UART_CMD += -DUART_RX=$(UART_RX)
endif
ifdef UART_TX
  SOFT_UART_CMD += -DUART_TX=$(UART_TX)
endif

ifdef LED_DATA_FLASH
LED_DATA_FLASH_CMD = -DLED_DATA_FLASH=$(LED_DATA_FLASH)
endif

ifdef LED
LED_CMD = -DLED=$(LED)
endif

#UART is handled separately and only passed for devices with more than one.
ifdef UART
UART_CMD = -DUART=$(UART)
endif

ifdef SUPPORT_EEPROM
COMMON_OPTIONS += -DSUPPORT_EEPROM=$(SUPPORT_EEPROM)
endif

ifdef FORCE_WATCHDOG
COMMON_OPTIONS += -DFORCE_WATCHDOG
endif

# Not supported yet
# ifdef TIMEOUT_MS
# TIMEOUT_MS_CMD = -DTIMEOUT_MS=$(TIMEOUT_MS)
# endif
#


#
# platforms support EEPROM and large bootloaders need the eeprom functions that
# are defined in libc, even though we explicity remove it with -nostdlib because
# of the space-savings.
LIBS       =  -lc

CC         = $(GCCROOT)avr-gcc
#
# Include additional platforms
include Makefile.atmel
include Makefile.extras
include Makefile.1284
include Makefile.custom


#---------------------------------------------------------------------------
# "Chip-level Platform" targets.
# A "Chip-level Platform" compiles for a particular chip, but probably does
# not have "standard" values for things like clock speed, LED pin, etc.
# Makes for chip-level platforms should usually explicitly define their
# options like: "make atmega1285 AVR_FREQ=16000000 LED=D0"
#---------------------------------------------------------------------------
#
# Note about fuses:
# the efuse should really be 0xf8; since, however, only the lower
# three bits of that byte are used on the atmega168, avrdude gets
# confused if you specify 1's for the higher bits, see:
# http://tinker.it/now/2007/02/24/the-tale-of-avrdude-atmega168-and-extended-bits-fuses/
#
# similarly, the lock bits should be 0xff instead of 0x3f (to
# unlock the bootloader section) and 0xcf instead of 0x2f (to
# lock it), but since the high two bits of the lock byte are
# unused, avrdude would get confused.
#---------------------------------------------------------------------------
#

# Test platforms
# Virtual boot block test
virboot8: TARGET := atmega8
virboot8: MCU_TARGET := atmega8
virboot8: AVR_FREQ := 16000000 
virboot8: FLASH_SIZE := 8192
virboot8: BOOT_PAGE_LEN := 256
virboot8: COMMON_OPTIONS += -DVIRTUAL_BOOT_PARTITION '-Dsave_vect_num=EE_RDY_vect_num'
virboot8: $(PROGRAM)_virboot8.hex
virboot8: $(PROGRAM)_virboot8.lst


virboot328: TARGET := atmega328
virboot328: MCU_TARGET := atmega328p
virboot328: AVR_FREQ := 16000000
virboot328: FLASH_SIZE = 32768
virboot328: BOOT_PAGE_LEN = 512
virboot328: COMMON_OPTIONS += -DVIRTUAL_BOOT_PARTITION
virboot328: $(PROGRAM)_virboot328.hex
virboot328: $(PROGRAM)_virboot328.lst

virboot328_isp: virboot328
virboot328_isp: TARGET = virboot328
virboot328_isp: MCU_TARGET = atmega328p
# no boot section, SPIEN
virboot328_isp: HFUSE ?= DF
# Low power xtal (16MHz) 16KCK/14CK+65ms
virboot328_isp: LFUSE ?= FF
# 2.7V brownout
virboot328_isp: EFUSE ?= 05
virboot328_isp: isp


# Diecimila, Duemilanove with m168, and NG use identical bootloaders
# Call it "atmega168" for generality and clarity, keep "diecimila" for
# backward compatibility of makefile
#
atmega168: TARGET := atmega168
atmega168: override MCU_TARGET = atmega168
atmega168: AVR_FREQ := 16000000 
atmega168: FLASH_SIZE := 16384
atmega168: BOOT_PAGE_LEN := 256
atmega168: $(PROGRAM)_atmega168.hex
atmega168: $(PROGRAM)_atmega168.lst

atmega168_isp: atmega168
atmega168_isp: TARGET := atmega168
# 2.7V brownout
atmega168_isp: HFUSE ?= DD
# Full swing xtal (16MHz) 16KCK/14CK+65ms
atmega168_isp: LFUSE ?= F7
# 512 byte boot
atmega168_isp: EFUSE ?= 04
atmega168_isp: isp

atmega168p: atmega168

atmega16: TARGET = atmega16
atmega16: MCU_TARGET = atmega16
atmega16: AVR_FREQ = 16000000
atmega16: FLASH_SIZE := 16384
atmega16: BOOT_PAGE_LEN := 256
atmega16: $(PROGRAM)_atmega16.hex
atmega16: $(PROGRAM)_atmega16.lst

atmega328: TARGET = atmega328
atmega328: MCU_TARGET = atmega328
atmega328: AVR_FREQ = 16000000
atmega328: FLASH_SIZE := 32768
atmega328: BOOT_PAGE_LEN := 512
atmega328: $(PROGRAM)_atmega328.hex
atmega328: $(PROGRAM)_atmega328.lst

atmega328_isp: atmega328
atmega328_isp: TARGET = atmega328
atmega328_isp: MCU_TARGET = atmega328
# 512 byte boot, SPIEN
atmega328_isp: HFUSE ?= DE
#atmega328_isp: HFUSE ?= D9
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328_isp: LFUSE ?= FF
# 2.7V brownout
atmega328_isp: EFUSE ?= 05
atmega328_isp: isp

atmega328p: TARGET = atmega328p
atmega328p: MCU_TARGET = atmega328p
atmega328p: AVR_FREQ = 16000000
atmega328p: FLASH_SIZE := 32768
atmega328p: BOOT_PAGE_LEN := 512
atmega328p: $(PROGRAM)_atmega328p.hex
atmega328p: $(PROGRAM)_atmega328p.lst

atmega328p_isp: atmega328p
atmega328p_isp: TARGET = atmega328p
atmega328p_isp: MCU_TARGET = atmega328p
# 512 byte boot, SPIEN
atmega328p_isp: HFUSE ?= DE
#atmega328_isp: HFUSE ?= D9
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328p_isp: LFUSE ?= FF
# 2.7V brownout
atmega328p_isp: EFUSE ?= 05
atmega328p_isp: isp

#Atmega1280
atmega1280: MCU_TARGET = atmega1280
atmega1280: AVR_FREQ = 16000000
atmega1280: FLASH_SIZE := 131072
atmega1280: BOOT_PAGE_LEN := 1024
atmega1280: COMMON_OPTIONS +=  $(UART_CMD)
atmega1280: $(PROGRAM)_atmega1280.hex
atmega1280: $(PROGRAM)_atmega1280.lst


# ATmega8
#
atmega8: TARGET := atmega8
atmega8: MCU_TARGET := atmega8
atmega8: AVR_FREQ := 16000000 
atmega8: FLASH_SIZE := 8192
atmega8: BOOT_PAGE_LEN = 256
atmega8: $(PROGRAM)_atmega8.hex
atmega8: $(PROGRAM)_atmega8.lst

atmega8_isp: atmega8
atmega8_isp: TARGET := atmega8
atmega8_isp: MCU_TARGET := atmega8
# SPIEN, CKOPT (for full swing xtal), Bootsize=512B
atmega8_isp: HFUSE ?= CC
# 2.7V brownout, 16MHz Xtal, 16KCK/14CK+65ms
atmega8_isp: LFUSE ?= BF
atmega8_isp: isp


#---------------------------------------------------------------------------
# "Board-level Platform" targets.
# A "Board-level Platform" implies a manufactured platform with a particular
# AVR_FREQ, LED, and so on.  Parameters are not particularly changable from
# the "make" command line.
# Most of the board-level platform builds should envoke make recursively
#  appropriate specific options
#---------------------------------------------------------------------------
# 20MHz clocked platforms
#
# These are capable of 230400 baud, or 115200 baud on PC (Arduino Avrdude issue)
#

pro20: TARGET = pro_20Mhz
pro20: CHIP = atmega168
pro20:
	$(MAKE) atmega168 F_CPU=20000000 LED_START_FLASHES=3
	mv $(PROGRAM)_$(CHIP).hex $(PROGRAM)_$(TARGET).hex
	mv $(PROGRAM)_$(CHIP).lst $(PROGRAM)_$(TARGET).lst

pro20_isp: pro20
pro20_isp: TARGET = pro_20Mhz
# 2.7V brownout
pro20_isp: HFUSE ?= DD
# Full swing xtal (20MHz) 258CK/14CK+4.1ms
pro20_isp: LFUSE ?= C6
# 512 byte boot
pro20_isp: EFUSE ?= 05
pro20_isp: isp

# 16MHz clocked platforms
#
# These are capable of 230400 baud, or 115200 baud on PC (Arduino Avrdude issue)
#

pro16: TARGET = pro_16MHz
pro16: CHIP = atmega168
pro16:
	$(MAKE) $(CHIP) F_CPU=16000000 LED_START_FLASHES=3
	mv $(PROGRAM)_$(CHIP).hex $(PROGRAM)_$(TARGET).hex
	mv $(PROGRAM)_$(CHIP).lst $(PROGRAM)_$(TARGET).lst

pro16_isp: pro16
pro16_isp: TARGET = pro_16MHz
# 2.7V brownout
pro16_isp: HFUSE ?= DD
# Full swing xtal (20MHz) 258CK/14CK+4.1ms
pro16_isp: LFUSE ?= C6
# 512 byte boot
pro16_isp: EFUSE ?= 05
pro16_isp: isp

diecimila: TARGET = diecimila
diecimila: CHIP = atmega168
diecimila:
	$(MAKE) $(CHIP) F_CPU=16000000 LED_START_FLASHES=3
	mv $(PROGRAM)_$(CHIP).hex $(PROGRAM)_$(TARGET).hex
	mv $(PROGRAM)_$(CHIP).lst $(PROGRAM)_$(TARGET).lst

diecimila_isp: diecimila
diecimila_isp: TARGET = diecimila
# 2.7V brownout
diecimila_isp: HFUSE ?= DD
# Low power xtal (16MHz) 16KCK/14CK+65ms
diecimila_isp: LFUSE ?= FF
# 512 byte boot
diecimila_isp: EFUSE ?= 05
diecimila_isp: isp


# MEGA1280 Board (this is different from the atmega1280 chip platform)
# Mega has a minimum boot size of 1024 bytes, so enable extra functions
# Note that optiboot does not (can not) work on the MEGA2560
#mega: TARGET = atmega1280
mega1280: atmega1280

mega1280_isp: mega1280
mega1280_isp: TARGET = atmega1280
mega1280_isp: MCU_TARGET = atmega1280
# 1024 byte boot
mega1280_isp: HFUSE ?= DE
# Low power xtal (16MHz) 16KCK/14CK+65ms
mega1280_isp: LFUSE ?= FF
# 2.7V brownout; wants F5 for some reason...
mega1280_isp: EFUSE ?= 05
mega1280_isp: isp

# 8MHz clocked platforms
#
# These are capable of 115200 baud
# Note that "new" Arduinos with an AVR as USB/Serial converter will NOT work
# with an 8MHz target Arduino.  The bitrate errors are in opposite directions,
# and total too large a number.
#

lilypad: TARGET = $@
lilypad: CHIP = atmega168
lilypad:
	$(MAKE) $(CHIP) F_CPU=8000000 LED_START_FLASHES=3
	mv $(PROGRAM)_$(CHIP).hex $(PROGRAM)_$(TARGET).hex
	mv $(PROGRAM)_$(CHIP).lst $(PROGRAM)_$(TARGET).lst

lilypad_isp: lilypad
lilypad_isp: TARGET = lilypad
# 2.7V brownout
lilypad_isp: HFUSE ?= DD
# Internal 8MHz osc (8MHz) Slow rising power
lilypad_isp: LFUSE ?= E2
# 512 byte boot
lilypad_isp: EFUSE ?= 05
lilypad_isp: isp

# lilypad_resonator is the same as a 8MHz lilypad, except for fuses.
lilypad_resonator: lilypad

lilypad_resonator_isp: lilypad
lilypad_resonator_isp: TARGET = lilypad
# 2.7V brownout
lilypad_resonator_isp: HFUSE ?= DD
# Full swing xtal (20MHz) 258CK/14CK+4.1ms
lilypad_resonator_isp: LFUSE ?= C6
# 512 byte boot
lilypad_resonator_isp: EFUSE ?= 05
lilypad_resonator_isp: isp

pro8: TARGET = pro_8MHz
pro8: CHIP = atmega168
pro8:
	$(MAKE) $(CHIP) F_CPU=8000000 LED_START_FLASHES=3
	mv $(PROGRAM)_$(CHIP).hex $(PROGRAM)_$(TARGET).hex
	mv $(PROGRAM)_$(CHIP).lst $(PROGRAM)_$(TARGET).lst

pro8_isp: pro8
pro8_isp: TARGET = pro_8MHz
# 2.7V brownout
pro8_isp: HFUSE ?= DD
# Full swing xtal (20MHz) 258CK/14CK+4.1ms
pro8_isp: LFUSE ?= C6
# 512 byte boot
pro8_isp: EFUSE ?= 05
pro8_isp: isp

atmega328_pro8: TARGET = atmega328_pro_8MHz
atmega328_pro8: CHIP = atmega328
atmega328_pro8:
	$(MAKE) $(CHIP) F_CPU=8000000 LED_START_FLASHES=3
	mv $(PROGRAM)_$(CHIP).hex $(PROGRAM)_$(TARGET).hex
	mv $(PROGRAM)_$(CHIP).lst $(PROGRAM)_$(TARGET).lst

atmega328_pro8_isp: atmega328_pro8
atmega328_pro8_isp: TARGET = atmega328_pro_8MHz
atmega328_pro8_isp: MCU_TARGET = atmega328p
# 512 byte boot, SPIEN
atmega328_pro8_isp: HFUSE ?= DE
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328_pro8_isp: LFUSE ?= FF
# 2.7V brownout
atmega328_pro8_isp: EFUSE ?= 06
atmega328_pro8_isp: isp

#
# Include additional platforms
#include Makefile.atmel
#include Makefile.extras
#include Makefile.1284
#include Makefile.custom
FLASH_SIZE ?= 4096
BOOT_PAGE_LEN ?= 8

SIZE           = $(GCCROOT)avr-size

# We can not compute the number of boot pages, because the object file must be created first!
#BOOT_PAGES = $(shell echo "pg_anz=(`$(SIZE) -C $(PROGRAM).o | grep "Program:" | cut -c 10-16`/$(BOOT_PAGE_LEN) +1); pg_anz + (pg_anz==3) + (pg_anz==5)*3 + (pg_anz==6)*2 + (pg_anz == 7)" | bc)
define BOOT_PAGES =
 qecho "pg_anz=(`$(SIZE) -C $(PROGRAM).o | grep "Program:" | cut -c 10-16`/$(BOOT_PAGE_LEN) +1); pg_anz + (pg_anz==3) + (pg_anz==5)*3 + (pg_anz==6)*2 + (pg_anz == 7)" | bc
endef

define BOOT_SZ =
 @echo "pg_anz=(`$(SIZE) -C $(PROGRAM).elf | grep "Program:" | cut -c 10-16`/$(BOOT_PAGE_LEN) +1); 0 + (pg_anz<5) + (pg_anz<3) + (pg_anz<2)" | bc
endef

LDSECTIONS  = -Wl,--section-start=.version=0x$(shell echo "obase=16;$(FLASH_SIZE)-2" | bc)

# Override is only needed by avr-lib build system.
override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(F_CPU_CMD) $(DEFS)
override LDFLAGS       = -Wl,--relax -nostartfiles -nostdlib

OBJCOPY        = $(GCCROOT)avr-objcopy
OBJDUMP        = $(call fixpath,$(GCCROOT)avr-objdump)


#---------------------------------------------------------------------------
#
# Generic build instructions
#

FORCE:

baudcheck: FORCE
	- @$(CC) $(CFLAGS) $(COMMON_OPTIONS) -E baudcheck.c -o baudcheck.tmp.sh
	- @bash ./baudcheck.tmp.sh
$(PROGRAM).o: $(PROGRAM).$(SOURCE_TYPE) FORCE
	$(CC) $(CFLAGS) $(COMMON_OPTIONS) -c -o $@ $<

isp: $(TARGET)
	$(MAKE) -f Makefile.isp isp TARGET=$(TARGET)

isp-stk500: $(PROGRAM)_$(TARGET).hex
	$(STK500-1)
	$(STK500-2)

#  we can determine the size of the loader with optiboot.o for Assembler source input,
#  but for C source we need to do some optimizing  with the binder call (.elf).
#  This call is done without the relolation of the .text section (instruction code).
#  After computing the required size (and the possible relocation address),
#  This .elf is removed.
$(PROGRAM)x.elf: $(OBJ)
	@$(CC) $(CFLAGS) $(COMMON_OPTIONS) $(LDSECTIONS) $(LDFLAGS)  -o $(PROGRAM)x.elf $< $(LIBS)

BootPages.dat: $(OBJ) $(PROGRAM)x.elf
	@echo "pg_anz=($(shell $(SIZE) -C $(PROGRAM)x.elf | grep "Program:" | cut -c 10-16)/$(BOOT_PAGE_LEN) +1); pg_anz + (pg_anz==3) + (pg_anz==5)*3 + (pg_anz==6)*2 + (pg_anz == 7)" | bc > BootPages.dat

BL_StartAdr.dat: $(OBJ) $(PROGRAM)x.elf BootPages.dat
	@echo "obase=16;($(FLASH_SIZE) - $(shell cat BootPages.dat)*$(BOOT_PAGE_LEN))" | bc > BL_StartAdr.dat
#	@rm $(PROGRAM)x.elf

$(PROGRAM).elf: $(OBJ) baudcheck  BL_StartAdr.dat
	@echo "Boot Loader start address: 0x$(shell cat BL_StartAdr.dat)"
	$(CC) $(CFLAGS) $(COMMON_OPTIONS) $(LDSECTIONS) \
        -Wl,--section-start=.text=0x$(shell cat BL_StartAdr.dat) $(LDFLAGS) -o $(PROGRAM).elf $< $(LIBS)
	$(SIZE) $(PROGRAM).elf
clean:
	rm -rf *.o *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex *.tmp.sh *.dat

BOOTSZ.dat: $(PROGRAM).elf BootPages.dat
	@echo "Requires $(shell cat BootPages.dat) Boot Pages, $(BOOT_PAGE_LEN) Bytes each"
	@echo "BOOTSZ=$(shell echo "pg_anz=(`$(SIZE) -C $(PROGRAM).elf | grep "Program:" | cut -c 10-16`/$(BOOT_PAGE_LEN) +1); 0 + (pg_anz<5) + (pg_anz<3) + (pg_anz<2)" | bc)"
	@echo   "$(shell echo "pg_anz=(`$(SIZE) -C $(PROGRAM).elf | grep "Program:" | cut -c 10-16`/$(BOOT_PAGE_LEN) +1); 0 + (pg_anz<5) + (pg_anz<3) + (pg_anz<2)" | bc)" > BOOTSZ.dat



%.lst: $(PROGRAM).elf BOOTSZ.dat
	$(OBJDUMP) -h -S $< > $@
#	rm $(PROGRAM).o

%.hex: $(PROGRAM).elf BOOTSZ.dat
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O ihex $< $@

%.srec: $(PROGRAM).elf BOOTSZ.dat
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O srec $< $@

%.bin: $(PROGRAM).elf BOOTSZ.dat
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O binary $< $@
