/*
 * pin_defs.h
 * optiboot helper defining the default pin assignments (LED, SOFT_UART)
 * for the various chips that are supported.  This also has some ugly macros
 * for selecting among various UARTs and LED possibilities using command-line
 * defines like "UART=2 LED=B5"
 *
 * reorganized 2016 by K.-H. Kuebbeler
 * UART_TX and UART_RX can be selected with the LED style  (D0 or B5)
 * Copyright 2013-2015 by Bill Westfield.
 * Copyright 2010 by Peter Knight.
 * This software is licensed under version 2 of the Gnu Public Licence.
 * See optiboot.c for details.
 */

#ifndef UART
 #define UART_NR 0		/* predefine 0 as default UART number */
#else
 #define UART_NR UART
#endif

#ifndef SOFT_UART
 #define SOFT_UART 0
#endif

#ifndef LED_START_FLASHES
 #define LED_START_FLASHES 0
#endif

#ifndef LED_DATA_FLASH
 #define LED_DATA_FLASH 0
#endif

#include <avr/io.h>
#include "short_port_codes.h"

#ifndef EEARL
 /* sometimes, if EEARH is missing because of limited EEprom space,
    the EEARL is named EEAR
  */
 #define EEARL EEAR	
#else
 #ifndef EEAR
  #define EEAR EEARL
 #endif
#endif

#if !defined(SELFPRGEN) && defined(SPMEN)
 #define SELFPRGEN SPMEN                /* use different name of SELFPRGEN bit */
#endif

#ifndef SPMCSR
 #if defined(SPMCR)
  #define SPMCSR SPMCR                   /* use different name of SPM register */
 #endif
#endif

#if !defined(WDCE) 
 #if defined(WDTOE)
  #define WDCE		WDTOE
 #elif defined WDE
  #define WDCE		WDE
 #endif
#endif

#ifndef MCUCSR
 #if defined(MCUSR)
  #define MCUCSR MCUSR
 #endif
#endif

#ifndef RAMSTART
 #define RAMSTART (0x100)
#endif

/* We now compute the NRWWSTART address from FLASHEND and BOOT_PAGE_LEN */
#ifndef BOOT_PAGE_LEN
 #warning "BOOT_PAGE_LEN is not set"
 #if FLASHEND >= 0xffff
  #define BOOT_PAGE_LEN 1024
 #elif FLASHEND >= 0x7fff
  #define BOOT_PAGE_LEN 512
 #elif FLASHEND >= 0x1fff
  #define BOOT_PAGE_LEN 256
 #else
  #define BOOT_PAGE_LEN 32
 #endif
#endif

#if BOOT_PAGE_LEN <= SPM_PAGESIZE
 /* I know no device, where the BOOT_PAGE_LEN is less or equal to SPM_PAGESIZE */
 #define NRWWSTART 0		/* device has no Boot Partition */
#else
 /* the total Bootloader area (8 Boot pages) is NRWW */
 #ifdef __ASSEMBLER__
  #define NRWWSTART  (((FLASHEND+1)  - (BOOT_PAGE_LEN * 8)) & 0xffff)
 #else
  #define NRWWSTART  ((((long)FLASHEND+1)  - ((long)BOOT_PAGE_LEN * 8)) & 0xffff)
 #endif
#endif

/* First make undefined ports equal to n */
#if !defined(LED)
 #define LED n
#endif
#if !defined(UART_RX)
 #warning undefined UART_RX
 #define UART_RX n
#endif
#if !defined(UART_TX)
 #warning undefined UART_TX
 #define UART_TX n
#endif

#if defined(UDR)
  //Name conversion R.Wiersma
  #undef UDR0		/* probably was Bit 0 of UDR before */
  #define UDR0 		UDR
  /* and rename some Bits */
  #define UDRE0 	UDRE
  #define RXC0		RXC
  #define FE0           FE
  #define U2X0		U2X
  #define RXEN0		RXEN
  #define TXEN0		TXEN
#endif		/* !defined(UDR0)  ... */

#ifndef UBRR0L
 #if defined(UBRR)
  #define UBRR0L	UBRR
 #elif defined(UBRRL)
  #define UBRR0L	UBRRL
 #endif
#endif

#ifndef UBRR0H
 #ifdef UBRRHI
  #define UBRR0H	UBRRHI
 #elif defined(UBRRH)
  #define UBRR0H	UBRRH
 #endif
#endif

#ifndef WDTCSR
  #define WDTCSR	WDTCR
#endif

#if !defined(UCSR0A) && defined(UCSRA)
  // Make the only UART to the UART0
  #define UCSR0A	UCSRA
  #define UCSR0B	UCSRB
#endif
#if !defined(UCSR0C) && defined(UCSRC)
  #define UCSR0C	UCSRC
  #define UCSZ01	UCSZ1
  #define UCSZ00	UCSZ0
#endif

#if !defined(EEPE) && defined(EEWE) 
  // bits in EECR has other names
 #define EEPE		EEWE
 #define EEMPE		EEMWE
#endif

#if !defined(TIFR1) && defined(TIFR)
 #define TIFR1 		TIFR
