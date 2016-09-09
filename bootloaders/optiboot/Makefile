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
#SUB_MAKE = $(MAKE) --no-print-directory -p
#SUB_MAKE = $(MAKE) --no-print-directory --warn-undefined-variables
SUB_MAKE = $(MAKE) --no-print-directory 

ifdef ENV
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
# no known config
GCCROOT =
AVRDUDE_CONF =
endif
else
# no ENV set
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
COMMON_OPTIONS += $(SOFT_UART_CMD) $(LED_DATA_FLASH_CMD) 

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
 else
  SUPPORT_EEPROM := 1
 endif
else
 SUPPORT_EEPROM := 1
endif

# let a F_CPU=  parameter pass as AVR_FREQ=
ifdef F_CPU
AVR_FREQ := $(F_CPU)
endif

BAUD_RATE ?= 115200
BAUD_RATE_CMD = -DBAUD_RATE=$(BAUD_RATE)

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

ifdef LED_DATA_FLASH
LED_DATA_FLASH_CMD = -DLED_DATA_FLASH=$(LED_DATA_FLASH)
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
virboot8: TARGET := virboot8
virboot8: MCU_TARGET := atmega8
virboot8: AVR_FREQ := 16000000 
virboot8: FLASH_SIZE := 8192
# for virtual boot partition we can use the Flash page size as boot page length
virboot8: BOOT_PAGE_LEN := 64
# SPIEN, CKOPT (for full swing xtal), no boot section
virboot8: HFUSE := C9
# 2.7V brownout, 16MHz Xtal, 16KCK/14CK+65ms
virboot8: LFUSE := BF
virboot8: VIRTUAL_BOOT_PARTITION := 1
virboot8: COMMON_OPTIONS += -DVIRTUAL_BOOT_PARTITION '-Dsave_vect_num=EE_RDY_vect_num'
virboot8: isp

virboot8_isp:
	$(SUB_MAKE) virboot8 ISP=1


virboot328: TARGET := virboot328
virboot328: MCU_TARGET = atmega328p
virboot328: AVR_FREQ := 16000000
virboot328: FLASH_SIZE := 32768
# for virtual boot partition we can use the Flash page size as Boot page length
virboot328: BOOT_PAGE_LEN := 128
virboot328: VIRTUAL_BOOT_PARTITION := 1
virboot328: COMMON_OPTIONS += -DVIRTUAL_BOOT_PARTITION
# no boot section, SPIEN
virboot328: HFUSE := DF
# Low power xtal (16MHz) 16KCK/14CK+65ms
virboot328: LFUSE := FF
# 2.7V brownout
virboot328: EFUSE := 05
virboot328: isp

virboot328_isp: 
	$(SUB_MAKE) virboot328 ISP=1


# Diecimila, Duemilanove with m168, and NG use identical bootloaders
# Call it "atmega168" for generality and clarity, keep "diecimila" for
# backward compatibility of makefile
#
################################################
# generic atmega168p
# let board specific change the frequency and fuses
ifndef TARGET
atmega168p: TARGET := atmega168p
endif
atmega168p: MCU_TARGET := atmega168p
ifndef AVR_FREQ
atmega168p: AVR_FREQ := 16000000 
endif
atmega168p: FLASH_SIZE := 16384
atmega168p: BOOT_PAGE_LEN := 256
ifndef HFUSE
# 2.7V brownout
atmega168p: HFUSE := DD
endif
ifndef LFUSE
# Low power xtal (16MHz) 16KCK/14CK+65ms :=FF
# Full swing xtal (16MHz) 16KCK/14CK+65ms  := FC
atmega168p: LFUSE := FC
endif
ifndef EFUSE
# 512 byte boot
atmega168p: EFUSE := 04
endif
atmega168p: isp

atmega168p_isp: 
	$(SUB_MAKE) atmega168p ISP=1

################################################
# generic atmega168
# let board specific change the frequency and fuses
ifndef TARGET
atmega168: TARGET := atmega168
endif
atmega168: MCU_TARGET := atmega168
ifndef AVR_FREQ
atmega168: AVR_FREQ := 16000000 
endif
atmega168: FLASH_SIZE := 16384
atmega168: BOOT_PAGE_LEN := 256
ifndef HFUSE
# 2.7V brownout
atmega168: HFUSE := DD
endif
ifndef LFUSE
# Low power xtal (16MHz) 16KCK/14CK+65ms :=FF
# Full swing xtal (16MHz) 16KCK/14CK+65ms  := FC
atmega168: LFUSE := FC
endif
ifndef EFUSE
# 512 byte boot
atmega168: EFUSE := 04
endif
atmega168: isp

