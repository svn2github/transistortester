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
/* OSCCAL_CORR:                                           */
/* The specified value is subtracted from the OSCCAL Byte */
/* to correct the internal RC-oscillator frequency        */
/* This option is only effectual, when the internal       */
/* Frequency generation of the ATmega is used             */
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

#define OPTIBOOT_MAJVER 6
#define OPTIBOOT_MINVER 2

/*
 * OPTIBOOT_CUSTOMVER should be defined (by the makefile) for custom edits
 * of optiboot.  That way you don't wind up with very different code that
 * matches the version number of a "released" optiboot.
 */

#if !defined(OPTIBOOT_CUSTOMVER)
 #define OPTIBOOT_CUSTOMVER 0
#endif

unsigned const int __attribute__((section(".version"))) 
optiboot_version = 256*(OPTIBOOT_MAJVER + OPTIBOOT_CUSTOMVER) + OPTIBOOT_MINVER;


#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

/*
 * Note that we use our own version of "boot.h"
 * <avr/boot.h> uses sts instructions, but this version uses out instructions
 * This saves cycles and program memory.  Sorry for the name overlap.
 */
#include "boot.h"


// We don't use <avr/wdt.h> as those routines have interrupt overhead we don't need.
#define wdt_reset() __asm__ __volatile__ ("wdr")

/*
 * pin_defs.h
 * This contains most of the rather ugly defines that implement our
 * ability to use UART=n and LED=D3, and some avr family bit name differences.
 */
#include "pin_defs.h"

/*
 * stk500.h contains the constant definitions for the stk500v1 comm protocol
 */
#include "stk500.h"

#include "check_fuses.h"

#ifdef LUDICROUS_SPEED
 #define BAUD_RATE 230400L
#endif

/* set the UART baud rate defaults */
#ifndef BAUD_RATE
 #if F_CPU >= 8000000L
  #define BAUD_RATE   115200L // Highest rate Avrdude win32 will support
 #elif F_CPU >= 1000000L
  #define BAUD_RATE   9600L   // 19200 also supported, but with significant error
 #elif F_CPU >= 128000L
  #define BAUD_RATE   4800L   // Good for 128kHz internal RC
 #else
  #define BAUD_RATE 1200L     // Good even at 32768Hz
 #endif
#endif


/*
 * We can never load flash with more than 1 page at a time, so we can save
 * some code space on parts with smaller pagesize by using a smaller int.
 */
#if SPM_PAGESIZE > 255
 typedef uint16_t pagelen_t ;
 #define GETLENGTH(len) len = getch()<<8; len |= getch()
#else
 typedef uint8_t pagelen_t;
 #define GETLENGTH(len) (void) getch() /* skip high byte */; len = getch()
#endif


/* Function Prototypes
 * The main() function is in init9, which removes the interrupt vector table
 * we don't need. It is also 'OS_main', which means the compiler does not
 * generate any entry or exit code itself (but unlike 'naked', it doesn't
 * supress some compile-time options we want.)
 */

int main(void) __attribute__ ((OS_main)) __attribute__ ((section (".init9"))) __attribute__ ((__noreturn__));
void __attribute__((noinline)) putch(uint8_t);
uint8_t __attribute__((noinline)) getch(void);
void __attribute__((noinline)) verifySpace();
void __attribute__((noinline)) watchdogConfig(uint8_t x);
static inline void getNch(uint8_t);
void __attribute__((noinline)) t1_delay(void);

#if SOFT_UART > 0
 void uartDelay() __attribute__ ((naked));
#endif
void wait_timeout(void) __attribute__ ((__noreturn__));
void appStart(uint8_t rstFlags) __attribute__ ((naked))  __attribute__ ((__noreturn__));

/*
 * NRWW memory
 * Addresses below NRWW (Non-Read-While-Write) can be programmed while
 * continuing to run code from flash, slightly speeding up programming
 * time.  Beware that Atmel data sheets specify this as a WORD address,
 * while optiboot will be comparing against a 16-bit byte address.  This
 * means that on a part with 128kB of memory, the upper part of the lower
 * 64k will get NRWW processing as well, even though it doesn't need it.
 * That's OK.  In fact, you can disable the overlapping processing for
 * a part entirely by setting NRWWSTART to zero.  This reduces code
 * space a bit, at the expense of being slightly slower, overall.
 *
 * RAMSTART should be self-explanatory.  It's bigger on parts with a
 * lot of peripheral registers.
 */
