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

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega88__)
/*------------------------------------------------------------------------ */

/* Onboard LED is connected to pin PB5 in Arduino NG, Diecimila, and Duemilanove
 */ 
#if !defined(LED)
 #define LED B5
#endif

/* Default "SOFT" UART Ports for ATmega8/88/168/328 */
#ifdef SOFT_UART
 #if !defined(UART_RX)
  #define UART_RX D0
 #endif
 #if !defined(UART_TX)
  #define UART_TX D1
 #endif
#endif
#endif		/* __AVR_ATmega168__  ... */

/* Luminet support */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny84__)
/*------------------------------------------------------------------------ */
/* Red LED is connected to pin PA4 */ 
#if !defined(LED)
  #define LED         A4
#endif

/* Default "SOFT" UART Ports for ATtiny84 */
/* Ports for soft UART - left port only for now. TX/RX on PA2/PA3 */
#ifdef SOFT_UART
 #if !defined(UART_RX)
  #define UART_RX	A3
 #endif
 #if !defined(UART_TX)
  #define UART_TX	A2
 #endif
#endif
#endif	/* __AVR_ATtiny84__ */

/*------------------------------------------------------------------------ */
/* Sanguino support (and other 40pin DIP cpus) */
#if defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega32__)
/*------------------------------------------------------------------------ */
/* Onboard LED is connected to pin PB0 on Sanguino */ 
#if !defined(LED)
 #define LED         B0
#endif

/* Default "SOFT" UART Ports for ATmega644/1284/32 */
#ifdef SOFT_UART
 #if !defined(UART_RX)
  #define UART_RX D0
 #endif
 #if !defined(UART_TX)
  #define UART_TX D1
 #endif
#endif
#endif		/* __AVR_ATmega644P__  .. */

#if defined(__AVR_ATmega32__)
  #define WDCE		WDTOE
#endif

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

#if !defined(UDR0) && defined(UDR)
  //Name conversion R.Wiersma
  // Make the only UART to the UART0
  #define UCSR0A	UCSRA
  #define UCSR0B	UCSRB
  #define UDR0 		UDR
  #define UDRE0 	UDRE
  #define RXC0		RXC
  #define FE0           FE
  #define U2X0		U2X
  #define TIFR1 	TIFR
  #define WDTCSR	WDTCR
  #define RXEN0		RXEN
  #define TXEN0		TXEN
  #define UBRR0L	UBRRL
  #define UDR0		UDR
#endif		/* __AVR_ATmega8__ */


/*------------------------------------------------------------------------ */
/* Mega support */
#if defined(__AVR_ATmega1280__)
/*------------------------------------------------------------------------ */
/* Onboard LED is connected to pin PB7 on Arduino Mega */ 
#if !defined(LED)
#define LED B7
#endif

/* Default "SOFT" UART Ports for ATmega1280 */
#ifdef SOFT_UART
 #if !defined(UART_RX)
  #define UART_RX E0
 #endif
 #if !defined(UART_TX)
  #define UART_TX E1
 #endif
#endif
#endif		/* __AVR_ATmega1280__ */

/*
 * ------------------------------------------------------------------------
 * A bunch of macros to enable the LED to be specifed as "B5" for bit 5 
 * of port B, and similar.
 */

#ifdef PORTA
#define A0 0x100
#define A1 0x101
#define A2 0x102
#define A3 0x103
#define A4 0x104
#define A5 0x105
#define A6 0x106
#define A7 0x107
#endif

#ifdef PORTB
#define B0 0x200
#define B1 0x201
#define B2 0x202
#define B3 0x203
#define B4 0x204
#define B5 0x205
#define B6 0x206
#define B7 0x207
#endif

#ifdef PORTC
#define C0 0x300
#define C1 0x301
#define C2 0x302
#define C3 0x303
#define C4 0x304
#define C5 0x305
#define C6 0x306
#define C7 0x307
#endif

#ifdef PORTD
#define D0 0x400
#define D1 0x401
#define D2 0x402
#define D3 0x403
#define D4 0x404
#define D5 0x405
#define D6 0x406
#define D7 0x407
#endif

#ifdef PORTE
#define E0 0x500
#define E1 0x501
#define E2 0x502
#define E3 0x503
#define E4 0x504
#define E5 0x505
#define E6 0x506
#define E7 0x507
#endif

