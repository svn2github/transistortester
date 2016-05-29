
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
#define UART_TX_PORT PORTA
#define UART_TX_DDR DDRA
#define UART_TX_BIT PA2
#define UART_RX_PIN PINA
#define UART_RX_BIT PA3
#endif	/* __AVR_ATtiny84__ */

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega32__) || defined(__AVR_ATmega16__)
/*------------------------------------------------------------------------ */

/* Default "SOFT" UART Ports for ATmega644/1284/32 */
#define UART_TX_PORT PORTD
#define UART_TX_DDR DDRD
#define UART_TX_BIT PD1
#define UART_RX_PIN PIND
#define UART_RX_BIT PD0
#endif		/* __AVR_ATmega644P__  .. */

/*------------------------------------------------------------------------ */
/* Mega support */
#if defined(__AVR_ATmega1280__)
/*------------------------------------------------------------------------ */

/* Default "SOFT" UART Ports for ATmega1280 */
#define UART_TX_PORT PORTE
#define UART_TX_DDR DDRE
#define UART_TX_BIT PE1
#define UART_RX_PIN PINE
#define UART_RX_BIT PE0
#endif		/* __AVR_ATmega1280__ */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || \
   defined(__AVR_ATmega328__)  || defined(__AVR_ATmega328P__)
/*------------------------------------------------------------------------ */
/* Default "SOFT" UART Ports for ATmega08/168/328 */
#define UART_TX_PORT PORTD
#define UART_TX_DDR DDRD
#define UART_TX_BIT PD1
#define UART_RX_PIN PIND
#define UART_RX_BIT PD0
#endif		/* __AVR_ATmega88/168/328__ */


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