#if defined(__AVR_ATmega1280__)
 #undef RAMSTART
 #define RAMSTART (0x200)
#endif


/* C zero initialises all global variables. However, that requires */
/* These definitions are NOT zero initialised, but that doesn't matter */
/* This allows us to drop the zero init code, saving us memory */
#define buff    ((uint8_t*)(RAMSTART))


#ifndef SUPPORT_EEPROM
 #define SUPPORT_EEPROM 0
#endif
#ifdef BIGBOOT
 #undef SUPPORT_EEPROM		/* prevent compiler error, if previously set */
 #define SUPPORT_EEPROM 1	/* allways set the EEprom support */
#else
 #define BIGBOOT 0
#endif

#if LED_START_FLASHES < 0
 // negative count of LED_START_FLASHES means a RX Pin monitoring!
 #define Check_RX 1
 #warning "LED flash loop with RX Pin monitoring!"
#endif



/* main program starts here */
int main(void) {
  uint8_t ch;

  /*
   * Making these local and in registers prevents the need for initializing
   * them, and also saves space because code no longer stores to memory.
   * (initializing address to 0 keeps the compiler happy, but isn't really
   *  necessary, and uses 4 bytes of flash.)
   * A "address = address" solve the problem because no code is generated.
   */
  register uint16_t address = address;
  register pagelen_t  length;

  // After the zero init loop, this is the first code to run.
  //
  // This code makes the following assumptions:
  //  No interrupts will execute
  //  SP points to RAMEND
  //  r1 contains zero
  //
  // If not, uncomment the following instructions:
  // cli();
  asm volatile ("clr __zero_reg__");
#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega128__) || \
    defined (__AVR_ATmega16__) || defined (__AVR_ATmega16A__) || \
    defined (__AVR_ATmega32__) || defined (__AVR_ATmega32A__) || \
    defined (__AVR_ATmega64__) || defined (__AVR_ATmega64A__) || \
    defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) || \
    defined(__AVR_AT90PWM2__) || defined(__AVR_AT90PWM3__) || \
    defined(__AVR_AT90PWM2B__) || defined(__AVR_AT90PWM3B__) || \
  defined(__AVR_AT90CAN32__) || defined(__AVR_AT90CAN64__) || defined(__AVR_AT90CAN128__) || \
    defined(__AVR_ATmega162__) || defined(__AVR_ATmega163__) || \
    defined(__AVR_ATmega323__) || \
    defined(__AVR_ATmega169__) || defined(__AVR_ATmega169P__) || \
    defined(__AVR_ATmega169A__) || defined(__AVR_ATmega169PA__) || \
    defined(__AVR_ATmega329__) || defined(__AVR_ATmega329P__) || \
    defined(__AVR_ATmega329A__) || defined(__AVR_ATmega329PA__) || \
    defined(__AVR_ATmega3290__) || defined(__AVR_ATmega3290P__) || \
    defined(__AVR_ATmega3290A__) || defined(__AVR_ATmega3290PA__) || \
    defined(__AVR_ATmega649__) || defined(__AVR_ATmega649P__) || \
    defined(__AVR_ATmega649A__) || \
    defined(__AVR_ATmega6490__) || defined(__AVR_ATmega6490P__) || \
    defined(__AVR_ATmega6490A__)  || \
    defined(__AVR_ATmega165__) || defined(__AVR_ATmega165P__) || \
    defined(__AVR_ATmega165A__) || defined(__AVR_ATmega165PA__) || \
    defined(__AVR_ATmega325__) || defined(__AVR_ATmega325P__) || \
    defined(__AVR_ATmega325A__) || defined(__AVR_ATmega325PA__) || \
    defined(__AVR_ATmega3250__) || defined(__AVR_ATmega3250P__) || \
    defined(__AVR_ATmega3250A__) || defined(__AVR_ATmega3250PA__) || \
    defined(__AVR_ATmega645__) || defined(__AVR_ATmega645P__) || \
    defined(__AVR_ATmega645A__) || defined(__AVR_ATmega645PA__) || \
    defined(__AVR_ATmega6450__) || defined(__AVR_ATmega6450P__) || \
    defined(__AVR_ATmega6450A__) || defined(__AVR_ATmega6450PA__)
 #if defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__)
  SP = RAMEND -256;
 #else
  SP=RAMEND;  // This is done by hardware reset
 #endif