#ifdef PORTF
#define F0 0x600
#define F1 0x601
#define F2 0x602
#define F3 0x603
#define F4 0x604
#define F5 0x605
#define F6 0x606
#define F7 0x607
#endif

#ifdef PORTG
#define G0 0x700
#define G1 0x701
#define G2 0x702
#define G3 0x703
#define G4 0x704
#define G5 0x705
#define G6 0x706
#define G7 0x707
#endif

#ifdef PORTH
#define H0 0x800
#define H1 0x801
#define H2 0x802
#define H3 0x803
#define H4 0x804
#define H5 0x805
#define H6 0x806
#define H7 0x807
#endif

#ifdef PORTJ
#define J0 0xA00
#define J1 0xA01
#define J2 0xA02
#define J3 0xA03
#define J4 0xA04
#define J5 0xA05
#define J6 0xA06
#define J7 0xA07
#endif

#ifdef PORTK
#define K0 0xB00
#define K1 0xB01
#define K2 0xB02
#define K3 0xB03
#define K4 0xB04
#define K5 0xB05
#define K6 0xB06
#define K7 0xB07
#endif

#ifdef PORTL
#define L0 0xC00
#define L1 0xC01
#define L2 0xC02
#define L3 0xC03
#define L4 0xC04
#define L5 0xC05
#define L6 0xC06
#define L7 0xC07
#endif

// if LED is set to a correct Port Bit, the Preprocessor can replace LEDX with a constant now
#define LEDX LED
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

// setup for UART_RX
#if defined(SOFT_UART)
 #define UART_RXX UART_RX
 #if ((UART_RXX & 0xff) > 7) || ((UART_RXX >> 8) > 12) || ((UART_RXX & 0xff00) == 0)
  #error "Unrecognized UART_RX name.  Should be like 'B5'"
  #error "You can only select a existing port for the target processor!"
 #endif
 // setup for UART_TX
 #define UART_TXX UART_TX
 #if ((UART_TXX & 0xff) > 7) || ((UART_TXX >> 8) > 12) || ((UART_TXX & 0xff00) == 0)
  #error "Unrecognized UART_TX name.  Should be like 'B5'"
  #error "You can only select a existing port for the target processor!"
 #endif
 // UART_RX_BIT must be set to the bit number of the selected Port.
 // This is allways given by the lower Byte of the previous definition
 #define UART_RX_BIT (UART_RXX & 0x07)
 // the same must be set for the TX_BIT
 #define UART_TX_BIT (UART_TXX & 0x07)
#else		/* Hardware UART */
 /*
  * Handle devices with up to 4 uarts (eg m1280.)  Rather inelegantly.
  * Note that mega8/m32 still needs special handling, because ubrr is handled
  * differently.
  */
 #if UART == 0
  #if !defined(UDR0)
   #error UART == 0, but no UART0 on device
  #endif
  #define UART_SRA UCSR0A
  #define UART_SRB UCSR0B
  #define UART_SRC UCSR0C
  #define UART_SRL UBRR0L
  #define UART_UDR UDR0
 #elif UART == 1
  #if !defined(UDR1)
   #error UART == 1, but no UART1 on device
  #endif
  #define UART_SRA UCSR1A
  #define UART_SRB UCSR1B
  #define UART_SRC UCSR1C
  #define UART_SRL UBRR1L
  #define UART_UDR UDR1
 #elif UART == 2
  #if !defined(UDR2)
   #error UART == 2, but no UART2 on device
  #endif
  #define UART_SRA UCSR2A
  #define UART_SRB UCSR2B
  #define UART_SRC UCSR2C
  #define UART_SRL UBRR2L
  #define UART_UDR UDR2
 #elif UART == 3
  #if !defined(UDR3)
   #error UART == 3, but no UART3 on device
  #endif
  #define UART_SRA UCSR3A
  #define UART_SRB UCSR3B
  #define UART_SRC UCSR3C
  #define UART_SRL UBRR3L
  #define UART_UDR UDR3
 #else
  #error "Unknown UART number, only 0 to 3 !!!"
 #endif

#endif		/* defined(SOFT_UART) */