atmega168_isp: 
	$(SUB_MAKE) atmega168 ISP=1


################################################
# generic atmega16
# let board specific change the frequency and fuses
ifndef TARGET
atmega16: TARGET := atmega16
endif
atmega16: MCU_TARGET := atmega16
ifndef AVR_FREQ
atmega16: AVR_FREQ := 16000000
endif
atmega16: FLASH_SIZE := 16384
atmega16: BOOT_PAGE_LEN := 256
ifndef HFUSE
# 512 byte boot, SPIEN
atmega16: HFUSE := 9C
endif
ifndef LFUSE
# BrownOut enable, Crystal/Resonator high Frequency (16MHz) 16KCK/14CK+65ms
atmega16: LFUSE := BF
endif
# LED is set to D6 by default for ATmega16
atmega16: LED := D6

atmega16: isp

################################################
# generic atmega328
# let board specific change the frequency and fuses
ifndef TARGET
atmega328: TARGET := atmega328
endif
atmega328: MCU_TARGET := atmega328
ifndef AVR_FREQ
atmega328: AVR_FREQ := 16000000
endif
atmega328: FLASH_SIZE := 32768
atmega328: BOOT_PAGE_LEN := 512
ifndef HFUSE
# 512 byte boot, SPIEN
atmega328: HFUSE := DE
endif
ifndef LFUSE
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328: LFUSE := FF
endif
ifndef EFUSE
# 2.7V brownout
atmega328: EFUSE := 05
endif
atmega328: isp

atmega328_isp: 
	$(SUB_MAKE) atmega328 ISP=1

################################################
# generic atmega328p
# let board specific change the frequency and fuses
ifndef TARGET
atmega328p: TARGET := atmega328p
endif
atmega328p: MCU_TARGET = atmega328p
ifndef AVR_FREQ
atmega328p: AVR_FREQ := 16000000
endif
atmega328p: FLASH_SIZE := 32768
atmega328p: BOOT_PAGE_LEN := 512
ifndef HFUSE
# 512 byte boot, SPIEN
atmega328p: HFUSE := DE
endif
ifndef LFUSE
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328p: LFUSE := FF
endif
ifndef EFUSE
# 2.7V brownout
atmega328p: EFUSE := 05
endif
atmega328p: isp

atmega328p_isp: 
	$(SUB_MAKE) atmega328p ISP=1

################################################
# generic atmega1280
# let board specific change the frequency and fuses
ifndef TARGET
atmega1280: TARGET := atmega1280
endif
atmega1280: MCU_TARGET := atmega1280
ifndef AVR_FREQ
atmega1280: AVR_FREQ := 16000000
endif
atmega1280: FLASH_SIZE := 131072
atmega1280: BOOT_PAGE_LEN := 1024
ifndef HFUSE
# 1024 byte boot
atmega1280: HFUSE := DE
endif
ifndef LFUSE
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega1280: LFUSE := FF
endif
ifndef LFUSE
# 2.7V brownout; wants F5 for some reason...
atmega1280: EFUSE := 05
endif
atmega1280: COMMON_OPTIONS +=  $(UART_CMD)
atmega1280: isp 

atmega1280_isp: 
	$(SUB_MAKE) atmega1280 ISP=1


################################################
# generic atmega8
# let board specific change the frequency and fuses
ifndef TARGET
atmega8: TARGET := atmega8
endif
atmega8: MCU_TARGET := atmega8
ifndef AVR_FREQ
atmega8: AVR_FREQ := 16000000 
endif
atmega8: FLASH_SIZE := 8192
atmega8: BOOT_PAGE_LEN := 256
ifndef HFUSE
# SPIEN, CKOPT (for full swing xtal), Bootsize=512B
atmega8: HFUSE := CC
endif
ifndef LFUSE
# 2.7V brownout, 16MHz Xtal, 16KCK/14CK+65ms
atmega8: LFUSE := BF
endif
atmega8: isp

atmega8_isp: 
	$(SUB_MAKE) atmega8 ISP=1


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

pro20: TARGET := pro_20Mhz
pro20: LED_START_FLASHES := 3
pro20: AVR_FREQ := 20000000
# 4.3V brownout (for max speed!)
pro20: HFUSE := DC
# Full swing xtal (20MHz) 258CK/14CK+4.1ms
pro20: LFUSE := F7
# 512 byte boot
pro20: EFUSE := 04
pro20:
	$(SUB_MAKE) atmega168 

pro20_isp: 
	$(SUB_MAKE) pro20 ISP=1