#endif

  /*
   * modified Adaboot no-wait mod.
   * Pass the reset reason to app.  Also, it appears that an Uno poweron
   * can leave multiple reset flags set; we only want the bootloader to
   * run on an 'external reset only' status
   */
  // Adaboot no-wait mod
  ch = MCUCSR;
  MCUCSR = 0;

#if !defined(OSCCAL)
 // OSCCAL0 can be Bit 0 of OSCCAL, if OSCCAL is defined
 #if defined(OSCCAL0)
  // OSCCAL0 is the name if the first OSCCAL register
  #define OSCCAL OSCCAL0
 #endif
#endif

#if defined(OSCCAL_CORR) && defined(OSCCAL)
 #if (OSCCAL_CORR < -10) || (OSCCAL_CORR > 10)
  #warning "OSCCAL_CORR is too big, should be greater -10 and less than 10"
 #elif (OSCCAL_CORR != 0)
  OSCCAL -= OSCCAL_CORR;
 #endif
#endif

  if (ch & (_BV(WDRF) | _BV(PORF) | _BV(BORF)))
    appStart(ch);

  /*
   * Disable pullups that may have been enabled by a user program.
   * Somehow a pullup on RXD screws up everything unless RXD is externally
   * driven high.
   */
#if ((UART_TXX & 0xff00) == (UART_RXX & 0xff00))
  UART_TX_PORT &= ~((1<<UART_TX_BIT) || (1<<UART_RX_BIT));
#else
  UART_TX_PORT &= ~(1<<UART_TX_BIT);
  UART_RX_PORT &= ~(1<<UART_RX_BIT);
#endif

#if SOFT_UART > 0
  /* Set TX pin as output */
 #define BAUD_SETTING ( (F_CPU + BAUD_RATE) / (BAUD_RATE * 2))
 #define BAUD_ACTUAL (F_CPU / (BAUD_SETTING * 2))
  UART_TX_DDR |= _BV(UART_TX_BIT);
#else	/* no SOFT_UART */
 /* Prepare the hardware UART */
 #define BAUD_DIV (((F_CPU / 4L / BAUD_RATE) - 1) / 2)
 #define BAUD_ACTUAL (F_CPU / 8L / ((BAUD_DIV)+1))
 #define UART_MODE_2X
 #if (BAUD_DIV > 255) && (BAUD_DIV < 2046)
  // try with single speed
  #undef UART_MODE_2X
  #undef BAUD_DIV
  #define BAUD_DIV ((F_CPU + BAUD_RATE * 8L) / (BAUD_RATE * 16L) - 1)
  #define BAUD_DIV (((F_CPU / 8L / BAUD_RATE) - 1) / 2)
  #define BAUD_ACTUAL (F_CPU / 16L / ((BAUD_DIV)+1))
  #if BAUD_DIV > 4095
   #error "Unachievable baud rate (too slow) BAUD_RATE"
  #endif
 #endif
 #if defined(__AVR_ATmega8__) || defined (__AVR_ATmega32__) || defined(__AVR_ATmega16__)
  #ifdef UART_MODE_2X
   UCSRA = _BV(U2X);	// Double speed mode USART
  #else
   UCSRA = 0;		// Single speed mode USART
  #endif
  UCSRB = _BV(RXEN) | _BV(TXEN);  // enable Rx & Tx
  UCSRC = _BV(URSEL) | _BV(UCSZ1) | _BV(UCSZ0);  // config USART; 8N1
  UBRRL = (uint8_t)( BAUD_DIV );
  #if (BAUD_DIV/256) != 0
   UCSRC = (uint8_t)( BAUD_DIV/256 );	// without URSEL bit this register hold the upper bits
  #endif
 #else		/* no ATmega8 ... */
  #ifdef UART_MODE_2X
   UART_SRA = _BV(U2X0);	// Double speed mode USART0
  #else
   UART_SRA = 0;		// Single speed mode USART0
  #endif
  #ifdef UART_ONE_WIRE
  UART_SRB = _BV(RXEN0);		// enable only UART input
  #else
  UART_SRB = _BV(RXEN0) | _BV(TXEN0);	// enable UART input and output
  #endif
  #if defined(UART_SRC)
  UART_SRC = _BV(UCSZ00) | _BV(UCSZ01);
  #endif
  UART_SRRL = (uint8_t)( BAUD_DIV );
  #if (BAUD_DIV/256) != 0
   UART_SRRH = (uint8_t)( BAUD_DIV/256 );
  #endif
 #endif		/* defined(ATmega8) ... */
