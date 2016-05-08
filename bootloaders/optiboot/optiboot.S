/**********************************************************************************/
/* Assembler-Version of Optiboot created by K.-H. Kuebbeler (kh_kuebbeler@web.de) */
/* This Version can support additional EEprom read/write  with blinking LED       */
/* within 512 bytes. */
/**********************************************************************************/

/**********************************************************/
/* Optiboot bootloader for Arduino                        */
/*                                                        */
/* http://optiboot.googlecode.com                         */
/*                                                        */
/* Arduino-maintained version : See README.TXT            */
/* http://code.google.com/p/arduino/                      */
/*  It is the intent that changes not relevant to the     */
/*  Arduino production envionment get moved from the      */
/*  optiboot project to the arduino project in "lumps."   */
/*                                                        */
/* Heavily optimised bootloader that is faster and        */
/* smaller than the Arduino standard bootloader           */
/*                                                        */
/* Enhancements:                                          */
/*   Fits in 512 bytes, saving 1.5K of code space         */
/*   Background page erasing speeds up programming        */
/*   Higher baud rate speeds up programming               */
/*   Written almost entirely in C                         */
/*   Customisable timeout with accurate timeconstant      */
/*   Optional virtual UART. No hardware UART required.    */
/*   Optional virtual boot partition for devices without. */
/*                                                        */
/* What you lose:                                         */
/*   Implements a skeleton STK500 protocol which is       */
/*     missing several features including EEPROM          */
/*     programming and non-page-aligned writes            */
/*   High baud rate breaks compatibility with standard    */
/*     Arduino flash settings                             */
/*                                                        */
/* Fully supported:                                       */
/*   ATmega168 based devices  (Diecimila etc)             */
/*   ATmega328P based devices (Duemilanove etc)           */
/*                                                        */
/* Beta test (believed working.)                          */
/*   ATmega8 based devices (Arduino legacy)               */
/*   ATmega328 non-picopower devices                      */
/*   ATmega644P based devices (Sanguino)                  */
/*   ATmega1284P based devices                            */
/*   ATmega1280 based devices (Arduino Mega)              */
/*                                                        */
/* Alpha test                                             */
/*   ATmega32                                             */
/*                                                        */
/* Work in progress:                                      */
/*   ATtiny84 based devices (Luminet)                     */
/*                                                        */
/* Does not support:                                      */
/*   USB based devices (eg. Teensy, Leonardo)             */
/*                                                        */
/* Assumptions:                                           */
/*   The code makes several assumptions that reduce the   */
/*   code size. They are all true after a hardware reset, */
/*   but may not be true if the bootloader is called by   */
/*   other means or on other hardware.                    */
/*     No interrupts can occur                            */
/*     UART and Timer 1 are set to their reset state      */
/*     SP points to RAMEND                                */
/*                                                        */
/* Code builds on code, libraries and optimisations from: */
/*   stk500boot.c          by Jason P. Kyle               */
/*   Arduino bootloader    http://arduino.cc              */
/*   Spiff's 1K bootloader http://spiffie.org/know/arduino_1k_bootloader/bootloader.shtml */
/*   avr-libc project      http://nongnu.org/avr-libc     */
/*   Adaboot               http://www.ladyada.net/library/arduino/bootloader.html */
/*   AVR305                Atmel Application Note         */
/*                                                        */

/* Copyright 2013-2015 by Bill Westfield.                 */
/* Copyright 2010 by Peter Knight.                        */
/*                                                        */
/* This program is free software; you can redistribute it */
/* and/or modify it under the terms of the GNU General    */
/* Public License as published by the Free Software       */
/* Foundation; either version 2 of the License, or        */
/* (at your option) any later version.                    */
/*                                                        */
/* This program is distributed in the hope that it will   */
/* be useful, but WITHOUT ANY WARRANTY; without even the  */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A   */
/* PARTICULAR PURPOSE.  See the GNU General Public        */
/* License for more details.                              */
/*                                                        */
/* You should have received a copy of the GNU General     */
/* Public License along with this program; if not, write  */
/* to the Free Software Foundation, Inc.,                 */
/* 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA */
/*                                                        */
/* Licence can be viewed at                               */
/* http://www.fsf.org/licenses/gpl.txt                    */
/*                                                        */
/**********************************************************/


/**********************************************************/
/*                                                        */
/* Optional defines:                                      */
/*                                                        */
/**********************************************************/
/*                                                        */
/* BIG_BOOT:                                              */
/* Build a 1k bootloader, not 512 bytes. This turns on    */
/* extra functionality.                                   */
/*                                                        */
/* BAUD_RATE:                                             */
/* Set bootloader baud rate.                              */
/*                                                        */
/* LUDICROUS_SPEED:                                       */
/* 230400 baud :-)                                        */
/*                                                        */
/* SOFT_UART:                                             */
/* Use AVR305 soft-UART instead of hardware UART.         */
/*                                                        */
/* LED_START_FLASHES:                                     */
/* Number of LED flashes on bootup.                       */
/*                                                        */
/* LED_DATA_FLASH:                                        */
/* Flash LED when transferring data. For boards without   */
/* TX or RX LEDs, or for people who like blinky lights.   */
/*                                                        */
/* SUPPORT_EEPROM:                                        */
/* Support reading and writing from EEPROM. This is not   */
/* used by Arduino, so off by default.                    */
/*                                                        */
/* TIMEOUT_MS:                                            */
/* Bootloader timeout period, in milliseconds.            */
/* 500,1000,2000,4000,8000 supported.                     */
/*                                                        */
/* UART:                                                  */
/* UART number (0..n) for devices with more than          */
/* one hardware uart (644P, 1284P, etc)                   */
/*                                                        */
/**********************************************************/