# 16MHz clocked platforms
#
# These are capable of 230400 baud, or 115200 baud on PC (Arduino Avrdude issue)
#

pro16: TARGET := pro_16MHz
pro16: LED_START_FLASHES := 3
pro16: AVR_FREQ := 16000000
# 2.7V brownout
pro16: HFUSE := DD
# Full swing xtal (20MHz) 258CK/14CK+4.1ms
pro16: LFUSE := F7
# 512 byte boot
pro16: EFUSE := 04
pro16:
	$(SUB_MAKE) atmega168 

pro16_isp:
	$(SUB_MAKE) pro16 ISP=1

pro8: TARGET := pro_8MHz
pro8: LED_START_FLASHES := 3
pro8: AVR_FREQ := 8000000
# 2.7V brownout
pro8: HFUSE := DD
# Full swing xtal (20MHz) 258CK/14CK+4.1ms
pro8: LFUSE := C6
# 512 byte boot
pro8: EFUSE := 04
pro8:
	$(SUB_MAKE) atmega168 

pro8_isp:
	$(SUB_MAKE) pro8 ISP=1 

diecimila: TARGET := diecimila
diecimila: LED_START_FLASHES := 3
# 2.7V brownout
diecimila: HFUSE := DD
# Low power xtal (16MHz) 16KCK/14CK+65ms
diecimila: LFUSE := F7
# 512 byte boot
diecimila: EFUSE := 04
diecimila:
	$(SUB_MAKE) atmega168

diecimila_isp: 
	$(SUB_MAKE) -r diecimila ISP=1


# MEGA1280 Board (this is different from the atmega1280 chip platform)
# Mega has a minimum boot size of 1024 bytes, so enable extra functions
# Note that optiboot does not (can not) work on the MEGA2560
#mega: TARGET = atmega1280
mega1280: TARGET := mega1280
mega1280:
	$(SUB_MAKE) atmega1280
# 1024 byte boot
mega1280_isp: HFUSE ?= DE
# Low power xtal (16MHz) 16KCK/14CK+65ms
mega1280_isp: LFUSE ?= FF
# 2.7V brownout; wants F5 for some reason...
mega1280_isp: EFUSE ?= 05
mega1280_isp:
	$(SUB_MAKE) mega1280 ISP=1

# 8MHz clocked platforms
#
# These are capable of 115200 baud
# Note that "new" Arduinos with an AVR as USB/Serial converter will NOT work
# with an 8MHz target Arduino.  The bitrate errors are in opposite directions,
# and total too large a number.
#

lilypad: TARGET := lilypad
lilypad: LED_START_FLASHES := 3
lilypad: AVR_FREQ := 8000000
# 2.7V brownout
lilypad: HFUSE := DD
# Internal 8MHz osc (8MHz) Slow rising power
lilypad: LFUSE := E2
# 512 byte boot
lilypad: EFUSE := 04
lilypad:
	$(SUB_MAKE) atmega168

lilypad_isp: 
	$(SUB_MAKE) lilypad ISP=1

# lilypad_resonator is the same as a 8MHz lilypad, except for fuses.
lilypad_resonator: TARGET := lilypad_resonator
lilypad_resonator: LED_START_FLASHES := 3
lilypad_resonator: AVR_FREQ := 8000000
# 2.7V brownout
lilypad_resonator: HFUSE := DD
# Full swing xtal (20MHz) 258CK/14CK+4.1ms
lilypad_resonator: LFUSE := C6
# 512 byte boot
lilypad_resonator: EFUSE := 04
lilypad_resonator:
	$(SUB_MAKE) atmega168 

lilypad_resonator_isp: 
	$(SUB_MAKE) lilypad_resonator ISP=1

atmega328_pro8: TARGET := atmega328_pro_8MHz
atmega328_pro8: AVR_FREQ := 8000000
atmega328_pro8: LED_START_FLASHES := 3
# 512 byte boot, SPIEN
atmega328_pro8: HFUSE := DE
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328_pro8: LFUSE := FF
# 2.7V brownout
atmega328_pro8: EFUSE := 05
atmega328_pro8:
	$(SUB_MAKE) atmega328p

atmega328_pro8_isp: 
	$(SUB_MAKE) atmega328_pro8 ISP=1

#
# Include additional platforms
include Makefile.atmel
include Makefile.extras
include Makefile.1284
include Makefile.custom
#FLASH_SIZE ?= 4096
#BOOT_PAGE_LEN ?= 8

SIZE           = $(GCCROOT)avr-size