#endif

// check the ACTUAL Baud Rate for soft and hard
#if BAUD_ACTUAL <= BAUD_RATE
  #define BAUD_ERROR (( 100*(BAUD_RATE - BAUD_ACTUAL) ) / BAUD_RATE)
  #if BAUD_ERROR >= 5
    #error "BAUD_RATE error greater than -5%"
  #elif BAUD_ERROR >= 2
    #warning "BAUD_RATE error greater than -2%"
  #endif
#else
  #define BAUD_ERROR (( 100*(BAUD_ACTUAL - BAUD_RATE) ) / BAUD_RATE)
  #if BAUD_ERROR >= 5
    #error "BAUD_RATE error greater than 5%"
  #elif BAUD_ERROR >= 2
    #warning "BAUD_RATE error greater than 2%"
  #endif
#endif

#if (BAUD_DIV < 3)
 #if BAUD_ERROR != 0 // permit high bitrates (ie 1Mbps@16MHz) if error is zero
  #error "Unachievable baud rate (too fast) BAUD_RATE"
 #endif
#endif // baud rate fastn check
#include "report_baud_div.h"

  // Set up watchdog to trigger after 500ms
#ifdef TIMEOUT_MS
 #if TIMEOUT_MS > 6000
  watchdogConfig(WATCHDOG_8S);		/* try to set watchdog timer to 8s */
 #elif TIMEOUT_MS > 3000
  watchdogConfig(WATCHDOG_4S);		/* try to set watchdog timer to 4s */
 #elif TIMEOUT_MS > 1500
  watchdogConfig(WATCHDOG_2S);		/* set the watchdog timer to 2s */
 #elif TIMEOUT_MS > 750
  watchdogConfig(WATCHDOG_1S);		/* set the watchdog timer to 1s */
 #else
  watchdogConfig(WATCHDOG_500MS);	/* set the watchdog timer to 500ms */
 #endif
#else
  watchdogConfig(WATCHDOG_1S);		/* set the watchdog timer to 1s (default) */
#endif

#if (LED_START_FLASHES != 0) || (LED_DATA_FLASH > 0)
  /* Set LED pin as output */
  LED_DDR |= _BV(LEDbit);
#endif

#if LED_START_FLASHES != 0
  /* Flash onboard LED to signal entering of bootloader */
 #if (LED_START_FLASHES > 1) || (LED_START_FLASHES < -1)
  uint8_t count = LED_START_FLASHES;
  do {
 #endif
    LED_PORT |= _BV(LEDbit);
    t1_delay();
    LED_PORT &= ~(_BV(LEDbit));
    t1_delay();

 #if LED_START_FLASHES > 1
  } while (--count);
 #endif
 #if LED_START_FLASHES < -1
  } while (++count);	/* { */
 #endif
#endif	/* LED_START_FLASHES != 0 */

#if TEST_OUTPUT == 1
 #warning "optiboot with test output only!"
    /* only a test output for baud rate check, the bootloader will not work with this */
   do {
    putch('U');         // produce a 01010101 pattern for test
   } ;