/**********************************************************/
/* Version Numbers!                                       */
/*                                                        */
/* Arduino Optiboot now includes this Version number in   */
/* the source and object code.                            */
/*                                                        */
/* Version 3 was released as zip from the optiboot        */
/*  repository and was distributed with Arduino 0022.     */
/* Version 4 starts with the arduino repository commit    */
/*  that brought the arduino repository up-to-date with   */
/*  the optiboot source tree changes since v3.            */
/* Version 5 was created at the time of the new Makefile  */
/*  structure (Mar, 2013), even though no binaries changed*/
/* It would be good if versions implemented outside the   */
/*  official repository used an out-of-seqeunce version   */
/*  number (like 104.6 if based on based on 4.5) to       */
/*  prevent collisions.                                   */
/*                                                        */
/**********************************************************/

/**********************************************************/
/* Edit History:					  */
/*			   				  */
/* Aug 2014						  */
/* 6.2 WestfW: make size of length variables dependent    */
/*              on the SPM_PAGESIZE.  This saves space    */
/*              on the chips where it's most important.   */
/* 6.1 WestfW: Fix OPTIBOOT_CUSTOMVER (send it!)	  */
/*             Make no-wait mod less picky about	  */
/*               skipping the bootloader.		  */
/*             Remove some dead code			  */
/*							  */
/* Jun 2014						  */
/* 6.0 WestfW: Modularize memory read/write functions	  */
/*             Remove serial/flash overlap		  */
/*              (and all references to NRWWSTART/etc)	  */
/*             Correctly handle pagesize > 255bytes       */
/*             Add EEPROM support in BIGBOOT (1284)       */
/*             EEPROM write on small chips now causes err */
/*             Split Makefile into smaller pieces         */
/*             Add Wicked devices Wildfire		  */
/*             Move UART=n conditionals into pin_defs.h	  */
/*             Remove LUDICOUS_SPEED option		  */
/*             Replace inline assembler for .version	  */
/*              and add OPTIBOOT_CUSTOMVER for user code  */
/*             Fix LED value for Bobuino (Makefile)       */
/*             Make all functions explicitly inline or    */
/*              noinline, so we fit when using gcc4.8	  */
/*             Change optimization options for gcc4.8	  */
/*             Make ENV=arduino work in 1.5.x trees.      */
/* May 2014                                               */
/* 5.0 WestfW: Add support for 1Mbps UART                 */
/* Mar 2013                                               */
/* 5.0 WestfW: Major Makefile restructuring.              */
/*             See Makefile and pin_defs.h                */
/*             (no binary changes)                        */
/*                                                        */
/* 4.6 WestfW/Pito: Add ATmega32 support                  */
/* 4.6 WestfW/radoni: Don't set LED_PIN as an output if   */
/*                    not used. (LED_START_FLASHES = 0)   */
/* Jan 2013						  */
/* 4.6 WestfW/dkinzer: use autoincrement lpm for read     */
/* 4.6 WestfW/dkinzer: pass reset cause to app in R2      */
/* Mar 2012                                               */
/* 4.5 WestfW: add infrastructure for non-zero UARTS.     */
/* 4.5 WestfW: fix SIGNATURE_2 for m644 (bad in avr-libc) */
/* Jan 2012:                                              */
/* 4.5 WestfW: fix NRWW value for m1284.                  */
/* 4.4 WestfW: use attribute OS_main instead of naked for */
/*             main().  This allows optimizations that we */
/*             count on, which are prohibited in naked    */
/*             functions due to PR42240.  (keeps us less  */
/*             than 512 bytes when compiler is gcc4.5     */
/*             (code from 4.3.2 remains the same.)        */
/* 4.4 WestfW and Maniacbug:  Add m1284 support.  This    */
/*             does not change the 328 binary, so the     */
/*             version number didn't change either. (?)   */
/* June 2011:                                             */
/* 4.4 WestfW: remove automatic soft_uart detect (didn't  */
/*             know what it was doing or why.)  Added a   */
/*             check of the calculated BRG value instead. */
/*             Version stays 4.4; existing binaries are   */
/*             not changed.                               */
/* 4.4 WestfW: add initialization of address to keep      */
/*             the compiler happy.  Change SC'ed targets. */
/*             Return the SW version via READ PARAM       */
/* 4.3 WestfW: catch framing errors in getch(), so that   */
/*             AVRISP works without HW kludges.           */
/*  http://code.google.com/p/arduino/issues/detail?id=368n*/
/* 4.2 WestfW: reduce code size, fix timeouts, change     */
/*             verifySpace to use WDT instead of appstart */
/* 4.1 WestfW: put version number in binary.		  */
/**********************************************************/

#ifndef __ASSEMBLER__
 #define __ASSEMBLER__
#endif
#include <avr/io.h>
// #include <avr/common.h>
// #include <avr/eeprom.h>
#include "stk500.h"
#include "pin_defs.h"

#define OPTIBOOT_MAJVER 6
#define OPTIBOOT_MINVER 2
/*
 * OPTIBOOT_CUSTOMVER should be defined (by the makefile) for custom edits
 * of optiboot.  That way you don't wind up with very different code that
 * matches the version number of a "released" optiboot.
 */

#if !defined(OPTIBOOT_CUSTOMVER)
 #define OPTIBOOT_CUSTOMVER 100
#endif


#ifndef LED_START_FLASHES
 #define LED_START_FLASHES 0
#endif
#ifndef LED_DATA_FLASH
 #define LED_DATA_FLASH 0
#endif
 /*
 * RAMSTART should be self-explanatory.  It's bigger on parts with a
 * lot of peripheral registers.
 */
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__)
 #define RAMSTART (0x100)
 #define NRWWSTART (0x3800)
#elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32__)
 #define NRWWSTART (0x7000)