# We can not compute the number of boot pages, because the object file must be created first!
#BOOT_PAGES = $(shell echo "pg_anz=(`$(SIZE) -C $(PROGRAM).o | grep "Program:" | cut -c 10-16`/$(BOOT_PAGE_LEN) +1); pg_anz + (pg_anz==3) + (pg_anz==5)*3 + (pg_anz==6)*2 + (pg_anz == 7)" | bc)
define BOOT_PAGES =
 @echo "pg_anz=(`$(SIZE) -C $(PROGRAM).o | grep "Program:" | cut -c 10-16`/$(BOOT_PAGE_LEN) +1); pg_anz + (pg_anz==3) + (pg_anz==5)*3 + (pg_anz==6)*2 + (pg_anz == 7)" | bc
endef

define BOOT_SZ =
 @echo "pg_anz=(`$(SIZE) -C $(PROGRAM).elf | grep "Program:" | cut -c 10-16`/$(BOOT_PAGE_LEN) +1); 0 + (pg_anz<5) + (pg_anz<3) + (pg_anz<2)" | bc
endef

LDSECTIONS  = -Wl,--section-start=.version=0x$(shell echo "obase=16;$(FLASH_SIZE)-2" | bc)

# Override is only needed by avr-lib build system.
override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS       = -Wl,--relax -nostartfiles -nostdlib

OBJCOPY        = $(GCCROOT)avr-objcopy
OBJDUMP        = $(call fixpath,$(GCCROOT)avr-objdump)


#---------------------------------------------------------------------------
#
# Generic build instructions
#

FORCE:

baudcheck: FORCE
	- @$(CC) $(CFLAGS) $(COMMON_OPTIONS) -DF_CPU=$(AVR_FREQ) -E baudcheck.c -o baudcheck.tmp.sh
	- @bash ./baudcheck.tmp.sh
$(PROGRAM).o: $(PROGRAM).$(SOURCE_TYPE) FORCE
	$(CC) $(CFLAGS) $(COMMON_OPTIONS) -DLED=p$(LED) -DUART_RX=p$(UART_RX) -DUART_TX=p$(UART_TX) -DF_CPU=$(AVR_FREQ) -c -o $@ $<

ifdef ISP
isp: add_options
	@$(SUB_MAKE) -r -f Makefile.isp isp TARGET=$(TARGET)
else
isp: add_options

endif

isp-stk500: $(PROGRAM).hex
	$(STK500-1)
	$(STK500-2)

#  we can determine the size of the loader with optiboot.o for Assembler source input,
#  but for C source we need to do some optimizing  with the binder call (.elf).
#  This call is done without the relolation of the .text section (instruction code).
#  After computing the required size (and the possible relocation address),
#  This .elf is removed.
$(PROGRAM)x.elf: $(OBJ)
	$(CC) $(CFLAGS) $(COMMON_OPTIONS) $(LDSECTIONS) $(LDFLAGS)  -o $(PROGRAM)x.elf $< $(LIBS)

# BootPages.dat fetch the actual boot loader size from a interim $(PROGRAM)x.elf file, not from the
# $(PROGRAM).o file. The ld program can do some optimizing for code generated from a C-source.
# For code generated with the assembler there is no size difference between .o and .elf !
# If 3 pages are required, number of pages is rounded to 4.
# If more than 4 pages are required, the number of pages is rounded to 8.
# Above 8 pages there is no round up. 
# The ATtiny84 has no hardware feature for the bootloader like the ATmega family.
# Therefore the "round up" is not required for the ATtiny84, but the BOOT_PAGE_LEN is 64 for
# this processor, so the number of pages is more than 7 pages for the actual size of optiboot.
BootPages.dat: $(OBJ) $(PROGRAM)x.elf
	echo "pg_anz=($(shell $(SIZE) -C $(PROGRAM)x.elf | grep "Program:" | cut -c 10-16)/$(BOOT_PAGE_LEN) +1); pg_anz + (pg_anz==3 && !0$(VIRTUAL_BOOT_PARTITION)) + (pg_anz==5 && !0$(VIRTUAL_BOOT_PARTITION))*3 + (pg_anz==6 && !0$(VIRTUAL_BOOT_PARTITION))*2 + (pg_anz == 7 && !0$(VIRTUAL_BOOT_PARTITION))" | bc > BootPages.dat
# without the last flash location used for version number of optiboot,
# the following computation for BootPages is also possible:
#	echo "pg_anz=($(shell $(SIZE) -C $(PROGRAM)x.elf | grep "Program:" | cut -c 10-16)+$(BOOT_PAGE_LEN)-2)/$(BOOT_PAGE_LEN); pg_anz + (pg_anz==3 && !0$(VIRTUAL_BOOT_PARTITION)) + (pg_anz==5 && !0$(VIRTUAL_BOOT_PARTITION))*3 + (pg_anz==6 && !0$(VIRTUAL_BOOT_PARTITION))*2 + (pg_anz == 7 && !0$(VIRTUAL_BOOT_PARTITION))" | bc > BootPages.dat