#endif

  /* Forever loop */
  for (;;) {
    /* get character from UART */
    ch = getch();

    if(ch == STK_GET_PARAMETER) {
      unsigned char which = getch();
      verifySpace();
      if (which == 0x82) {
	/*
	 * Send optiboot version as "SW version"
         * Note that the references to memory are optimized away.
	 */
	putch(OPTIBOOT_MINVER);
      } else if (which == 0x81) {
	  putch(OPTIBOOT_MAJVER+OPTIBOOT_CUSTOMVER);
      } else {
	/*
	 * GET PARAMETER returns a generic 0x03 reply for
         * other parameters - enough to keep Avrdude happy
	 */
	putch(0x03);
      }
    }
    else if(ch == STK_SET_DEVICE) {
      // SET DEVICE is ignored
      getNch(20);
    }
    else if(ch == STK_SET_DEVICE_EXT) {
      // SET DEVICE EXT is ignored
      getNch(5);
    }
    else if(ch == STK_LOAD_ADDRESS) {
      // LOAD ADDRESS
      union {
        // this contruct will help the compiler to generate effective code
        uint16_t w;		// word access, 16 bits
        uint8_t b[2];		// char access to the same item, 2x8 bits
      } newAddress;
      newAddress.b[0] = getch();	// first byte to lower bits
      newAddress.b[1] = getch();	// next byte to upper bits
#ifdef RAMPZ
      // Transfer top bit to RAMPZ
      RAMPZ = (newAddress.b[1] & 0x80) ? 1 : 0;
#endif
      newAddress.w += newAddress.w; // Convert from word address to byte address
      address = newAddress.w;
      verifySpace();
    }
    else if(ch == STK_UNIVERSAL) {
      // UNIVERSAL command is ignored
      getNch(4);
      putch(0x00);
    }
    /* Write memory, length is big endian and is in bytes */
    else if(ch == STK_PROG_PAGE) {
      // PROGRAM PAGE - we support flash and optional EEPROM programming
      uint8_t *bufPtr;
      uint16_t addrPtr;

      GETLENGTH(length);

#if SUPPORT_EEPROM > 0
      pagelen_t savelength;
      savelength = length;
      uint8_t desttype = getch() - 'E';	/* desttype = 0, if EEprom */
      if (desttype)
#else
      getch();			/* dummy type */
#endif 
        // If we are in RWW section, immediately start page erase
      if (address < NRWWSTART) {
//#if defined(__AVR_ATmega64__)
//         __boot_page_erase_normal((uint16_t)(void*)address);
//#else
//         __boot_page_erase_short((uint16_t)(void*)address);
//#endif
         boot_page_erase((uint16_t)(void*)address);
      }

      // While that is going on, read in page contents
      bufPtr = buff;
      do *bufPtr++ = getch();
      while (--length);

#if SUPPORT_EEPROM > 0
      if (!desttype) {	/* EEPROM */
        // Read command terminator, start reply
        verifySpace();

        length = savelength;
        addrPtr = address;
        bufPtr = buff;
        while (length--) {
          wdt_reset();
          while (!eeprom_is_ready());

          EEAR = addrPtr++;
          EEDR = *bufPtr++;
          EECR |= 1 << EEMPE;	/* Write logical one to EEMPE */
          EECR |= 1 << EEPE;	/* Start eeprom write by setting EEPE */
        }
      } else {
#endif
        // If we are in NRWW section, page erase has to be delayed until now.
        // Todo: Take RAMPZ into account (not doing so just means that we will
        //  treat the top of both "pages" of flash as NRWW, for a slight speed
        //  decrease, so fixing this is not urgent.)
        if (address >= NRWWSTART) {
//#if defined(__AVR_ATmega64__)
//           __boot_page_erase_normal((uint16_t)(void*)address);
//#else
//           __boot_page_erase_short((uint16_t)(void*)address);
//#endif
           boot_page_erase((uint16_t)(void*)address);
        }

        // Read command terminator, start reply
        verifySpace();

        // If only a partial page is to be programmed, the erase might not be complete.
        // So check that here
        boot_spm_busy_wait();

#ifdef VIRTUAL_BOOT_PARTITION
 #if FLASHEND > 8192
/*
 * AVR with 4-byte ISR Vectors and "jmp"
 * WARNING: this works only up to 128KB flash!
 */
      if (address == 0) {
        // This is the reset vector page. We need to live-patch the
        // code so the bootloader runs first.
        //
        // Save jmp targets (for "Verify")
	// Both interrupt vectors (rstVect and saveVect) must hold a JMP instruction!!
        rstVect0_sav = buff[rstVect0];
        rstVect1_sav = buff[rstVect1];
        saveVect0_sav = buff[saveVect0];
        saveVect1_sav = buff[saveVect1];

        // Move RESET jmp target to 'save' vector
        buff[saveVect0] = rstVect0_sav;
        buff[saveVect1] = rstVect1_sav;

        // Add jump to bootloader at RESET vector
        // WARNING: this works as long as 'main' is in first section
	// we should check, that the reset vector holds a JMP, not a RJMP!!!
        buff[rstVect0] = ((uint16_t)main) & 0xFF;
        buff[rstVect1] = ((uint16_t)main) >> 8;
      }

 #else
/*
 * AVR with 2-byte ISR Vectors and rjmp
 */
      if ((uint16_t)(void*)address == rstVect0) {
        // This is the reset vector page. We need to live-patch
        // the code so the bootloader runs first.
        //
        // Move RESET vector to 'save' vector
        // Save jmp targets (for "Verify")
        rstVect0_sav = buff[rstVect0];
        rstVect1_sav = buff[rstVect1];
        saveVect0_sav = buff[saveVect0];
        saveVect1_sav = buff[saveVect1];

        // Instruction is a relative jump (rjmp), so recalculate.
        uint16_t vect=(rstVect0_sav & 0xff) | ((rstVect1_sav & 0x0f)<<8); //calculate 12b displacement
        vect = (vect-save_vect_num) & 0x0fff; //substract 'save' interrupt position and wrap around 4096
        // Move RESET jmp target to 'save' vector
        buff[saveVect0] = vect & 0xff;
        buff[saveVect1] = (vect >> 8) | 0xc0; //

        // Add rjump to bootloader at RESET vector
        vect = ((uint16_t)main) &0x0fff; //WARNIG: this works as long as 'main' is in first section
	// where is the offset for relative jmp !!!!!!
        buff[rstVect0] = vect & 0xFF; // rjmp 0x1c00 instruction
        buff[rstVect1] = (vect >> 8) | 0xC0;
      }
 #endif // FLASHEND
#endif // VBP


        // Copy buffer into programming buffer
        uint16_t *buf16Ptr;
        buf16Ptr = (uint16_t *)buff;
        addrPtr = (uint16_t)(void*)address;
        ch = SPM_PAGESIZE / 2;
        do {
//#if defined(__AVR_ATmega64__)
//          __boot_page_fill_normal((uint16_t)(void*)addrPtr,*buf16Ptr++);
//#else
//          __boot_page_fill_short((uint16_t)(void*)addrPtr,*buf16Ptr++);
//#endif
	  boot_page_fill((uint16_t)(void *)addrPtr,*buf16Ptr++);
          addrPtr += 2;
        } while (--ch);

        // Write from programming buffer
//#if defined(__AVR_ATmega64__)
//        __boot_page_write_normal((uint16_t)(void*)address);
//#else
//        __boot_page_write_short((uint16_t)(void*)address);
//#endif
        boot_page_write((uint16_t)(void*)address);
        boot_spm_busy_wait();

#if defined(RWWSRE)
        // Reenable read access to flash
        boot_rww_enable();
#endif
#if SUPPORT_EEPROM > 0
      }
#endif
    }
    /* Read memory block mode, length is big endian.  */
    else if(ch == STK_READ_PAGE) {
      // READ PAGE - we only read flash and EEPROM

      GETLENGTH(length);
#if SUPPORT_EEPROM > 0
      uint8_t desttype = getch() - 'E';     /* 0 if EEprom */

      verifySpace();
      /* TODO: putNch */
      if (desttype)
#else
      getch(); 		/* dummy desttype */

      verifySpace();
      /* TODO: putNch */
#endif
        do {
#ifdef VIRTUAL_BOOT_PARTITION
        // Undo vector patch in bottom page so verify passes
            if (address == rstVect0) ch = rstVect0_sav;
            else if (address == rstVect1) ch = rstVect1_sav;
            else if (address == saveVect0) ch = saveVect0_sav;
            else if (address == saveVect1) ch = saveVect1_sav;
            else ch = pgm_read_byte_near(address);
            address++;
#elif defined(RAMPZ)
          // Since RAMPZ should already be set, we need to use EPLM directly.
          // Also, we can use the autoincrement version of lpm to update "address"
          //      do putch(pgm_read_byte_near(address++));
          //      while (--length);
          // read a Flash and increment the address (may increment RAMPZ)
          __asm__ ("elpm %0,Z+\n" : "=r" (ch), "=z" (address): "1" (address));
#else
          // read a Flash byte and increment the address
          __asm__ ("lpm %0,Z+\n" : "=r" (ch), "=z" (address): "1" (address));
#endif
          putch(ch);
        } while (--length);
#if SUPPORT_EEPROM > 0
      else 
        while (length--) {
          while (!eeprom_is_ready());

          EEAR = address++;
          EECR |= 1 << EERE;	/* Start eeprom read by writing EERE */

          putch( EEDR );
        }
#endif
    }

    /* Get device signature bytes  */
    else if(ch == STK_READ_SIGN) {
      // READ SIGN - return what Avrdude wants to hear
      verifySpace();
      putch(SIGNATURE_0);
      putch(SIGNATURE_1);
      putch(SIGNATURE_2);
    }
    else if (ch == STK_LEAVE_PROGMODE) { /* 'Q' */
      // Adaboot no-wait mod
      watchdogConfig(WATCHDOG_16MS);
      verifySpace();
    }
    else {
      // This covers the response to commands like STK_ENTER_PROGMODE
      verifySpace();
    }
    putch(STK_OK);
  }
}