#elif defined (__AVR_ATmega644P__)
 #define NRWWSTART (0xE000)
 #define SELFPRGEN SPMEN		/* use different name of SELFPRGEN bit */
 // correct for a bug in avr-libc
 #undef SIGNATURE_2
 #define SIGNATURE_2 0x0A
#elif defined (__AVR_ATmega1284P__)
 #define NRWWSTART (0xE000)
#elif defined(__AVR_ATtiny84__)
 #define NRWWSTART (0x0000)
#elif defined(__AVR_ATmega1280__)
 #define RAMSTART (0x200)
 #define NRWWSTART (0xE000)
#define SELFPRGEN SPMEN		/* use different name of SELFPRGEN bit */
 #elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega88__)
 #define NRWWSTART (0x1800)
#endif
#ifndef SPMCSR
 #define SPMCSR SPMCR			/* use different name of SPM register */
#endif
#ifndef SELFPRGEN
 #define SELFPRGEN SPMEN		/* use different name of SELFPRGEN bit */
#endif

#if defined(__AVR_ATmega8__) || defined (__AVR_ATmega32__) || defined(__AVR_ATmega16__)
 // bits in EECR has other names
 #define EEMPE EEMWE
 #define EEPE EEWE
#endif
/*
 * We can use memory to hold data before the flash data buffer
 * Currently the reset vectors are hold in registers r2:r2 and r8:r9
 * So no additional space is required before the data buffer
 */
#define Buff    0	/* RAMSTART offset to data buffer */

/* Virtual boot partition support */
#ifdef VIRTUAL_BOOT_PARTITION
 #define rstVect0_sav 4
 #define rstVect1_sav 5
 #define saveVect0_sav 6
 #define saveVect1_sav 7
// Vector to save original reset jump:
//   SPM Ready is least probably used, so it's default
//   if not, use old way WDT_vect_num,
//   or simply set custom save_vect_num in Makefile using vector name
//   or even raw number.
 #if !defined (save_vect_num)
  #if defined (SPM_RDY_vect_num)
   #define save_vect_num (SPM_RDY_vect_num)
  #elif defined (SPM_READY_vect_num)
   #define save_vect_num (SPM_READY_vect_num)
  #elif defined (WDT_vect_num)
  #define save_vect_num (WDT_vect_num)
 #else
  #error Cant find SPM or WDT interrupt vector for this CPU
 #endif
 #endif //save_vect_num
 // check if it's on the same page (code assumes that)
 #if (SPM_PAGESIZE <= save_vect_num)
  #error Save vector not in the same page as reset!
 #endif

 #if FLASHEND > 8192
  // AVRs with more than 8k of flash have 4-byte vectors, and use jmp.
  //  We save only 16 bits of address, so devices with more than 128KB
  //  may behave wrong for upper part of address space.
  #define rstVect0 2
  #define rstVect1 3
  #define save_vect_addr (save_vect_num*4)
 #else
  // AVRs with up to 8k of flash have 2-byte vectors, and use rjmp.
  #define rstVect0 0
  #define rstVect1 1
  #define save_vect_addr (save_vect_num*2)
 #endif
#else
 #define appstart_vec (0)
#endif // VIRTUAL_BOOT_PARTITION


/*
 * Handle devices with up to 4 uarts (eg m1280.)  Rather inelegantly.
 * Note that mega8/m32 still needs special handling, because ubrr is handled
 * differently.
 */
#if UART == 0
# define UART_SRA UCSR0A
# define UART_SRB UCSR0B
# define UART_SRC UCSR0C
# define UART_SRL UBRR0L
# define UART_UDR UDR0
#elif UART == 1
#if !defined(UDR1)
#error UART == 1, but no UART1 on device
#endif
# define UART_SRA UCSR1A
# define UART_SRB UCSR1B
# define UART_SRC UCSR1C
# define UART_SRL UBRR1L
# define UART_UDR UDR1
#elif UART == 2
#if !defined(UDR2)
#error UART == 2, but no UART2 on device
#endif
# define UART_SRA UCSR2A
# define UART_SRB UCSR2B
# define UART_SRC UCSR2C
# define UART_SRL UBRR2L
# define UART_UDR UDR2
#elif UART == 3
#if !defined(UDR3)
#error UART == 3, but no UART3 on device
#endif
# define UART_SRA UCSR3A
# define UART_SRB UCSR3B
# define UART_SRC UCSR3C
# define UART_SRL UBRR3L
# define UART_UDR UDR3
#endif

/* Watchdog settings */
#define WATCHDOG_OFF    (0)
#define WATCHDOG_16MS   (_BV(WDE))
#define WATCHDOG_32MS   (_BV(WDP0) | _BV(WDE))
#define WATCHDOG_64MS   (_BV(WDP1) | _BV(WDE))
#define WATCHDOG_125MS  (_BV(WDP1) | _BV(WDP0) | _BV(WDE))
#define WATCHDOG_250MS  (_BV(WDP2) | _BV(WDE))
#define WATCHDOG_500MS  (_BV(WDP2) | _BV(WDP0) | _BV(WDE))
#define WATCHDOG_1S     (_BV(WDP2) | _BV(WDP1) | _BV(WDE))
#define WATCHDOG_2S     (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE))
#if defined(WDP3)
 #define WATCHDOG_4S     (_BV(WDP3) | _BV(WDE))
 #define WATCHDOG_8S     (_BV(WDP3) | _BV(WDP0) | _BV(WDE))
#else
 #define WATCHDOG_4S     (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE))	/* 2 seconds are max */
 #define WATCHDOG_8S     (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE))	/* 2 seconds are max */
#endif



	.section	.version
optiboot_version:
	.byte	OPTIBOOT_MINVER
	.byte	OPTIBOOT_MAJVER+OPTIBOOT_CUSTOMVER
