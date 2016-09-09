#ifndef UART
 #define UART 0
#endif
#ifndef SOFT_UART
 #define SOFT_UART 0
#endif
#include "short_port_codes.h"

/* First make undefined ports equal to p */
#if !defined(UART_RX)
#define UART_RX p
#endif
#if !defined(UART_TX)
#define UART_TX p
#endif


#if !defined(UDR0) && defined(UDR)
  //Name conversion R.Wiersma
  // Make the only UART to the UART0
  #define UCSR0A        UCSRA
  #define UCSR0B        UCSRB
  #define UDR0          UDR
  #define UDRE0         UDRE
  #define RXC0          RXC
  #define FE0           FE
  #define U2X0          U2X
  #define TIFR1         TIFR
  #define WDTCSR        WDTCR
  #define RXEN0         RXEN
  #define TXEN0         TXEN
  #define UBRR0L        UBRRL
  #define UDR0          UDR
#endif          /* the only UART has number 0 */

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny84__)
/*------------------------------------------------------------------------ */

/* Default "SOFT" UART Ports for ATtiny84 */
/* Ports for soft UART - left port only for now. TX/RX on PA2/PA3 */
 #undef SOFT_UART
 #define SOFT_UART 1
 #if UART_RX == p
  #define UART_RXX      pA3
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == p
  #define UART_TXX      pA2
 #else
  #define UART_TXX      UART_TX
 #endif
#endif	/* __AVR_ATtiny84__ */

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega32__) || defined(__AVR_ATmega16__)
/*------------------------------------------------------------------------ */

/* Default "SOFT" UART Ports for ATmega644/1284/32 */
 #if UART_RX == p
  #if UART == 0
   #define UART_RXX     pD0
  #else
   #define UART_RXX     pD2
  #endif
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == p
  #if UART == 0
   #define UART_TXX     pD1
  #else
   #define UART_TXX     pD3
  #endif
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_ATmega644P__  .. */

/*------------------------------------------------------------------------ */
/* Mega support */
#if defined(__AVR_ATmega1280__)
/*------------------------------------------------------------------------ */

/* Default "SOFT" UART Ports for ATmega1280 */
 #if UART_RX == p
  #if UART == 0
   #define UART_RXX     pE0
  #endif
  #if UART == 1
   #define UART_RXX     pD2
  #endif
  #if UART == 2
   #define UART_RXX     pH0
  #endif
  #if UART == 3
   #define UART_RXX     pJ0
  #endif
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == p
  #if UART == 0
   #define UART_TXX     pE1
  #endif
  #if UART == 1
   #define UART_TXX     pD3
  #endif
  #if UART == 2
   #define UART_TXX     pH1
  #endif
  #if UART == 3
   #define UART_TXX     pJ1
  #endif
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_ATmega1280__ */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || \
   defined(__AVR_ATmega328__)  || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega8__)
/*------------------------------------------------------------------------ */
/* Default "SOFT" UART Ports for ATmega08/168/328 */
 #if UART_RX == p
  #define UART_RXX      pD0
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == p
  #define UART_TXX      pD1
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_ATmega88/168/328__ */

// UART_RX_BIT must be set to the bit number of the selected Port.
// This is allways given by the lower Byte of the previous definition
#define UART_RX_BIT (UART_RXX & 0x07)
// the same must be set for the TX_BIT
#define UART_TX_BIT (UART_TXX & 0x07)

#if SOFT_UART == 0
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

#endif

// setup the Port definitions for UART_RX
#if (UART_RXX & 0xff00) == pB0
 #define UART_RX_DDR     DDRB
 #define UART_RX_PORT    PORTB
 #define UART_RX_PIN     PINB
#elif (UART_RXX & 0xff00) == pC0
 #define UART_RX_DDR     DDRC
 #define UART_RX_PORT    PORTC
 #define UART_RX_PIN     PINC
#elif (UART_RXX & 0xff00) == pD0
 #define UART_RX_DDR     DDRD
 #define UART_RX_PORT    PORTD
 #define UART_RX_PIN     PIND
#elif (UART_RXX & 0xff00) == pE0
 #define UART_RX_DDR     DDRE
 #define UART_RX_PORT    PORTE
 #define UART_RX_PIN     PINE