#endif


/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || \
    defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || \
    defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || \
    defined(__AVR_ATmega8__) || defined(__AVR_ATmega8A__) || \
    defined(__AVR_ATmega48__) || defined(__AVR_ATmega48P__) || \
    defined(__AVR_ATmega88__) || defined(__AVR_ATmega88P__) 
/*------------------------------------------------------------------------ */

 /* Onboard LED is connected to pin PB5 in Arduino NG, Diecimila, and Duemilanove */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B5"
  #define LEDX           nB5	/* coded Port B Bit 5 */
 #else
  #define LEDX           LED
 #endif

 /* Default "SOFT" UART Ports for ATmega8/48/88/168/328 */
 #if UART_RX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin D0 as RX"
  #endif
  #define UART_RXX      nD0
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin D1 as TX"
  #endif
  #define UART_TXX      nD1
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_ATmega168__  ... */

/* Luminet support */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny24__) || \
    defined(__AVR_ATtiny84A__) || defined(__AVR_ATtiny44A__) || defined(__AVR_ATtiny24A__)
/*------------------------------------------------------------------------ */
 /* Red LED is connected to pin PA4 */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default A4"
   #define LEDX        nA4
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATtiny84 */
 /* Ports for soft UART - left port only for now. TX/RX on PA2/PA3 */
 #if UART_RX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin A3 as RX"
  #endif		/* SOFT_UART > 0 */
  #define UART_RXX	nA3
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin A2 as TX"
  #endif
  #define UART_TXX	nA2
 #else
  #define UART_TXX      UART_TX
 #endif
#endif	/* __AVR_ATtiny44__ || __AVR_ATtiny84__ */

/*------------------------------------------------------------------------ */
/* support for attiny841 and attiny441 */
#if defined(__AVR_ATtiny841__) || defined(__AVR_ATtiny441__) 
/*------------------------------------------------------------------------ */
 /* Onboard LED can be connected to pin PB0 on Sanguino */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B0"
  #define LEDX         nB0
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATtiny441/841 */
 #if UART_RX == n
  #if UART_NR == 0
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin B2 as RX for UART 0"
   #endif		/* SOFT_UART > 0 */
   #define UART_RXX	nB2
  #else
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin A4 as RX for UART 1"
   #endif		/* SOFT_UART > 0 */
   #define UART_RXX	nA4
  #endif
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if UART_NR == 0
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin A7 as TX for UART 0"
   #endif
   #define UART_TXX	nA7
  #else
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin A5 as TX for UART 1"
   #endif
   #define UART_TXX	nA5
  #endif
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_ATiny841__  .. */

/*------------------------------------------------------------------------ */

/* Support for ATtiny48 and ATtiny88 */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny88__) || defined(__AVR_ATtiny48__)
/*------------------------------------------------------------------------ */
 /* Red LED is connected to pin PA4 */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B5"
   #define LEDX        nB5
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATtiny84 */
 /* Ports for soft UART - left port only for now. TX/RX on PA2/PA3 */
 #if SOFT_UART > 0
  #if UART_RX == n
   #warning "SOFT_UART use Pin D0 as RX"
   #define UART_RXX	nD0
  #else
   #define UART_RXX      UART_RX
  #endif
  #if UART_TX == n
   #warning "SOFT_UART use Pin D1 as TX"
   #define UART_TXX	nD1
  #else
   #define UART_TXX      UART_TX
  #endif
 #else
  #error "Attiny48 and ATtiny88 has no Hardware UART"
 #endif		/* SOFT_UART > 0 */
#endif	/* __AVR_ATtiny88__ || __AVR_ATtiny48__ */

/* Support for ATtiny85 family*/
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) 
/*------------------------------------------------------------------------ */
 /* Red LED is connected to pin PA4 */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B2"
   #define LEDX        nB2
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATtiny85 */
 /* Ports for soft UART - left port only for now. TX/RX on PA2/PA3 */
 #if SOFT_UART > 0
  #if UART_RX == n
   #warning "SOFT_UART use Pin B0 as RX"
   #define UART_RXX	nB0
  #else
   #define UART_RXX      UART_RX
  #endif
  #if UART_TX == n
   #warning "SOFT_UART use Pin B1 as TX"
   #define UART_TXX	nB1
  #else
   #define UART_TXX      UART_TX
  #endif
 #else
  #error "ATtiny85 family has no hardware UART"
 #endif		/* SOFT_UART > 0 */
#endif	/* __AVR_ATtiny85__  */

/* Support for ATtiny 26x family*/
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny861__) || defined(__AVR_ATtiny461__) || defined(__AVR_ATtiny261__) || \
    defined(__AVR_ATtiny861A__) || defined(__AVR_ATtiny461A__) || defined(__AVR_ATtiny261A__) 