#ifdef RADIO_UART
 #error RADIO_UART is not supported by the assembler version of optiboot!
#endif

;***************************************************************
;***************************************************************
	.section .text
	.func optiboot
	.global optiboot

optiboot:
;	AIN	r28, SPL
;	AIN	r29, SPH
	cli
optiboot2:
	cli
	eor	r1, r1
#if defined(__AVR_ATmega8__) || defined (__ATmega16__) || defined (__AVR_ATmega32__)
	ldi	r24,hi8(RAMEND)
	AOUT	SPH, r24
	ldi	r24,lo8(RAMEND)
	AOUT	SPL, r24
#endif

  /*
   * With wireless flashing it's possible that this is a remote
   * board that's hard to reset manually.  In this case optiboot can
   * force the watchdog to run before jumping to userspace, so that if
   * a buggy program is uploaded, the board resets automatically.  We
   * still use the watchdog to reset the bootloader too.
   */

//#define reset_cause (*(uint8_t *) (RAMEND - 16 - 4))
//#define marker (*(uint32_t *) (RAMEND - 16 - 3))

 ; the reset cause is hold in GPIOR0 (or OCR2 for ATmega8 or ATmega32)
#ifdef GPIOR0
 #define RESET_CAUSE GPIOR0
#else
 #define RESET_CAUSE OCR2
#endif

//#define RESET_CAUSE GPIOR1

	AIN	r24, MCUSR
	AOUT	MCUSR, r1	; MCUSR = 0
	AOUT	RESET_CAUSE, r24	; save reason of restart (MCUSR) in IO register

#ifdef FORCE_WATCHDOG
 #define marker 16-3
 #ifdef GPIOR1
  #define MARKER1 GPIOR1
  #define MARKER2 GPIOR2
 #else
  #define MARKER1 OCR1BL
  #define MARKER2 OCR1BH
 #endif
 #define MARKER3 ICR1L
 #define MARKER4 ICR1H

//if ((ch & _BV(WDRF)) && marker == 0xdeadbeef) {
//    marker = 0;
//    appStart(reset_cause);
//  }
	andi	r24, (1<<WDRF)
	breq	no_app_start
#if 0
	AIN	r20, MARKER1		; MARKER1:4 == 0xDEADBEEF
	cpi	r20, 0xDE
	AIN	r20, MARKER2
	sbci	r20, 0xAD
	AIN	r20, MARKER3
	sbci	r20, 0xBE
	AIN	r20, MARKER4
	sbci	r20, 0xEF
	brne	no_app_start
#endif
	AOUT	MARKER1, r1		; marker = 0
	AOUT	MARKER2, r1		;
	AOUT	MARKER3, r1		;
	AOUT	MARKER4, r1		;
	AIN	r24, RESET_CAUSE
	rjmp	appStart
no_app_start:
	ldi	r20, 0xDE		; marker = 0xdeadbeef
	AOUT	MARKER1
	ldi	r20, 0xAD
	AOUT	MARKER2
	ldi	r20, 0xBE
	AOUT	MARKER3
	ldi	r20, 0xEF
	AOUT	MARKER4
	rjmp	try_loader
#else
  // save the reset flags in the designated register
  //  This can be saved in a main program by putting code in .init0 (which
  //  executes before normal c init code) to save R2 to a global variable.
	andi	r24, (1<<WDRF)|(1<<PORF)|(1<<BORF)  ;0x0D	
	breq	try_loader
	AIN	r24, RESET_CAUSE
#endif
;***************************************************************
appStart:

#ifdef FORCE_WATCHDOG
	ldi	r20, WATCHDOG_OFF
#else
	ldi	r20, WATCHDOG_4S
#endif
	rcall	watchdogConfig		; WATCHDOG_OFF
#if 0
;##############################################################
	; talk to the application 
	ldi	ZL,hi8(1000)
	AOUT	GPIOR2, ZH
	AOUT	ICR1H, ZH
	ldi	ZL,lo8(1000)
	AOUT	GPIOR1, ZH
	AOUT	ICR1L, ZH
;##############################################################
#endif

#ifdef	VIRTUAL_BOOT_PARTITION
	ldi	ZL, save_vect_addr/2		; // Jump to WDT vector (jmp or rjmp table)
	eor	ZH, ZH
#else
       	eor	ZL, ZL	; // Jump to RST vector	 0x0000
      	eor	ZH, ZH
#endif
       	ijmp

;***************************************************************
try_loader:

#ifndef SOFT_UART
 #if defined(PORTD) && defined(PD1)
	cbi	_SFR_IO_ADDR(PORTD), PD0	; RXD, disable PullUp
	cbi	_SFR_IO_ADDR(PORTD), PD1	; TX0   ????
 #endif
 #if defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined (__AVR_ATmega32__)
  #define U2X0 U2X
  #define RXEN0 RXEN
  #define TXEN0 TXEN
  #define UART_SRA UCSRA
  #define UART_SRB UCSRB
  #define UART_SRL UBRRL
 #endif
 #define BAUD_DIV ((F_CPU + BAUD_RATE * 4) / (BAUD_RATE * 8) - 1)
 #if BAUD_DIV > 255
  #undef BAUD_DIV
  #define BAUD_DIV ((F_CPU + BAUD_RATE * 8) / (BAUD_RATE * 16) - 1)
  #if BAUD_DIV > 250
   #error Unachievable baud rate (too slow) BAUD_RATE
  #endif // baud rate slow check
 	ldi	r24, (0<<U2X0)
 #else
	ldi	r24, (1<<U2X0)
 #endif
	sts	UART_SRA, r24
	ldi	r24, (1<<RXEN0)|(1<<TXEN0)	;0x18	
	sts	UART_SRB, r24
 #if defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined (__AVR_ATmega32__)
	ldi	r25, (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0)	;config UART
	sts	UCSRC, r25
 #else
	ldi	r25, (1<<UCSZ00)|(1<<UCSZ01)	;0x06
	sts	UART_SRC, r25
 #endif
	ldi	r25, BAUD_DIV	; 0x10
	sts	UART_SRL, r25