// setup the Port definitions for LED
#if (LEDX & 0xff00) == B0
 #define LED_DDR     DDRB
 #define LED_PORT    PORTB
 #define LED_PIN     PINB
#elif (LEDX & 0xff00) == C0
 #define LED_DDR     DDRC
 #define LED_PORT    PORTC
 #define LED_PIN     PINC
#elif (LEDX & 0xff00) == D0
 #define LED_DDR     DDRD
 #define LED_PORT    PORTD
 #define LED_PIN     PIND
#elif (LEDX & 0xff00) == E0
 #define LED_DDR     DDRE
 #define LED_PORT    PORTE
 #define LED_PIN     PINE
#elif (LEDX & 0xff00) == F0
 #define LED_DDR     DDRF
 #define LED_PORT    PORTF
 #define LED_PIN     PINF
#elif (LEDX & 0xff00) == G0
 #define LED_DDR     DDRG
 #define LED_PORT    PORTG
 #define LED_PIN     PING
#elif (LEDX & 0xff00) == H0
 #define LED_DDR     DDRH
 #define LED_PORT    PORTH
 #define LED_PIN     PINH
#elif (LEDX & 0xff00) == J0
 #define LED_DDR     DDRJ
 #define LED_PORT    PORTJ
 #define LED_PIN     PINJ
#elif (LEDX & 0xff00) == K0
 #define LED_DDR     DDRK
 #define LED_PORT    PORTK
 #define LED_PIN     PINK
#elif (LEDX & 0xff00) == L0
 #define LED_DDR     DDRL
 #define LED_PORT    PORTL
 #define LED_PIN     PINL
#elif (LEDX & 0xff00) == A0
 #define LED_DDR     DDRA
 #define LED_PORT    PORTA
 #define LED_PIN     PINA

#else
#error "--------------------------------------------"
#error "Unrecognized LED name.  Should be like 'B4' "
#error "--------------------------------------------"
#endif

#if defined(SOFT_UART)
// setup the Port definitions for UART_RX
#if (UART_RXX & 0xff00) == B0
 #define UART_RX_DDR     DDRB
 #define UART_RX_PORT    PORTB
 #define UART_RX_PIN     PINB
#elif (UART_RXX & 0xff00) == C0
 #define UART_RX_DDR     DDRC
 #define UART_RX_PORT    PORTC
 #define UART_RX_PIN     PINC
#elif (UART_RXX & 0xff00) == D0
 #define UART_RX_DDR     DDRD
 #define UART_RX_PORT    PORTD
 #define UART_RX_PIN     PIND
#elif (UART_RXX & 0xff00) == E0
 #define UART_RX_DDR     DDRE
 #define UART_RX_PORT    PORTE
 #define UART_RX_PIN     PINE
#elif (UART_RXX & 0xff00) == F0
 #define UART_RX_DDR     DDRF
 #define UART_RX_PORT    PORTF
 #define UART_RX_PIN     PINF
#elif (UART_RXX & 0xff00) == G0
 #define UART_RX_DDR     DDRG
 #define UART_RX_PORT    PORTG
 #define UART_RX_PIN     PING
#elif (UART_RXX & 0xff00) == H0
 #define UART_RX_DDR     DDRH
 #define UART_RX_PORT    PORTH
 #define UART_RX_PIN     PINH
#elif (UART_RXX & 0xff00) == J0
 #define UART_RX_DDR     DDRJ
 #define UART_RX_PORT    PORTJ
 #define UART_RX_PIN     PINJ
#elif (UART_RXX & 0xff00) == K0
 #define UART_RX_DDR     DDRK
 #define UART_RX_PORT    PORTK
 #define UART_RX_PIN     PINK
#elif (UART_RXX & 0xff00) == L0
 #define UART_RX_DDR     DDRL
 #define UART_RX_PORT    PORTL
 #define UART_RX_PIN     PINL
#elif (UART_RXX & 0xff00) == A0
 #define UART_RX_DDR     DDRA
 #define UART_RX_PORT    PORTA
 #define UART_RX_PIN     PINA

#else
#error -------------------------------------------
#error Unrecognized UART_RX name.  Should be like "B5"
#error -------------------------------------------
#endif
#endif 		/* defined(SOFT_UART) */