/*------------------------------------------------------------------------ */
 /* Red LED is connected to pin PA4 */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default A4"
   #define LEDX        nA0
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATtiny26x */
 /* Ports for soft UART - left port only for now. TX/RX on PA2/PA3 */
 #if SOFT_UART > 0
  #if UART_RX == n
   #warning "SOFT_UART use Pin B0 as RX"
   #define UART_RXX	nB0
  #else
   #define UART_RXX      UART_RX
  #endif
  #if UART_TX == n
   #warning "SOFT_UART use Pin B1 as TX"
   #define UART_TXX	nB1
  #else
   #define UART_TXX      UART_TX
  #endif
 #endif		/* SOFT_UART > 0 */
#endif	/* __AVR_ATtiny86x__  */

/* Support for ATtiny4313 */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny4313__) || defined(__AVR_ATtiny2313__) || \
    defined(__AVR_ATtiny4313A__) || defined(__AVR_ATtiny2313A__)
/*------------------------------------------------------------------------ */
 /* Red LED is connected to pin PA4 */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B5"
   #define LEDX        nB5
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATtiny4313 */
 #if UART_RX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin D0 as RX"
  #endif		/* SOFT_UART > 0 */
  #define UART_RXX	nD0
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin D1 as TX"
  #endif
  #define UART_TXX	nD1
 #else
  #define UART_TXX      UART_TX
 #endif
#endif	/* __AVR_ATtiny4313__ */

/* Support for ATtiny1634 */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny1634__)
/*------------------------------------------------------------------------ */
 /* Red LED is connected to pin PA4 */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B1"
   #define LEDX        nB1
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATtiny1634 */
 /* Ports for soft UART - left port only for now. TX/RX on PA2/PA3 */
 #if UART_RX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin A7 as RX"
  #endif		/* SOFT_UART > 0 */
  #define UART_RXX	nA7
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin B0 as TX"
  #endif
  #define UART_TXX	nB0
 #else
  #define UART_TXX      UART_TX
 #endif
#endif	/* __AVR_ATtiny1634__ */

/*------------------------------------------------------------------------ */
/* Sanguino support (and other 40pin DIP cpus) */
#if defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || \
    defined(__AVR_ATmega164PA__) || \
    defined(__AVR_ATmega324__) || defined(__AVR_ATmega324P__) || \
    defined(__AVR_ATmega324PA__) || \
    defined(__AVR_ATmega644__) || defined(__AVR_ATmega644P__) || \
    defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644PA__) || \
    defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || \
    defined(__AVR_ATmega1284A__) || \
    defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || \
    defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__) || \
    defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__)
/*------------------------------------------------------------------------ */
 #if defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) || \
     defined(__AVR_ATmega16A__) || defined(__AVR_ATmega32A__) || \
    defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__)
  /* ATmega16/32 support only one UART */
  #undef UART_NR
  #define UART_NR 0
 #endif
 /* Onboard LED is connected to pin PB0 on Sanguino */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B0"
  #define LEDX         nB0
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATmega644/1284/32 */
 #if UART_RX == n
  #if UART_NR == 0
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin D0 as RX for UART 0"
   #endif		/* SOFT_UART > 0 */
   #define UART_RXX	nD0
  #else
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin D2 as RX for UART 1"
   #endif		/* SOFT_UART > 0 */
   #define UART_RXX	nD2
  #endif
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if UART_NR == 0
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin D1 as TX for UART 0"
   #endif		/* SOFT_UART > 0 */
   #define UART_TXX	nD1
  #else
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin D3 as TX for UART 1"
   #endif		/* SOFT_UART > 0 */
   #define UART_TXX	nD3
  #endif
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_ATmega644P__  .. */

/*------------------------------------------------------------------------ */
/* Support for AT90CAN32_64_128 */
#if defined(__AVR_AT90CAN32__) || defined(__AVR_AT90CAN64__) || defined(__AVR_AT90CAN128__) 
/*------------------------------------------------------------------------ */
 /* Onboard LED is connected to pin PB0  */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B5"
  #define LEDX         nB5
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for AT90CAN... */
 #if UART_RX == n
  #if UART_NR == 0
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin E0 as RX for UART 0"
   #endif		/* SOFT_UART > 0 */
   #define UART_RXX	nE0
  #else
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin D2 as RX for UART 1"
   #endif		/* SOFT_UART > 0 */
   #define UART_RXX	nD2
  #endif
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if UART_NR == 0
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin E1 as TX for UART 0"
   #endif		/* SOFT_UART > 0 */
   #define UART_TXX	nE1
  #else
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin D3 as TX for UART 1"
   #endif		/* SOFT_UART > 0 */
   #define UART_TXX	nD3
  #endif
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_AT90CAN... */

/*------------------------------------------------------------------------ */
#if defined(__AVR_AT90PWM2__) || defined(__AVR_AT90PWM3__) || \
    defined(__AVR_AT90PWM2B__) || defined(__AVR_AT90PWM3B__)