#endif
	ldi	r20, WATCHDOG_1S	;0x0E
	rcall	watchdogConfig

#if (LED_START_FLASHES > 0) || (LED_DATA_FLASH > 0)
	sbi	_SFR_IO_ADDR(LED_DDR), LED
#endif
#ifdef SOFT_UART
	sbi	_SFR_IO_ADDR(UART_DDR), UART_TX_BIT	; set TX bit as output
#endif
	ldi	r18, lo8(RAMSTART+Buff)	; r18:r19 = RAMSTART
	ldi	r19, hi8(RAMSTART+Buff)	; 

#if LED_START_FLASHES > 0
 #if LED_START_FLASHES > 1
;##	ldi	r23, LED_START_FLASHES
	ldi	r23, LED_START_FLASHES
fl_lop:
 #endif
	sbi	_SFR_IO_ADDR(LED_PORT), LED
	rcall	wait_T1ov
	cbi	_SFR_IO_ADDR(LED_PORT), LED
 #if LED_START_FLASHES > 1
	rcall	wait_T1ov
	subi	r23, 1
	brne	fl_lop		; while (--count)
 #endif
#endif

;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  /* Forever loop */
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
get_nextp:
	rcall	getch
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	cpi	r24, STK_GET_PARAMETER		; 'A'
	brne	ck_SET_DEV
// handle get parameter instruction
	rcall	getch
	mov	r21, r24
	rcall	verifySpace

 	ldi	r24, OPTIBOOT_MINVER	; 0x03	
	cpi	r21, 0x82	; 130
	breq	to_putch	; rcall putch, rjmp put_ok
	ldi	r24, 0x03	; answer generic 0x03
	cpi	r21, 0x81	; 129
	brne	to_putch	; rcall putch, rjmp put_ok
	ldi	r24, OPTIBOOT_MAJVER+OPTIBOOT_CUSTOMVER
to_putch:
       	rcall	putch
	rjmp	put_ok
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
ck_SET_DEV:
	ldi	r20, 20
	cpi	r24, STK_SET_DEVICE		; 'B'
       	breq	to_getNch	; STK set device is ignored
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	ldi	r20, 5
   	cpi	r24, STK_SET_DEVICE_EXT		; 'E'
	brne	ck_LA
; STK set device ext is ignored
to_getNch:
	rcall	getNch
to_put_ok:
	rjmp	put_ok
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
ck_LA:
	cpi	r24, STK_LOAD_ADDRESS		; 'U'
   	brne	ck_UNI
; **** STK load address
	rcall	getch
	mov	r4, r24
	rcall	getch
	mov	r5, r24		; r4:5 is load address
	add	r4, r4		; newAddress << 1
	adc	r5, r5
#ifdef RAMPZ
	adc	r1, r1
	AOUT	RAMPZ, r1
	eor	r1, r1
#endif
	rjmp	ver_put 
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
ck_UNI:
       	cpi	r24, STK_UNIVERSAL 	; 'V'
       	brne	ck_PP
	ldi	r20, 4		; getNch(4)
	rcall	getNch
 	ldi	r24, 0
	rjmp	to_putch	; rcall putch, rjmp put_ok
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
ck_PP:
  	cpi	r24, STK_PROG_PAGE 	; 'd'
	breq	is_PROG
	rjmp	ck_READP
is_PROG:
    /* Write memory, length is big endian and is in bytes */
	rcall	get_length	; r16:r17 is length

	rcall	getch	
    // PROGRAM PAGE - we support flash and optional EEPROM programming
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#if 0
	ldi	r30, 0
	cpi	r24, 'F'	;STK_READ_FUSE	; 'r'
	breq	read_fuse
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	ldi	r30, 1
	cpi	r24, 'r'	;STK_READ_LOCK	; 's'
	breq	read_fuse
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	ldi	r30, 3
	cpi	r24, 'N'	;STK_READ_HFUSE 	; 's'
	breq	read_fuse
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	ldi	r30, 2
	cpi	r24, 'Q'	;STK_READ_FUSE_EXT	; 'w'
	brne	ee_check
read_fuse:
	ldi	r31, 0		; upper bits are allways zero
	ldi	r24, (1<<BLBSET) | (1<<SELFPRGEN)
	AOUT	SPMCSR, r24
	lpm
	mov	r24, r0
	rjmp	to_putch	; rcall putch; rjmp wr_ok
#endif
ee_check:
#ifdef SUPPORT_EEPROM
	subi	r24, 'E'	; type = getch() - 'E'
	mov	r6, r24

    	breq	no_pg_erase	; if (type)
#endif
;**	cp	r4, r1		; lo8(NRWWSTART) allways 0
	ldi	r24, hi8(NRWWSTART) ; 0x70
;**	cpc	r5, r24
;**	brcc	no_pg_erase	; if (address < NRWWSTART)
	cp	r5, r24		; lo8() is allways zero
	brsh	no_pg_erase	; if (address < NRWWSTART)
 // If we are in RWW section, immediately start page erase
	rcall	boot_page_erase
 // While that is going on, read in page contents
no_pg_erase:
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	movw	YL, r18		; buf16Ptr (r28:r29) = RAMSTART+Buff
fill_buf:
	rcall	getch		; call next data from serial
	st	Y+, r24		; *bufPtr++ = getch()
	sbiw	r26, 1		; length = length - 1
	brne	fill_buf
	movw	r26, r16	; set length back to start value

	; SRAM of ATmega is filled with data