void putch(uint8_t ch) {
#if SOFT_UART == 0
 // use the specified hardware UART
 #ifdef UART_ONE_WIRE
  // The main advantage of Hardware UART can not be used with ONE_WIRE mode.
  // We enable the TX transfer only for transmission time, therefore we must
  // wait until the transfer is done
  UART_SRB = (1<<TXEN0);	// enable UART output, disable input
  UART_UDR = ch;		// load data to transfer
  while (!(UART_SRA & _BV(TXC0)));	// wait for TX transfer complete
  UART_SRB = (1<<RXEN0);	// enable UART input, disable output
 #else
  // For normal Serial communication we wait until the buffer can be loaded again
  // and return to caller after loading the new data.
  while (!(UART_SRA & _BV(UDRE0)));	// wait for buffer empty
  UART_UDR = ch;
 #endif
#else
  // Transfer serial data with software loop
  __asm__ __volatile__ (
    "   com %[ch]\n" // ones complement, carry set
    "   sec\n"
    "1: brcc 2f\n"
    "   cbi %[uartPort],%[uartBit]\n"
    "   rjmp 3f\n"
    "2: sbi %[uartPort],%[uartBit]\n"
    "   nop\n"
    "3: rcall uartDelay\n"
    "   rcall uartDelay\n"
    "   lsr %[ch]\n"
    "   dec %[bitcnt]\n"
    "   brne 1b\n"
    :
    :
      [bitcnt] "d" (10),
      [ch] "r" (ch),
 #ifdef UART_ONE_WIRE
      [uartPort] "I" (_SFR_IO_ADDR(UART_TX_DDR)),
 #else
      [uartPort] "I" (_SFR_IO_ADDR(UART_TX_PORT)),
 #endif
      [uartBit] "I" (UART_TX_BIT)
    :
      "r25"
  );
#endif
 wdt_reset();		/* prevent wdt time-out during slow TX transmission */
}