/*------------------------------------------------------------------------ */

 /* Onboard LED is connected to pin PB5 in Arduino NG, Diecimila, and Duemilanove */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B5"
  #define LEDX           nB5	/* coded Port B Bit 5 */
 #else
  #define LEDX           LED
 #endif

 /* Default "SOFT" UART Ports for AT90PWM */
 #if UART_RX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin D4 as RX"
  #endif		/* SOFT_UART > 0 */
  #define UART_RXX      nD4
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin D3 as TX"
  #endif		/* SOFT_UART > 0 */
  #define UART_TXX      nD3
 #else
  #define UART_TXX      UART_TX
 #endif
 #if defined(__AVR_AT90PWM2__) || defined(__AVR_AT90PWM3__) 
   /* add missing Signature bytes */
   #define SIGNATURE_0	0x1e
   #define SIGNATURE_1	0x93
   #define SIGNATURE_2	0x81
 #endif
#endif		/* __AVR_AT90PWM... */

/*------------------------------------------------------------------------ */
/* Support for ATmega64 */
#if defined(__AVR_ATmega64__) || defined(__AVR_ATmega64A__) || \
    defined(__AVR_ATmega128__)
/*------------------------------------------------------------------------ */
 #undef UART_NR
 #define UART_NR 0
 /* Onboard LED is connected to pin PB0  */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B7"
  #define LEDX         nB7
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATmega644/1284/32 */
 #if UART_RX == n
  #if SOFT_UART > 0
    #warning "SOFT_UART use Pin E0 as RX for UART 0"
  #endif		/* SOFT_UART > 0 */
  #define UART_RXX	nE0
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
    #warning "SOFT_UART use Pin E1 as TX for UART 0"
  #endif		/* SOFT_UART > 0 */
  #define UART_TXX	nE1
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_ATmega64__  .. */

#if defined(__AVR_ATmega162__) || defined(__AVR_ATmega163__) || defined(__AVR_ATmega323__)
 /* Onboard LED is connected to pin PB5 */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B0"
  #define LEDX         nB0
 #else
  #define LEDX         LED
 #endif
 #if UART_RX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin D0 as RX"
  #endif		/* SOFT_UART > 0 */
  #define UART_RXX	nD0
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin D1 as TX"
  #endif		/* SOFT_UART > 0 */
  #define UART_TXX	nD1
 #else
  #define UART_TXX      UART_TX
 #endif
#endif

#if defined(__AVR_ATmega169__) || defined(__AVR_ATmega169P__) || \
    defined(__AVR_ATmega169A__) || defined(__AVR_ATmega169PA__)
 /* Onboard LED is connected to pin PB5 */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B5"
  #define LEDX         nB5
 #else
  #define LEDX         LED
 #endif
 #if UART_RX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin E0 as RX"
  #endif		/* SOFT_UART > 0 */
  #define UART_RXX	nE0
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin E1 as TX"
  #endif		/* SOFT_UART > 0 */
  #define UART_TXX	nE1
 #else
  #define UART_TXX      UART_TX
 #endif
#endif


#if defined(__AVR_ATmega165__) || defined(__AVR_ATmega165P__) || \
    defined(__AVR_ATmega165A__) || defined(__AVR_ATmega165PA__) || \
    defined(__AVR_ATmega325__) || defined(__AVR_ATmega325P__) || \
    defined(__AVR_ATmega325A__) || defined(__AVR_ATmega325PA__) || \
    defined(__AVR_ATmega3250__) || defined(__AVR_ATmega3250P__) || \
    defined(__AVR_ATmega3250A__) || defined(__AVR_ATmega3250PA__) || \
    defined(__AVR_ATmega645__) || defined(__AVR_ATmega645P__) || \
    defined(__AVR_ATmega645A__) || defined(__AVR_ATmega645PA__) || \
    defined(__AVR_ATmega6450__) || defined(__AVR_ATmega6450P__) || \
    defined(__AVR_ATmega6450A__) || defined(__AVR_ATmega6450PA__) || \
    defined(__AVR_ATmega329__) || defined(__AVR_ATmega329P__) || \
    defined(__AVR_ATmega329A__) || defined(__AVR_ATmega329PA__) || \
    defined(__AVR_ATmega3290__) || defined(__AVR_ATmega3290P__) || \
    defined(__AVR_ATmega3290A__) || defined(__AVR_ATmega3290PA__) || \
    defined(__AVR_ATmega649__) || defined(__AVR_ATmega649P__) || \
    defined(__AVR_ATmega649A__) || \
    defined(__AVR_ATmega6490__) || defined(__AVR_ATmega6490P__) || \
    defined(__AVR_ATmega6490A__) 
 
 /* Onboard LED can be connected to pin PG0 */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B7"
  #define LEDX         nB7
 #else
  #define LEDX         LED
 #endif
 #if UART_RX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin E0 as RX"
  #endif		/* SOFT_UART > 0 */
  #define UART_RXX	nE0
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin E1 as TX"
  #endif		/* SOFT_UART > 0 */
  #define UART_TXX	nE1
 #else
  #define UART_TXX      UART_TX
 #endif
#endif