#ifdef SUPPORT_EEPROM
	cpse	r6, r1		; r6 == 0, is EEprom write
	rjmp	write_flash	; if (!type)
; is EEprom write
	rcall	verifySpace
	movw	r24, r4		; addrPtr = address
	movw	YL, r18		; buf16Ptr (r28:r29) = RAMSTART+Buff
wrlop2:
     	wdr		; watchdogReset();
w_ee:
  	sbic	_SFR_IO_ADDR(EECR), EEPE	; while (!eeprom_is_ready())
   	rjmp	w_ee
	AOUT	EEARH, r25	; EEAR = addrPtr++
	AOUT	EEARL, r24
	adiw	r24, 1

	ld	r14, Y+				; *bufPtr++
	AOUT	EEDR, r14
	sbi	_SFR_IO_ADDR(EECR), EEMPE
	sbi	_SFR_IO_ADDR(EECR), EEPE	; /* Start eeprom write by setting EEPE */
	sbiw	r26, 1		; length = length - 1
	brne	wrlop2
	; eeprom write is finished
	rjmp	put_ok
#endif		/* SUPPORT_EEPROM */
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
write_flash:
;**	cp	r4, r1			; lo8(NRWWSTART) is 0 
	ldi	ZH, hi8(NRWWSTART) ; 0x70
;**	cpc	r5, ZH
;**	brcs	no_erase1		;if (address >= NRWWSTART)
	cp	r5, ZH			; hi8(NRWWSTART) lo8() is allways zero
	brlo	no_erase1
        // If we are in NRWW section, page erase has to be delayed until now.
        // Todo: Take RAMPZ into account (not doing so just means that we will
        //  treat the top of both "pages" of flash as NRWW, for a slight speed
        //  decrease, so fixing this is not urgent.)

	rcall	boot_page_erase
no_erase1:
	rcall	verifySpace		; // Read command terminator, start reply
        // If only a partial page is to be programmed, the erase might not be complete.
        // So check that here
	rcall	wait_flash_ready

#ifdef VIRTUAL_BOOT_PARTITION
 #warning RESET vector will be patched!
 #ifdef RAMPZ
	AIN	r2, RAMPZ	; upper address bits in RAMPZ must be 0
	cp	r1, r2
	; RAMPZ is zero, when carry is unset
 #endif
	cpc	r1, r4
	cpc	r1, r5
	brcs	no_patch1	; address not zero, no patch
	// address is zero!
        // This is the reset vector page. We need to live-patch the code so the
        // bootloader runs.
        //
        // Move RESET vector to WDT vector
 #if Buff == 0
	movw	YL, r18		; buf16Ptr (r28:r29) = RAMSTART+Buff
 #else
	ldi	YL, lo8(RAMSTART)
	ldi	YH, hi8(RAMSTART)
 #endif
 #if FLASHEND > 8192
 /*
  * We assume, that the vector table is filled with jmp instructions.
  * But this ist not checked!! If the table is "optimized" with rjmp
  * instructions, the two bytes loaded here, are  usually filled with
  * a nop instruction behind the rjmp.
  * Probably a patch program at the host computer, which send the 
  * programming data, is the better solution.
  * A patch program at the host can analyse the content of the hex data file
  * and create a new "patched" file. The patch program must know the
  * address of the bootloader and the interrupt vector number to save
  * the original reset vector content. 
  * The bootloader solution save the vector content for simulating
  + a correct verify pass after flashing.
  * But you can not repeat a separate verify pass without errors!!!
  */
	ldd	r2, Y+Buff+2	; rstVect = buff[2] | (buff[3]<<8)
	ldd	r3, Y+Buff+3
	movw	r30, r28	; Z = Y
	adiw	r30, (save_vect_num*2)
	adiw	r30, (save_vect_num*2)	; Z = Y + save_vect_num*4
	ldd	r8, Z+Buff+2	; wdtVect = buff[8] | (buff[9]<<8)
	ldd	r9, Z+Buff+3	; wdtVect = buff[8] | (buff[9]<<8)
	std	Z+Buff+2, r2	; new WDT vector = old reset vector
	std	Z+Buff+3, r3
	ldi	r24, lo8(gs(optiboot))
	std	Y+Buff+2, r24
	ldi	r24, hi8(gs(optiboot))
	std	Y+Buff+3, r24
 #else
	ldd	r2, Y+Buff	; rstVect = buff[0] | (buff[1]<<8)
	ldd	r3, Y+Buff+1
          // Add jump to bootloader at RESET vector
	ldd	r8, Y+Buff+save_vect_addr	; wdtVect = buff[8] | (buff[9]<<8)
	ldd	r9, Y+Buff+save_vect_addr+1	; wdtVect = buff[8] | (buff[9]<<8)
	movw	r24, r2		; rstVect
	sbiw	r24, save_vect_addr/2		; recalculate relative jmp, word address!
	std	Y+Buff+save_vect_addr, r24	; new WDT vector
	std	Y+Buff+save_vect_addr+1, r25
	ldi	r24, 0x7f
	std	Y+Buff, r24
	ldi	r24, 0xce	; rjmp 0x1d00 instruction
	std	Y+Buff+1, r24
 #endif

no_patch1:
#endif		/* VIRTUAL_BOOT_PARTITION */

	movw	ZL, r4		; addrPtr = address
	movw	YL, r18		; buf16Ptr (r28:r29) = RAMSTART+Buff
wr_lop1:
    	ld	r0, Y+		; *buf16Ptr++
	ld	r1, Y+
	ldi	r20, (1<<SELFPRGEN)
	; r0:r1 is data, Z r30:r31 is address, probably RAMPZ is also set
	rcall	do_spm		; AOUT SPMCSR, r20 ; spm
	eor	r1, r1
	adiw	ZL, 2		; increment address
	sbiw	r26, 2		; length = length - 2
	brne	wr_lop1