#elif (UART_RXX & 0xff00) == pF0
 #define UART_RX_DDR     DDRF
 #define UART_RX_PORT    PORTF
 #define UART_RX_PIN     PINF
#elif (UART_RXX & 0xff00) == pG0
 #define UART_RX_DDR     DDRG
 #define UART_RX_PORT    PORTG
 #define UART_RX_PIN     PING
#elif (UART_RXX & 0xff00) == pH0
 #define UART_RX_DDR     DDRH
 #define UART_RX_PORT    PORTH
 #define UART_RX_PIN     PINH
#elif (UART_RXX & 0xff00) == pJ0
 #define UART_RX_DDR     DDRJ
 #define UART_RX_PORT    PORTJ
 #define UART_RX_PIN     PINJ
#elif (UART_RXX & 0xff00) == pK0
 #define UART_RX_DDR     DDRK
 #define UART_RX_PORT    PORTK
 #define UART_RX_PIN     PINK
#elif (UART_RXX & 0xff00) == pL0
 #define UART_RX_DDR     DDRL
 #define UART_RX_PORT    PORTL
 #define UART_RX_PIN     PINL
#elif (UART_RXX & 0xff00) == pA0
 #define UART_RX_DDR     DDRA
 #define UART_RX_PORT    PORTA
 #define UART_RX_PIN     PINA

#else
#error -------------------------------------------
#error Unrecognized UART_RX name.  Should be like "B5"
#error -------------------------------------------
#endif

// setup the Port definitions for UART_TX
#if (UART_TXX & 0xff00) == pB0
 #define UART_TX_DDR     DDRB
 #define UART_TX_PORT    PORTB
 #define UART_TX_PIN     PINB
#elif (UART_TXX & 0xff00) == pC0
 #define UART_TX_DDR     DDRC
 #define UART_TX_PORT    PORTC
 #define UART_TX_PIN     PINC
#elif (UART_TXX & 0xff00) == pD0
 #define UART_TX_DDR     DDRD
 #define UART_TX_PORT    PORTD
 #define UART_TX_PIN     PIND
#elif (UART_TXX & 0xff00) == pE0
 #define UART_TX_DDR     DDRE
 #define UART_TX_PORT    PORTE
 #define UART_TX_PIN     PINE
#elif (UART_TXX & 0xff00) == pF0
 #define UART_TX_DDR     DDRF
 #define UART_TX_PORT    PORTF
 #define UART_TX_PIN     PINF
#elif (UART_TXX & 0xff00) == pG0
 #define UART_TX_DDR     DDRG
 #define UART_TX_PORT    PORTG
 #define UART_TX_PIN     PING
#elif (UART_TXX & 0xff00) == pH0
 #define UART_TX_DDR     DDRH
 #define UART_TX_PORT    PORTH
 #define UART_TX_PIN     PINH
#elif (UART_TXX & 0xff00) == pJ0
 #define UART_TX_DDR     DDRJ
 #define UART_TX_PORT    PORTJ
 #define UART_TX_PIN     PINJ
#elif (UART_TXX & 0xff00) == pK0
 #define UART_TX_DDR     DDRK
 #define UART_TX_PORT    PORTK
 #define UART_TX_PIN     PINK
#elif (UART_TXX & 0xff00) == pL0
 #define UART_TX_DDR     DDRL
 #define UART_TX_PORT    PORTL
 #define UART_TX_PIN     PINL
#elif (UART_TXX & 0xff00) == pA0
 #define UART_TX_DDR     DDRA
 #define UART_TX_PORT    PORTA
 #define UART_TX_PIN     PINA

#else
#error -------------------------------------------
#error Unrecognized UART_TX name.  Should be like "B5"
#error -------------------------------------------
#endif



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
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbic	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	\adr, r0
	sbrc	r0, \bit
        .endif
	.endm
/* define ASBIS macro */
/* AIN select automatically the right instruction "sbis" or "lds; sbrs" depending on argument. */
	.macro	ASBIS adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbis	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	\adr, r0
	sbrs	r0, \bit
        .endif
	.endm
/* define ASBI macro */
/* AIN select automatically the right instruction "sbi" or "lds; sbr; sts" depending on argument. */
	.macro	ASBI adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
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
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	cbi	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	r0, \adr
	cbr	r0, \bit
	sts	\adr, r0
        .endif
	.endm
#endif