/*------------------------------------------------------------------------ */
/* Mega support */
#if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__)
/*------------------------------------------------------------------------ */
 /* Onboard LED is connected to pin PB7 on Arduino Mega1280 */ 
 #if (LED == n) && ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
  #warning "LED bit is set to default B7"
  #define LEDX	nB7
 #else
  #define LEDX   LED
 #endif

 /* Default "SOFT" UART Ports for ATmega1280 */
 #if UART_RX == n
  #if UART_NR == 0
   #if SOFT_UART > 0
    #warning "ATmega use Pin E0 as RX for soft UART 0"
   #endif		/* SOFT_UART > 0 */
   #define UART_RXX	nE0
  #endif
  #if UART_NR == 1
   #if SOFT_UART > 0
    #warning "ATmega use Pin D2 as RX for soft UART 1"
   #endif		/* SOFT_UART > 0 */
   #define UART_RXX	nD2
  #endif
  #if UART_NR == 2
   #if SOFT_UART > 0
    #warning "ATmega use Pin H0 as RX for soft UART 2"
   #endif		/* SOFT_UART > 0 */
   #define UART_RXX	nH0
  #endif
  #if UART_NR == 3
   #if SOFT_UART > 0
    #warning "ATmega use Pin J0 as RX for soft UART 3"
   #endif		/* SOFT_UART > 0 */
   #define UART_RXX	nJ0
  #endif
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if UART_NR == 0
   #if SOFT_UART > 0
    #warning "ATmega use Pin E1 as TX for soft UART 0"
   #endif		/* SOFT_UART > 0 */
   #define UART_TXX	nE1
  #endif
  #if UART_NR == 1
   #if SOFT_UART > 0
    #warning "ATmega use Pin D3 as TX for soft UART 1"
   #endif		/* SOFT_UART > 0 */
   #define UART_TXX	nD3
  #endif
  #if UART_NR == 2
   #if SOFT_UART > 0
    #warning "ATmega use Pin H1 as TX for soft UART 2"
   #endif		/* SOFT_UART > 0 */
   #define UART_TXX	nH1
  #endif
  #if UART_NR == 3
   #if SOFT_UART > 0
    #warning "ATmega use Pin J1 as TX for soft UART 3"
   #endif		/* SOFT_UART > 0 */
   #define UART_TXX	nJ1
  #endif
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_ATmega640__ || __AVR_ATmega1280__ */

/*------------------------------------------------------------------------ */
/* Settings for all processors */
/*------------------------------------------------------------------------ */



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
 #define WATCHDOG_4S     (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE)) /* 2 seconds are max */
 #define WATCHDOG_8S     (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE)) /* 2 seconds are max */
#endif


// The Preprocessor should have replaced LEDX with a constant now
#if ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
 #if (LEDX & 0xff) > 7
  #error "Unrecognized LED name. Should be like 'B5' "
  #error "probably the bit number is wrong!"
 #endif
 #if ((LEDX >> 8) > 12) || ((LEDX & 0xff00) == 0)
  #error "Unrecognized LED name.  Should be like 'B5' "
  #error "probably the port is wrong!"
 #endif

// LEDbit must be set to the bit number of the selected Port.
// This is allways given by the lower Byte of the previous definition
 #define LEDbit (LEDX & 0x07)
#endif

// setup for UART_RX
//#if SOFT_UART > 0
 #if ((UART_RXX & 0xff) > 7) || ((UART_RXX >> 8) > 12) || ((UART_RXX & 0xff00) == 0)
  #error "Unrecognized UART_RX name.  Should be like 'B5'"
  #error "You can only select a existing port for the target processor!"
 #endif
 // setup for UART_TX
 #if ((UART_TXX & 0xff) > 7) || ((UART_TXX >> 8) > 12) || ((UART_TXX & 0xff00) == 0)
  #error "Unrecognized UART_TX name.  Should be like 'B5'"
  #error "You can only select a existing port for the target processor!"
 #endif
 // UART_RX_BIT must be set to the bit number of the selected Port.
 // This is allways given by the lower Byte of the previous definition
 #define UART_RX_BIT (UART_RXX & 0x07)
 // the same must be set for the TX_BIT
 #define UART_TX_BIT (UART_TXX & 0x07)
//#else		/* Hardware UART */
#if SOFT_UART == 0
 /*
  * Handle devices with up to 4 uarts (eg m1280.)  Rather inelegantly.
  * Note that mega8/m32 still needs special handling, because ubrr is handled
  * differently.
  */
 #if UART_NR == 0
  #if !defined(UDR0)
   #error "UART == 0, but no UART0 on device"
  #endif
  #define UART_SRA UCSR0A
  #define UART_SRB UCSR0B
  #ifdef UCSR0C
   #define UART_SRC UCSR0C
  #endif
  #define UART_SRRL UBRR0L
  #define UART_SRRH UBRR0H
  #define UART_UDR UDR0
 #elif UART_NR == 1
  #if !defined(UDR1)
   #error "UART == 1, but no UART1 on device"
  #endif
  #define UART_SRA UCSR1A
  #define UART_SRB UCSR1B
  #define UART_SRC UCSR1C
  #define UART_SRRL UBRR1L
  #define UART_SRRH UBRR1H
  #define UART_UDR UDR1
 #elif UART_NR == 2
  #if !defined(UDR2)
   #error "UART == 2, but no UART2 on device"
  #endif
  #define UART_SRA UCSR2A
  #define UART_SRB UCSR2B
  #define UART_SRC UCSR2C
  #define UART_SRRL UBRR2L
  #define UART_SRRH UBRR2H
  #define UART_UDR UDR2
 #elif UART_NR == 3
  #if !defined(UDR3)
   #error "UART == 3, but no UART3 on device"
  #endif
  #define UART_SRA UCSR3A
  #define UART_SRB UCSR3B
  #define UART_SRC UCSR3C
  #define UART_SRRL UBRR3L
  #define UART_SRRH UBRR3H
  #define UART_UDR UDR3
 #else
  #error "Unknown UART number, only 0 to 3 !!!"
 #endif

