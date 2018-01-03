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


#if defined(UDR) && defined(UDRE)
  //Name conversion R.Wiersma
  // Make the only UART to the UART0
  #undef UDR0			/* probably Bit 0 of UDR was named so */
  #define UDR0          UDR
  #define UDRE0         UDRE
  #define RXC0          RXC
#endif          /* the only UART has number 0 */

#if !defined(TIFR1) && defined(TIFR)
  #define TIFR1         TIFR
#endif

#ifndef UBRR0L
 #if defined(UBRR)
  #define UBRR0L        UBRR
 #elif defined(UBRRL)
  #define UBRR0L        UBRRL
 #endif
#endif

#ifndef UBRR0H
 #ifdef UBRRHI
  #define UBRR0H        UBRRHI
 #elif defined(UBRRH)
  #define UBRR0H        UBRRH
 #endif
#endif

#ifndef WDTCSR
  #define WDTCSR        WDTCR
#endif

#if !defined(UCSR0A) && defined(UCSRA)
  // Make the only UART to the UART0
  #define UCSR0A        UCSRA
  #define FE0           FE
  #define U2X0          U2X
  #define UCSR0B        UCSRB
  #define RXEN0         RXEN
  #define TXEN0         TXEN
#endif

#if defined(__AVR_ATmega163__) && !defined(UCSRC)
 #define UCSR0C		_SFR_IO8(0x20)
 #define UCSZ01		2
 #define UCSZ00		1
#endif

#if !defined(UCSR0C) && defined(UCSRC)
  #define UCSR0C        UCSRC
  #define UCSZ01        UCSZ1
  #define UCSZ00        UCSZ0
#endif

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny24__) || \
    defined(__AVR_ATtiny84A__) || defined(__AVR_ATtiny44A__) || defined(__AVR_ATtiny24A__)
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
#endif	/* __AVR_ATtiny44__ || __AVR_ATtiny84__ */

/*------------------------------------------------------------------------ */
/* support for attiny841 and attiny441 */
#if defined(__AVR_ATtiny841__) || defined(__AVR_ATtiny441__) 
/*------------------------------------------------------------------------ */

 /* Default "SOFT" UART Ports for ATtiny441/841 */
 #if UART_RX == n
  #if UART_NR == 0
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin B2 as RX for UART 0"
   #endif         /* SOFT_UART > 0 */
   #define UART_RXX    pB2
  #else
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin A4 as RX for UART 1"
   #endif         /* SOFT_UART > 0 */
   #define UART_RXX    pA4
  #endif
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if UART_NR == 0
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin A7 as TX for UART 0"
   #endif         /* SOFT_UART > 0 */
   #define UART_TXX    pA7
  #else
   #if SOFT_UART > 0
    #warning "SOFT_UART use Pin A5 as TX for UART 1"
   #endif         /* SOFT_UART > 0 */
   #define UART_TXX    pA5
  #endif
 #else
  #define UART_TXX      UART_TX
 #endif
#endif          /* __AVR_ATiny841__  .. */

/*------------------------------------------------------------------------ */
/* Support for ATtiny48 and ATtiny88 */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny48__) || defined(__AVR_ATtiny88__)
/*------------------------------------------------------------------------ */
 /* Default "SOFT" UART Ports for ATtiny48/88 */
 /* Ports for soft UART - left port only for now. TX/RX on PA2/PA3 */
 #if SOFT_UART > 0
  #if UART_RX == n
   #warning "SOFT_UART use Pin D0 as RX"
   #define UART_RXX     pD0
  #else
   #define UART_RXX      UART_RX
  #endif
  #if UART_TX == n
   #warning "SOFT_UART use Pin D1 as TX"
   #define UART_TXX     pD1
  #else
   #define UART_TXX      UART_TX
  #endif
 #else
  #error "Attiny48 and ATtiny88 has no Hardware UART"
 #endif         /* SOFT_UART > 0 */
#endif  /* __AVR_ATtiny44__ || __AVR_ATtiny84__ */

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny4313__) || defined(__AVR_ATtiny4313A__) || \
    defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny2313A__)
/*------------------------------------------------------------------------ */
 #if UART_RX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin D0 as RX"
  #endif         /* SOFT_UART > 0 */
  #define UART_RXX     pD0
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin D1 as TX"
  #endif         /* SOFT_UART > 0 */
  #define UART_TXX     pD1
 #else
  #define UART_TXX      UART_TX
 #endif
#endif  /* __AVR_ATtiny4313__ || __AVR_ATtiny2313A__ */


/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny861__) || defined(__AVR_ATtiny461__) || \
    defined(__AVR_ATtiny261__) 
/*------------------------------------------------------------------------ */
 #if UART_RX == n
   #warning "SOFT_UART use Pin B1 as RX"
  #define UART_RXX     pB1
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
   #warning "SOFT_UART use Pin B2 as TX"
  #define UART_TXX     pB2
 #else
  #define UART_TXX      UART_TX
 #endif
#endif  /* __AVR_ATtiny4313__ || __AVR_ATtiny2313A__ */

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny1634__) 
/*------------------------------------------------------------------------ */
 #if UART_RX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin A7 as RX"
  #endif         /* SOFT_UART > 0 */
  #define UART_RXX     pA7
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if SOFT_UART > 0
   #warning "SOFT_UART use Pin B0 as TX"
  #endif         /* SOFT_UART > 0 */
  #define UART_TXX     pB0
 #else
  #define UART_TXX      UART_TX
 #endif