;**	cpi	r28, lo8(buff+SPM_PAGESIZE); 0x80
;**	ldi	r24, hi8(buff+SPM_PAGESIZE); 0x01	
;**	cpc	r29, r24
;**	brne	wr_lop1		; while(--ch)

	movw	ZL, r4		; addrPtr = address
        // Write from programming buffer
	ldi	r20, (1<<PGWRT)|(1<<SELFPRGEN)	; 0x05	
	rcall	do_spm		; AOUT SPMCSR, r20 ; spm
	rcall	wait_flash_ready
#if defined(RWWSRE)
       // Reenable read access to flash
	ldi	r20, (1<<RWWSRE)|(1<<SELFPRGEN)	; 0x11	
	rcall	do_spm		; AOUT SPMCSR, r20 ; spm
#endif
	rjmp	put_ok
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
ck_READP:
      	cpi	r24, STK_READ_PAGE	; 't'
	brne   	ck_READS
    /* Read memory block mode, length is big endian.  */
	rcall	get_length
     // READ PAGE - we only read flash and optional EEPROM
	rcall	getch
	mov	r23, r24	; type = getch()
	rcall	verifySpace
;	TODO: putNch()
	movw	ZL, r4		; addrPtr = address

#ifdef SUPPORT_EEPROM
	cpi	r23, 'E'	; 0x45
	brne	rd_lop
;     must be EEprom read
; read EEprom
rd_lop2:
	sbic	_SFR_IO_ADDR(EECR), EEPE
	rjmp	rd_lop2		; wait for EEprom ready
	AOUT	EEARH, ZH	; set EEprom address
	AOUT	EEARL, ZL
	adiw	ZL, 1 		; address + 1
	sbi	_SFR_IO_ADDR(EECR), EERE
	AIN	r24, EEDR		; read data from EEprom
	rcall	putch
check2:
	sbiw	r26, 1		; length-1
	brne	rd_lop2
	movw	r4, ZL		; set address to next element
	rjmp	put_ok
#endif

; - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;	read flash
rd_lop:

#ifdef RAMPZ
          // Since RAMPZ should already be set, we need to use EPLM directly.
          // Also, we can use the autoincrement version of lpm to update "address"
          //      do putch(pgm_read_byte_near(address++));
          //      while (--length);
          // read a Flash and increment the address (may increment RAMPZ)
	elpm	r24, Z+
#else
	lpm	r24, Z+
#endif
#define LenDecrement 1

#ifdef	VIRTUAL_BOOT_PARTITION
	// Undo vector patch in bottom page so verify passes
 #undef LenDecrement 
 #define LenDecrement 2
 #ifdef RAMPZ
	elpm	r25, Z+
	AIN	r21, RAMPZ
	cpse	r21,r1
	rjmp	nopatch		; RAMPZ not zero, no patch
 #else
	lpm	r25, Z+
 #endif
 #if FLASHEND > 8192
	cpi	ZL, 2
	brne	ck8
	movw	r24, r2			; old rstVect
ck8:
	cpi	ZL, save_vect_addr+2
	brne	nopatch
	movw	r24, r8 		; old wdtVect
 #else
	cpi	ZL, 0
	brne	ck8
	movw	r24, r2			; old rstVect
ck8:
	cpi	ZL, save_vect_addr
	brne	nopatch
	movw	r24, r8 		; old wdtVect
 #endif
nopatch:
	rcall	putch
	mov	r24, r25
#endif		/* VIRTUAL_BOOT_PARTITION */

	rcall	putch
	sbiw	r26, LenDecrement	; length - 1 or 2 bytes for VIRTUAL_BOOT_PARTITION
	brne	rd_lop
	movw	r4, ZL		; new address  ???
put_ok:
     	ldi	r24, STK_OK	; 0x10
       	rcall	putch
       	rjmp	get_nextp

;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
ck_READS:
     	cpi	r24, STK_READ_SIGN	; 'u'
	brne	ck_LEAVE
;	READ SIGN - return what Avrdude wants to hear
	rcall	verifySpace
	ldi	r24, SIGNATURE_0
	rcall	putch
	ldi	r24, SIGNATURE_1
	rcall	putch
	ldi	r24, SIGNATURE_2
	rjmp	to_putch	; rcall putch, rjmp put_ok
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
ck_LEAVE:
      	cpi	r24, STK_LEAVE_PROGMODE	; 'Q'
	brne	ver_put 
;  Adaboot no wait mod
	ldi	r20, WATCHDOG_16MS	; 0x08
	rcall	watchdogConfig
ver_put:
     	rcall	verifySpace
	rjmp	put_ok

;**********************************************************
getNch:		; call  getNch, r20 = count
	; repeat count times "call getch"
repeat_g:
     	rcall	getch		; do getch(); while (--count);
       	subi	r20, 1		; count - 1
     	brne	repeat_g
;** 	rjmp	verifySpace	; verifySpace(); let verifySpace return to netNch call

;**********************************************************
verifySpace:		/* 0x7fcc void verifySpace(void) { */
; use of r24,
     	rcall	getch		; if (getch() != CRC_EOP)
       	cpi	r24, CRC_EOP	; 0x20
       	breq	no_to
     	rcall	wait_timeout		;wait_timeout();
no_to:
       	ldi	r24, STK_INSYNC
;**    	rjmp	putch		; let putch return to verifySpace call


;**********************************************************
#ifdef SOFT_UART
 #include "soft_uart.S"