#endif		/* SOFT_UART > 0 */

// setup the Port definitions for LED
#if ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0))
 #if (LEDX & 0xff00) == nB0
  #define LED_DDR     DDRB
  #define LED_PORT    PORTB
  #define LED_PIN     PINB
 #elif (LEDX & 0xff00) == nC0
  #define LED_DDR     DDRC
  #define LED_PORT    PORTC
  #define LED_PIN     PINC
 #elif (LEDX & 0xff00) == nD0
  #define LED_DDR     DDRD
  #define LED_PORT    PORTD
  #define LED_PIN     PIND
 #elif (LEDX & 0xff00) == nE0
  #define LED_DDR     DDRE
  #define LED_PORT    PORTE
  #define LED_PIN     PINE
 #elif (LEDX & 0xff00) == nF0
  #define LED_DDR     DDRF
  #define LED_PORT    PORTF
  #define LED_PIN     PINF
 #elif (LEDX & 0xff00) == nG0
  #define LED_DDR     DDRG
  #define LED_PORT    PORTG
  #define LED_PIN     PING
 #elif (LEDX & 0xff00) == nH0
  #define LED_DDR     DDRH
  #define LED_PORT    PORTH
  #define LED_PIN     PINH
 #elif (LEDX & 0xff00) == nJ0
  #define LED_DDR     DDRJ
  #define LED_PORT    PORTJ
  #define LED_PIN     PINJ
 #elif (LEDX & 0xff00) == nK0
  #define LED_DDR     DDRK
  #define LED_PORT    PORTK
  #define LED_PIN     PINK
 #elif (LEDX & 0xff00) == nL0
  #define LED_DDR     DDRL
  #define LED_PORT    PORTL
  #define LED_PIN     PINL
 #elif (LEDX & 0xff00) == nA0
  #define LED_DDR     DDRA
  #define LED_PORT    PORTA
  #define LED_PIN     PINA
 
 #else
  #error "--------------------------------------------"
  #error "Unrecognized LED name.  Should be like 'B4' "
  #error "--------------------------------------------"
 #endif
#endif		/*# ((LED_DATA_FLASH > 0) || (LED_START_FLASHES != 0)) */

//#if SOFT_UART > 0
 // setup the Port definitions for UART_RX
 #if (UART_RXX & 0xff00) == nB0
  #define UART_RX_DDR     DDRB
  #define UART_RX_PORT    PORTB
  #define UART_RX_PIN     PINB
 #elif (UART_RXX & 0xff00) == nC0
  #define UART_RX_DDR     DDRC
  #define UART_RX_PORT    PORTC
  #define UART_RX_PIN     PINC
 #elif (UART_RXX & 0xff00) == nD0
  #define UART_RX_DDR     DDRD
  #define UART_RX_PORT    PORTD
  #define UART_RX_PIN     PIND
 #elif (UART_RXX & 0xff00) == nE0
  #define UART_RX_DDR     DDRE
  #define UART_RX_PORT    PORTE
  #define UART_RX_PIN     PINE
 #elif (UART_RXX & 0xff00) == nF0
  #define UART_RX_DDR     DDRF
  #define UART_RX_PORT    PORTF
  #define UART_RX_PIN     PINF
 #elif (UART_RXX & 0xff00) == nG0
  #define UART_RX_DDR     DDRG
  #define UART_RX_PORT    PORTG
  #define UART_RX_PIN     PING
 #elif (UART_RXX & 0xff00) == nH0
  #define UART_RX_DDR     DDRH
  #define UART_RX_PORT    PORTH
  #define UART_RX_PIN     PINH
 #elif (UART_RXX & 0xff00) == nJ0
  #define UART_RX_DDR     DDRJ
  #define UART_RX_PORT    PORTJ
  #define UART_RX_PIN     PINJ
 #elif (UART_RXX & 0xff00) == nK0
  #define UART_RX_DDR     DDRK
  #define UART_RX_PORT    PORTK
  #define UART_RX_PIN     PINK
 #elif (UART_RXX & 0xff00) == nL0
  #define UART_RX_DDR     DDRL
  #define UART_RX_PORT    PORTL
  #define UART_RX_PIN     PINL
 #elif (UART_RXX & 0xff00) == nA0
  #define UART_RX_DDR     DDRA
  #define UART_RX_PORT    PORTA
  #define UART_RX_PIN     PINA
 
 #else
  #error -------------------------------------------
  #error Unrecognized UART_RX name.  Should be like "B5"
  #error -------------------------------------------
 #endif