uint8_t getch(void) {
  uint8_t ch;

#if LED_DATA_FLASH > 0
  LED_PORT |= _BV(LEDbit);			// switch on LED
#endif

#if SOFT_UART > 0
  __asm__ __volatile__ (
    "1: sbic  %[uartPin],%[uartBit]\n"  // Wait for start edge
    "   rjmp  1b\n"
    "   rcall uartDelay\n"          // Get to middle of start bit
    "2: rcall uartDelay\n"              // Wait 1 bit period
    "   rcall uartDelay\n"              // Wait 1 bit period
    "   clc\n"
    "   sbic  %[uartPin],%[uartBit]\n"
    "   sec\n"
    "   dec   %[bitCnt]\n"
    "   breq  3f\n"
    "   ror   %[ch]\n"
    "   rjmp  2b\n"
    "3:\n"
    :
      [ch] "=r" (ch)
    :
      [bitCnt] "d" (9),
      [uartPin] "I" (_SFR_IO_ADDR(UART_RX_PIN)),
      [uartBit] "I" (UART_RX_BIT)
    :
      "r25"
);
#else
  while(!(UART_SRA & _BV(RXC0)))
    ;
  if (!(UART_SRA & _BV(FE0))) {
      /*
       * A Framing Error indicates (probably) that something is talking
       * to us at the wrong bit rate.  Assume that this is because it
       * expects to be talking to the application, and DON'T reset the
       * watchdog.  This should cause the bootloader to abort and run
       * the application "soon", if it keeps happening.  (Note that we
       * don't care that an invalid char is returned...)
       */
    wdt_reset();
  }

  ch = UART_UDR;
#endif

#if LED_DATA_FLASH > 0
  LED_PORT &= ~(_BV(LEDbit));		// switch off LED
#endif

  return ch;
}  /* end getch() */