#if defined(SOFT_UART)
// setup the Port definitions for UART_TX
#if (UART_TXX & 0xff00) == B0
 #define UART_TX_DDR     DDRB
 #define UART_TX_PORT    PORTB
 #define UART_TX_PIN     PINB
#elif (UART_TXX & 0xff00) == C0
 #define UART_TX_DDR     DDRC
 #define UART_TX_PORT    PORTC
 #define UART_TX_PIN     PINC
#elif (UART_TXX & 0xff00) == D0
 #define UART_TX_DDR     DDRD
 #define UART_TX_PORT    PORTD
 #define UART_TX_PIN     PIND
#elif (UART_TXX & 0xff00) == E0
 #define UART_TX_DDR     DDRE
 #define UART_TX_PORT    PORTE
 #define UART_TX_PIN     PINE
#elif (UART_TXX & 0xff00) == F0
 #define UART_TX_DDR     DDRF
 #define UART_TX_PORT    PORTF
 #define UART_TX_PIN     PINF
#elif (UART_TXX & 0xff00) == G0
 #define UART_TX_DDR     DDRG
 #define UART_TX_PORT    PORTG
 #define UART_TX_PIN     PING
#elif (UART_TXX & 0xff00) == H0
 #define UART_TX_DDR     DDRH
 #define UART_TX_PORT    PORTH
 #define UART_TX_PIN     PINH
#elif (UART_TXX & 0xff00) == J0
 #define UART_TX_DDR     DDRJ
 #define UART_TX_PORT    PORTJ
 #define UART_TX_PIN     PINJ
#elif (UART_TXX & 0xff00) == K0
 #define UART_TX_DDR     DDRK
 #define UART_TX_PORT    PORTK
 #define UART_TX_PIN     PINK
#elif (UART_TXX & 0xff00) == L0
 #define UART_TX_DDR     DDRL
 #define UART_TX_PORT    PORTL
 #define UART_TX_PIN     PINL
#elif (UART_TXX & 0xff00) == A0
 #define UART_TX_DDR     DDRA
 #define UART_TX_PORT    PORTA
 #define UART_TX_PIN     PINA

#else
#error -------------------------------------------
#error Unrecognized UART_TX name.  Should be like "B5"
#error -------------------------------------------
#endif
#endif 		/* defined(SOFT_UART) */

// setup some Macros for Assembly language use to simplify the port access
#ifdef __ASSEMBLER__

/* define AOUT macro */
/* AOUT select automatically the right instruction "out" or "sts" depending on argument. */
	.macro	AOUT adr, reg
	.if	_SFR_IO_REG_P(\adr)
	out	_SFR_IO_ADDR(\adr), \reg
	.else
	sts	\adr,\reg
	.endif
	.endm
/* define AIN macro */
/* AIN select automatically the right instruction "in" or "lds" depending on argument. */
	.macro	AIN reg, adr
	.if	_SFR_IO_REG_P(\adr)
	in	\reg, _SFR_IO_ADDR(\adr)
	.else
	lds	\reg, \adr
	.endif
	.endm
/* define ASBIC macro */
/* AIN select automatically the right instruction "sbic" or "lds; sbrc" depending on argument. */
	.macro	ASBIC adr, bit
	.if	_SFR_IO_REG_P(\adr)
	sbic	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	\adr, r0
	sbrc	r0, \bit
        .endif
	.endm
/* define ASBIS macro */
/* AIN select automatically the right instruction "sbis" or "lds; sbrs" depending on argument. */
	.macro	ASBIS adr, bit
	.if	_SFR_IO_REG_P(\adr)
	sbis	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	\adr, r0
	sbrs	r0, \bit
        .endif
	.endm
/* define ASBI macro */
/* AIN select automatically the right instruction "sbi" or "lds; sbr; sts" depending on argument. */
	.macro	ASBI adr, bit
	.if	_SFR_IO_REG_P(\adr)
	sbi	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	r0, \adr
	sbr	r0, \bit
	sts	\adr, r0
        .endif
	.endm
/* define ACBI macro */
/* AIN select automatically the right instruction "sbi" or "lds; cbr; sts" depending on argument. */
	.macro	ACBI adr, bit
	.if	_SFR_IO_REG_P(\adr)
	cbi	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	r0, \adr
	cbr	r0, \bit
	sts	\adr, r0
        .endif
	.endm
#endif