//#endif 		/* SOFT_UART > 0 */


//#if SOFT_UART > 0
 // setup the Port definitions for UART_TX
 #if (UART_TXX & 0xff00) == nB0
  #define UART_TX_DDR     DDRB
  #define UART_TX_PORT    PORTB
  #define UART_TX_PIN     PINB
 #elif (UART_TXX & 0xff00) == nC0
  #define UART_TX_DDR     DDRC
  #define UART_TX_PORT    PORTC
  #define UART_TX_PIN     PINC
 #elif (UART_TXX & 0xff00) == nD0
  #define UART_TX_DDR     DDRD
  #define UART_TX_PORT    PORTD
  #define UART_TX_PIN     PIND
 #elif (UART_TXX & 0xff00) == nE0
  #define UART_TX_DDR     DDRE
  #define UART_TX_PORT    PORTE
  #define UART_TX_PIN     PINE
 #elif (UART_TXX & 0xff00) == nF0
  #define UART_TX_DDR     DDRF
  #define UART_TX_PORT    PORTF
  #define UART_TX_PIN     PINF
 #elif (UART_TXX & 0xff00) == nG0
  #define UART_TX_DDR     DDRG
  #define UART_TX_PORT    PORTG
  #define UART_TX_PIN     PING
 #elif (UART_TXX & 0xff00) == nH0
  #define UART_TX_DDR     DDRH
  #define UART_TX_PORT    PORTH
  #define UART_TX_PIN     PINH
 #elif (UART_TXX & 0xff00) == nJ0
  #define UART_TX_DDR     DDRJ
  #define UART_TX_PORT    PORTJ
  #define UART_TX_PIN     PINJ
 #elif (UART_TXX & 0xff00) == nK0
  #define UART_TX_DDR     DDRK
  #define UART_TX_PORT    PORTK
  #define UART_TX_PIN     PINK
 #elif (UART_TXX & 0xff00) == nL0
  #define UART_TX_DDR     DDRL
  #define UART_TX_PORT    PORTL
  #define UART_TX_PIN     PINL
 #elif (UART_TXX & 0xff00) == nA0
  #define UART_TX_DDR     DDRA
  #define UART_TX_PORT    PORTA
  #define UART_TX_PIN     PINA
 
 #else
  #error -------------------------------------------
  #error Unrecognized UART_TX name.  Should be like "B5"
  #error -------------------------------------------
 #endif
//#endif 		/* SOFT_UART > 0 */

#if (UART_TXX == UART_RXX)
 #define UART_ONE_WIRE 
 #ifdef INVERS_UART
  #warning UART RX and TX to the same Port Bit not possible with INVERS_UART! Option is canceled!
  #undef INVERS_UART
 #endif
 #if SOFT_UART == 0
  #warning "for using One-Wire mode with hardware UART, please connect TX and RX pin!"
 #endif
#endif

/* Virtual boot partition support */
#ifdef VIRTUAL_BOOT_PARTITION
 #define rstVect0_sav (*(uint8_t*)(RAMSTART+SPM_PAGESIZE*2+4))
 #define rstVect1_sav (*(uint8_t*)(RAMSTART+SPM_PAGESIZE*2+5))
 #define saveVect0_sav (*(uint8_t*)(RAMSTART+SPM_PAGESIZE*2+6))
 #define saveVect1_sav (*(uint8_t*)(RAMSTART+SPM_PAGESIZE*2+7))