# With the file BootPages.dat and the the $(BOOT_PAGE_LEN) we can compute the 
# Start Address of the bootloader depending on the $(FLASH_SIZE) 
BL_StartAdr.dat: $(OBJ) $(PROGRAM)x.elf BootPages.dat
	echo "obase=16;($(FLASH_SIZE) - $(shell cat BootPages.dat)*$(BOOT_PAGE_LEN))" | bc > BL_StartAdr.dat
	rm $(PROGRAM)x.elf

# Generate the final $(PROGRAM).elf file at the right Start Address,
# which is the base to generate the $(PROGRAM).hex and $(PROGRAM).lst files.
$(PROGRAM).elf: $(OBJ) baudcheck  BL_StartAdr.dat
	@echo "Boot Loader start address: 0x$(shell cat BL_StartAdr.dat)"
	$(CC) $(CFLAGS) $(COMMON_OPTIONS) $(LDSECTIONS) \
        -Wl,--section-start=.text=0x$(shell cat BL_StartAdr.dat) $(LDFLAGS) -o $(PROGRAM).elf $< $(LIBS)
	$(SIZE) $(PROGRAM).elf

# remove all generated files
clean:
	rm -rf *.o *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex *.tmp.sh *.dat

# With the Bootpages.dat file we can set the required BOOTSZ1 and BOOTSZ0 bits, which are
# combined to BOOTSZ (0 for eight pages, 1 for four pages, 2 for two pages and 3 for one page)
# This BOOTSZ.dat is taken by the Makefile.isp file to correct the HFUSE or EFUSE.
BOOTSZ.dat: $(PROGRAM).elf BootPages.dat
	@echo "Requires $(shell cat BootPages.dat) Boot Pages, $(BOOT_PAGE_LEN) Bytes each"
	@echo "BOOTSZ=$(shell echo "pg_anz=(`$(SIZE) -C $(PROGRAM).elf | grep "Program:" | cut -c 10-16`/$(BOOT_PAGE_LEN) +1); 0 + (pg_anz<5) + (pg_anz<3) + (pg_anz<2)" | bc)"
	@echo   "$(shell echo "pg_anz=(`$(SIZE) -C $(PROGRAM).elf | grep "Program:" | cut -c 10-16`/$(BOOT_PAGE_LEN) +1); 0 + (pg_anz<5) + (pg_anz<3) + (pg_anz<2)" | bc)" > BOOTSZ.dat

# add some options to the end of the .lst file as comment
add_options: hex_copy
	@echo -e "\n; MCU_TARGET = $(MCU_TARGET)\n; SOURCE_TYPE=$(SOURCE_TYPE)\n; AVR_FREQ= $(AVR_FREQ)\n; BAUD_RATE=$(BAUD_RATE)\n; LED_START_FLASHES=$(LED_START_FLASHES)\n; SOFT_UART=$(SOFT_UART)\n; UART_RX=$(UART_RX)\n; UART_TX=$(UART_TX)\n; LED_DATA_FLASH=$(LED_DATA_FLASH)\n; LED=$(LED)\n; UART$(UART)\n; SUPPORT_EEPROM=$(SUPPORT_EEPROM)\n; FORCE_WATCHDOG=$(FORCE_WATCHDOG)">> $(PROGRAM)_$(TARGET).lst

# copy the  .lst and .hex files to files which identify the target
hex_copy: $(PROGRAM).lst $(PROGRAM).hex
	cp $(PROGRAM).lst $(PROGRAM)_$(TARGET).lst
	cp $(PROGRAM).hex $(PROGRAM)_$(TARGET).hex


# allways generate a $(PROGRAM)_$(TARGET).lst file, if a .hex file is generated from $(PROGRAM).elf
%.lst: $(PROGRAM).elf BOOTSZ.dat
	$(OBJDUMP) -h -S $< > $(PROGRAM).lst

%.hex: $(PROGRAM).elf BOOTSZ.dat
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O ihex $< $(PROGRAM).hex
# you can ignore the .version section with the following command
#	$(OBJCOPY) -j .text -j .data -R .version -O ihex $< $(PROGRAM).hex

%.srec: $(PROGRAM).elf BOOTSZ.dat
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O srec $< $@

%.bin: $(PROGRAM).elf BOOTSZ.dat
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O binary $< $@