#endif  /* __AVR_ATtiny1634__  */


/* Support for ATtiny85 family*/
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny45__)  || defined(__AVR_ATtiny25__)
/*------------------------------------------------------------------------ */
 /* Default "SOFT" UART Ports for ATtiny85 */
 /* Ports for soft UART - left port only for now. TX/RX on PA2/PA3 */
 #if SOFT_UART > 0
  #if UART_RX == n
   #warning "SOFT_UART use Pin B0 as RX"
   #define UART_RXX     pB0
  #else
   #define UART_RXX      UART_RX
  #endif
  #if UART_TX == n
   #warning "SOFT_UART use Pin B1 as TX"
   #define UART_TXX     pB1
  #else
   #define UART_TXX      UART_TX
  #endif
 #else
  #error "ATtiny85 family has no hardware UART"
 #endif         /* SOFT_UART > 0 */
#endif  /* __AVR_ATtiny85__  */

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || \
    defined(__AVR_ATmega164PA__) || \
    defined(__AVR_ATmega324__) || defined(__AVR_ATmega324P__) || \
    defined(__AVR_ATmega324PA__) || \
    defined(__AVR_ATmega644__) || defined(__AVR_ATmega644P__) || \
    defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644PA__) || \
    defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || \
    defined(__AVR_ATmega1284A__) || \
    defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
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
#if defined(__AVR_ATmega162__) 
/*------------------------------------------------------------------------ */
 #if UART_RX == p
  #if UART == 0
   #define UART_RXX     pD0
  #else
   #define UART_RXX     pD1
  #endif
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == p
  #if UART == 0
   #define UART_TXX     pB2
  #else
   #define UART_TXX     pB3
  #endif
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_ATmega162__  .. */

/*------------------------------------------------------------------------ */
/* Mega support */
#if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__)
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
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || \
    defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || \
    defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || \
    defined(__AVR_ATmega8__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega88P__) || \
    defined(__AVR_ATmega48__) || defined(__AVR_ATmega48P__) || \
    defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) || \
    defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) || \
    defined(__AVR_ATmega163__) || defined(__AVR_ATmega323__)
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

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega169__) || defined(__AVR_ATmega169P__) || \
    defined(__AVR_ATmega329__) || defined(__AVR_ATmega329P__) || \
    defined(__AVR_ATmega3290__) || defined(__AVR_ATmega3290P__) || \
    defined(__AVR_ATmega649__) || defined(__AVR_ATmega649P__) || \
    defined(__AVR_ATmega6490__) || defined(__AVR_ATmega6490P__) || \
    defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__) 
/* Default "SOFT" UART Ports for ATmega169/169P ... */
 #if UART_RX == p
  #define UART_RXX      pE0
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == p
  #define UART_TXX      pE1
 #else
  #define UART_TXX      UART_TX
 #endif
#endif		/* __AVR_ATmega/169/169P */

/*------------------------------------------------------------------------ */
/* Support for AT90CAN32_64_128 */
#if defined(__AVR_AT90CAN32__) || defined(__AVR_AT90CAN64__) || defined(__AVR_AT90CAN128__) 
 /* Default "SOFT" UART Ports for AT90CAN... */
 #if UART_RX == n
  #if UART_NR == 0
   #define UART_RXX     pE0
  #else
   #define UART_RXX     pD2
  #endif
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #if UART_NR == 0
   #define UART_TXX     pE1
  #else
   #define UART_TXX     pD3
  #endif
 #else
  #define UART_TXX      UART_TX
 #endif
#endif          /* __AVR_AT90CAN... */


/*------------------------------------------------------------------------ */
#if defined(__AVR_AT90PWM2__) || defined(__AVR_AT90PWM3__) || \
    defined(__AVR_AT90PWM2B__) || defined(__AVR_AT90PWM3B__)
 /* Default "SOFT" UART Ports for AT90CAN */
 #if UART_RX == n
  #define UART_RXX      pD4
 #else
  #define UART_RXX      UART_RX
 #endif
 #if UART_TX == n
  #define UART_TXX      pD3
 #else
  #define UART_TXX      UART_TX
 #endif
#endif          /* __AVR_AT90PWM... */


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
  #define UART_SRRL UBRR0L
  #define UART_SRRH UBRR0H
  #define UART_UDR UDR0
 #elif UART == 1
  #if !defined(UDR1)
   #error UART == 1, but no UART1 on device
  #endif
  #define UART_SRA UCSR1A
  #define UART_SRB UCSR1B
  #define UART_SRC UCSR1C
  #define UART_SRRL UBRR1L
  #define UART_SRRH UBRR1H
  #define UART_UDR UDR1
 #elif UART == 2
  #if !defined(UDR2)
   #error UART == 2, but no UART2 on device
  #endif
  #define UART_SRA UCSR2A
  #define UART_SRB UCSR2B
  #define UART_SRC UCSR2C
  #define UART_SRRL UBRR2L
  #define UART_SRRH UBRR2H
  #define UART_UDR UDR2
 #elif UART == 3
  #if !defined(UDR3)
   #error UART == 3, but no UART3 on device
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