// Vector to save original reset jump:
//   SPM Ready is least probably used, so it's default
//   if not, use old way WDT_vect_num,
//   or simply set custom save_vect_num in Makefile using vector name
//   or even raw number.
 #if !defined(SPM_RDY_vect_num) && defined(SPM_READY_vect_num)
  // rename _READY_ to _RDY_
  #define SPM_RDY_vect_num (SPM_READY_vect_num)
 #endif

 #if !defined(EE_RDY_vect_num) && defined(EE_READY_vect_num)
  // rename _READY_ to _RDY_
  #define EE_RDY_vect_num (EE_READY_vect_num)
 #elif !defined(EE_RDY_vect_num) && defined(EEPROM_Ready_vect_num)
  // rename EEPROM_Ready_ to EE_RDY
  #define EE_RDY_vect_num (EEPROM_Ready_vect_num)
 #endif

 #if !defined(WDT_vect_num) && defined(WDT_OVERFLOW_vect_num)
  // rename _OVERFLOW_ to _
  #define WDT_vect_num (WDT_OVERFLOW_vect_num)
 #endif

 #if FLASHEND > 8192
  #define Vect2Byte 4
 #else
  #define Vect2Byte 2
 #endif

 #if !defined (save_vect_num)
  #if (defined (SPM_RDY_vect_num)) && ((SPM_RDY_vect_num * Vect2Byte) < (SPM_PAGESIZE*2))
   #warning "SPM_RDY_vect_num is selected as save_vect_num for virtual boot partition!"
   #define save_vect_num (SPM_RDY_vect_num)
  #elif (defined (EE_RDY_vect_num)) && ((EE_RDY_vect_num * Vect2Byte) < (SPM_PAGESIZE*2))
   #warning "EE_RDY_vect_num is selected as save_vect_num for virtual boot partition!"
   #define save_vect_num (EE_RDY_vect_num)
  #elif (defined (WDT_vect_num)) && ((WDT_vect_num * Vect2Byte) < (SPM_PAGESIZE*2))
   #warning "WDT_vect_num is selected as save_vect_num for virtual boot partition!"
   #define save_vect_num (WDT_vect_num)
  #else
   #error "Cant find SPM, EE or WDT interrupt vector for this CPU to support virtual boot partition"
  #endif
 #endif //save_vect_num

 // check if it's on the same page (code assumes that)
 #if ((SPM_PAGESIZE*2) <= (save_vect_num * Vect2Byte))
  #error "Save vector not in the same page as reset vector!"
 #endif

 #if FLASHEND > 8192
  // AVRs with more than 8k of flash have 4-byte vectors, and use jmp.
  //  We save only 16 bits of address, so devices with more than 128KB
  //  may behave wrong for upper part of address space.
  #define rstVect0 2
  #define rstVect1 3
  #define save_vect_addr (save_vect_num*4)
  #define saveVect0 (save_vect_num*4+2)
  #define saveVect1 (save_vect_num*4+3)
  #define appstart_vec (save_vect_num*2)
 #else
  // AVRs with up to 8k of flash have 2-byte vectors, and use rjmp.
  #define rstVect0 0
  #define rstVect1 1
  #define save_vect_addr (save_vect_num*2)
  #define saveVect0 (save_vect_num*2)
  #define saveVect1 (save_vect_num*2+1)
  #define appstart_vec (save_vect_num)
 #endif
#else
 #define appstart_vec (0)
#endif // VIRTUAL_BOOT_PARTITION


// setup some Macros for Assembly language use to simplify the port access
#ifdef __ASSEMBLER__

/* define AOUT macro */
/* AOUT select automatically the right instruction "out" or "sts" depending on argument. */
	.macro	AOUT adr, reg
	.if	_SFR_IO_REG_P(\adr)
	out	_SFR_IO_ADDR(\adr), \reg
	.else
	sts	_SFR_MEM_ADDR(\adr), \reg
	.endif
	.endm
/* define AIN macro */
/* AIN select automatically the right instruction "in" or "lds" depending on argument. */
	.macro	AIN reg, adr
	.if	_SFR_IO_REG_P(\adr)
	in	\reg, _SFR_IO_ADDR(\adr)
	.else
	lds	\reg, _SFR_MEM_ADDR(\adr)
	.endif
	.endm
/* define ASBIC macro */
/* AIN select automatically the right instruction "sbic" or "lds; sbrc" depending on argument. */
	.macro	ASBIC adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbic	_SFR_IO_ADDR(\adr), \bit
	.else
	 .if	_SFR_IO_REG_P(\adr)
	in	r0, _SFR_IO_ADDR(\adr)
	 .else
	lds	r0, _SFR_MEM_ADDR(\adr)
	 .endif
	sbrc	r0, \bit
	.endif
	.endm
/* define ASBIS macro */
/* AIN select automatically the right instruction "sbis" or "lds; sbrs" depending on argument. */
	.macro	ASBIS adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbis	_SFR_IO_ADDR(\adr), \bit
	.else
	 .if	_SFR_IO_REG_P(\adr)
	in	r0, _SFR_IO_ADDR(\adr)
	 .else
	lds	r0, _SFR_MEM_ADDR(\adr)
	 .endif
	sbrs	r0, \bit
	.endif
	.endm
/* define ASBI macro */
/* AIN select automatically the right instruction "sbi" or "lds; sbr; sts" depending on argument. */
	.macro	ASBI adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbi	_SFR_IO_ADDR(\adr), \bit
	.else
	 .if	_SFR_IO_REG_P(\adr)
	in	r25, _SFR_IO_ADDR(\adr)
	sbr	r25, \bit
	out	_SFR_IO_ADDR(\adr), r25
	 .else
	lds	r25, _SFR_MEM_ADDR(\adr)
	sbr	r25, \bit
	sts	_SFR_MEM_ADDR(\adr), r25
	 .endif
	.endif
	.endm
/* define ACBI macro */
/* AIN select automatically the right instruction "sbi" or "lds; cbr; sts" depending on argument. */
	.macro	ACBI adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	cbi	_SFR_IO_ADDR(\adr), \bit
	.else
	 .if	_SFR_IO_REG_P(\adr)
	in	r25, _SFR_IO_ADDR(\adr)
	cbr	r25, \bit
	out	_SFR_IO_ADDR(\adr), r25
	 .else
	lds	r25, _SFR_MEM_ADDR(\adr)
	cbr	r25, \bit
	sts	_SFR_MEM_ADDR(\adr), r25
	 .endif
	.endif
	.endm
#endif