#if LED_START_FLASHES != 0
void t1_delay(void) {
 #ifdef TCNT1H
  // Set up Timer 1 for timeout counter
  TCCR1B = _BV(CS12) | _BV(CS10); // div 1024
  TCNT1 = -(F_CPU/(1024*16));
  TIFR1 = _BV(TOV1);
  #ifdef Check_RX
  while( !(TIFR1 & _BV(TOV1)) && (UART_RX_PIN & _BV(UART_RX_BIT)) );
  #else
  while(!(TIFR1 & _BV(TOV1)));
  #endif
 #elif defined(TCNT0H)
  TCCR0B = _BV(CS02) | _BV(CS00); // div 1024
  TCNT0 = -(F_CPU/(1024*16));
  TIFR0 = _BV(TOV0);
  #ifdef Check_RX
  while( !(TIFR0 & _BV(TOV0)) && (UART_RX_PIN & _BV(UART_RX_BIT)) );
  #else
  while(!(TIFR0 & _BV(TOV0)));
  #endif
 #endif
  wdt_reset();		/* prevent wdt time-out during LED flashing */
}
#endif

#if SOFT_UART > 0
// AVR305 equation: #define UART_B_VALUE (((F_CPU/BAUD_RATE)-23)/6)
// Adding 3 to numerator simulates nearest rounding for more accurate baud rates
#define RCALL_TICS 7
#define LOOP_TICS 9
#define WAST_TICS (((F_CPU/BAUD_RATE)- ((2*RCALL_TICS)+LOOP_TICS))+1)
#define UART_B_VALUE (WAST_TICS / 6)
 #if UART_B_VALUE > 255
  #error "Baud rate too slow for soft UART"
 #endif
#define UART_R_VALUE (WAST_TICS - (UART_B_VALUE * 6))/2
// with UART_R_VALUE the remainder of the uartDelay loop
// is added as dummy instruction at the end of the counter loop.

void uartDelay() {
  __asm__ __volatile__ (
#if UART_B_VALUE > 0
    "ldi r25,%[count]\n"
    "1:dec r25\n"
    "brne 1b\n"
#endif
#if UART_R_VALUE == 2
    "rjmp  .\n"
#endif
#if UART_R_VALUE == 1
    "nop   \n"
#endif
    "ret\n"
    ::[count] "M" (UART_B_VALUE)
  );
}
#endif

void getNch(uint8_t count) {
  do getch(); while (--count);
  verifySpace();
}

void verifySpace(void) {
  if (getch() != CRC_EOP)
    wait_timeout();
  putch(STK_INSYNC);
}

void wait_timeout(void) {
  watchdogConfig(WATCHDOG_16MS);      // shorten WD timeout
  while (1)			      // and busy-loop so that WD causes
    ;				      //  a reset and app start.
}

void watchdogConfig(uint8_t x) {
  WDTCSR = _BV(WDCE) | _BV(WDE);
  WDTCSR = x;
}

void appStart(uint8_t rstFlags) {
#ifdef FORCE_WATCHDOG
  watchdogConfig(WATCHDOG_4S);
#else
  watchdogConfig(WATCHDOG_OFF);
#endif

  // save the reset flags in the designated register
  //  This can be saved in a main program by putting code in .init0 (which
  //  executes before normal c init code) to save R2 to a global variable.
  __asm__ __volatile__ ("mov r2, %0\n" :: "r" (rstFlags));

  __asm__ __volatile__ (
    // Jump to WDT or RST vector
    "ldi r30,%[rstvec]\n"
    "clr r31\n"
    "ijmp\n"::[rstvec] "M"(appstart_vec)
  );
#if BIGBOOT >= 128
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*2)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*3)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*4)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*5)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*6)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*7)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*8)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*9)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*10)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*11)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*12)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*13)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*14)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*15)
 #include "wast_128bytes.h"
#endif
#if BIGBOOT >= (128*16)
 #include "wast_128bytes.h"
#endif
}