#else

 #if ((F_CPU + (BAUD_RATE * 4)) / (BAUD_RATE * 8) - 1) < 3
  #if BAUD_ERROR != 0 // permit high bitrates (ie 1Mbps@16MHz) if error is zero
   #error Unachievable baud rate (too fast) BAUD_RATE
  #endif
 #endif // baud rate fastn check
putch:	/* 0x7f98 , void putch(char ch) */
	lds	r25, UART_SRA	; while (!(UART_SRA & _BV(UDRE0)));
      	sbrs	r25, UDRE0
      	rjmp	putch
	sts	UART_UDR, r24		; UART_UDR = ch;
      	ret
;**********************************************************
	/* call getch fetch a character from serial interface */
	; return value: r24 = new character read
	; use r22, r25 (soft)
getch: 
 #if (LED_DATA_FLASH > 0) && defined(LED_PORT) && defined(LED)
	sbi	_SFR_IO_ADDR(LED_PORT), LED
 #endif
gtch1:
	AIN	r24, UART_SRA		; if (UART_SRA & _BV(RXC0)) {
     	sbrs	r24, RXC0
       	rjmp	gtch1			; no data received, wait
;	lds	r24, UART_SRA		; if (!(UART_SRA & _BV(FE0))) {
      	sbrs	r24, FE0
     	wdr		; watchdogReset();
       /*
         * A Framing Error indicates (probably) that something is talking
         * to us at the wrong bit rate.  Assume that this is because it
         * expects to be talking to the application, and DON'T reset the
         * watchdog.  This should cause the bootloader to abort and run
         * the application "soon", if it keeps happening.  (Note that we
         * don't care that an invalid char is returned...)
         */

 	lds	r24, UART_UDR	; ch = UART_UDR; return ch;
 #if (LED_DATA_FLASH > 0) && defined(LED_PORT) && defined(LED)
	cbi	_SFR_IO_ADDR(LED_PORT), LED
 #endif
       	ret
#endif	/* SOFT_UART */

;**********************************************************
;	rcall get_length get two bytes from serial inputi
;	result is r26:r27 = r16:r17  last:first byte
;	use r22, r25 (soft)
get_length:
	rcall	getch
	mov	r17, r24	; r17 = upper bits of length
	rcall	getch
	mov	r16, r24	; r16 = lower bits of length
	movw	r26, r16	; can be changed by sbiw or adiw
	ret

;**********************************************************
;	call wait_flash_ready wait for a idle Flash controller
;	use r0
wait_flash_ready:
       	AIN	r0, SPMCSR 
	sbrc	r0, SELFPRGEN
	rjmp	wait_flash_ready
	ret

;**********************************************************
;	rcall boot_page_erase let the flash controller erase a page
;	r4:r5 must contain the byte address of the flash page to be erased
;	Z (r30:r31) is destroyed  (copy from r4:r5)
;	r20 is used to setup the spm instruction
;	probably RAMPZ must be set before to extend the r4:r5 address
;	return is immediately, the flash controller is probably still busy
boot_page_erase:
;	rcall	wait_flash_ready
    	movw	ZL, r4		; __boot_page_erase_short((uint16_t)(void*)address)
	ldi	r20, (1<<PGERS)|(1<<SELFPRGEN)	; 0x03
;	second entry	***********************************
;	rcall do_spm
;	r20 must contain the spm command
;	no register is destroyed
do_spm:
	AOUT	SPMCSR, r20	; (1<<PGERS)|(SELFPRGEN)
	spm
	ret

;**********************************************************
;	rcall wait_timeout  set the watch dog timer to 16ms and wait for reset
wait_timeout:
     	ldi	r20, WATCHDOG_16MS
	rcall	watchdogConfig	;  watchdogConfig(WATCHDOG_16MS) 
lop77:
    	rjmp	lop77		; endless loop, watch Dog will reset!


;**********************************************************
;	rcall watchdogConfig set the watch dog timer to the time specified by r20
;	use r21
watchdogConfig: 	/* 0x7fe6 */
    	ldi	r21, (1<<WDCE) | (1<<WDE)	; 0x18
	AOUT	WDTCSR, r21	; (1<<WDCE) | (1<<WDE) ; watchdogConfig(x);
       	AOUT	WDTCSR, r20		; WDTCSR = x;
       	ret


;**********************************************************
#if LED_START_FLASHES > 0
; rcall wait_T1ov setup the timer1 to overflow in r24:r25 clock tics
; use  r22, r24:r25
wait_T1ov:
	ldi	r24, (1<<CS12)|(1<<CS10)	; internal clock, divide by 1024
	sts	TCCR1B, r24	
	ldi	r24, lo8(0xfffe - (F_CPU/(1024*16)))
	ldi	r25, hi8(0xfffe - (F_CPU/(1024*16)))
	AOUT	TCNT1H, r25		; set new counter value to TCNT1
	AOUT	TCNT1L, r24
 #if defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
	ldi	r22, (1<<TOV1)
	AOUT	TIFR, r22		; clear OV bit Timer 1
 #else
	sbi	_SFR_IO_ADDR(TIFR1), TOV1	; clear OV bit Timer1
 #endif
wt_ov:
#if 0
	; leave the wait for OV event loop, if data at the RX port are present
	AIN	r22, UART_SRA		; if (UART_SRA & _BV(RXC0)) {
     	sbrc	r22, RXC0
       	rjmp	wt_fin			; any character present at serial rx port
#endif
 #if defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
	AIN	r22, TIFR
	sbrc	r22, (1<<TOV1)
	rjmp	wt_ov
 #else
	sbis	_SFR_IO_ADDR(TIFR1), TOV1	; wait until OV bit is set again
	rjmp	wt_ov
 #endif
wt_fin:
     	wdr		; watchdogReset();
	ret
#endif


;**********************************************************
        .endfunc
