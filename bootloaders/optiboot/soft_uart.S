
#ifndef __ASSEMBLER__
 #define __ASSEMBLER__
#endif
#include <avr/io.h>
//#include "pin_defs.h"


;***************************************************************
;	.section .text
;	.func soft_uart
;	.global getch
;	.global putch



;**********************************************************
putch:	/*  void putch(char ch) */
	ldi	r22, 10
;	ldi	r19, 0
	.if	_SFR_IO_REG_P(UART_TX_PORT)
	.else
	lds	r0, UART_TX_PORT
	.endif
	com	r24
	sec
puplop:
	brcc	set_tx		; 1/2 clock tics
	.if	_SFR_IO_REG_P(UART_TX_PORT)
	cbi	_SFR_IO_ADDR(UART_TX_PORT), UART_TX_BIT	; 1+2
	rjmp	pup2		; 1+2+2 = 5
	.else
	cbr	r0, UART_TX_BIT	; 1+1
	sts	UART_TX_PORT, r0	; 1+1+2
	rjmp	pup2		; 1+1+2+2 = 6!!!!
	.endif
set_tx:
	.if	_SFR_IO_REG_P(UART_TX_PORT)
	sbi	_SFR_IO_ADDR(UART_TX_PORT), UART_TX_BIT	;2+2
	nop			; 2+2+1 = 5
	.else
	sbr	r0, UART_TX_BIT	; 2+1
	sts	UART_TX_PORT, r0 ; 2+1+2 = 5
	.endif
pup2:
	rcall	uartDelay	; takes 7 + UART_B_VALUE*3 + UART_R_VALUE clock tics
	rcall	uartDelay	; takes 7 + UART_B_VALUE*3 + UART_R_VALUE clock tics
	lsr	r24		; 5+1
	dec	r22		; decrement don't touch the carry
	brne	puplop		; 5+1+1+2 = 9, total 9 +(2*7) = 23 Clock tics
      	ret

;**********************************************************
	/* call getch fetch a character from serial interface */
	; return value: r24 = new character read
	; use r22, r25 (soft)
getch:  
#if (LED_DATA_FLASH > 0) && defined(LED_PORT) && defined(LEDpin)
	ASBI	LED_PORT, LEDbit
#endif
	ldi	r22, 9
;	ldi	r19, 0
wait_start:
	ASBIC	UART_RX_PIN, UART_RX_BIT
	rjmp	wait_start	; RX bit still set, wait
	rcall	uartDelay	; wait half BAUD time
guplop:
	rcall	uartDelay	; takes 7 + UART_B_VALUE*3 + UART_R_VALUE clock tics
	rcall	uartDelay	; takes 7 + UART_B_VALUE*3 + UART_R_VALUE clock tics
	clc			; 1 clear carry  
/* ASBIC macro use a sbic, if possible. Otherwise a lds, sbrc sequence is used */
/* With lds instruction two additional cycles are within the loop */
	ASBIC	UART_RX_PIN, UART_RX_BIT ; 1+1
	sec			; 1+1+1 set carry
	dec	r22		; 1+1+1+1
	breq	fin_g		; 1+1+1+1+1
	ror	r24		; 1+1+1+1+1+1 =6
	rjmp	guplop		; 6+2 + 2*7 clock tics (22 + UART_B_VALUE*6 + UART_R_VALUE*2)
				; with lds The loop takes two clock tics more (=10+14 + ...)
fin_g:
     	wdr		; watchdogReset();
#if (LED_DATA_FLASH > 0) && defined(LED_PORT) && defined(LEDpin)
	ACBI	LED_PORT, LEDbit
#endif
       	ret


;**********************************************************
// AVR305 equation: #define UART_B_VALUE (((F_CPU/BAUD_RATE)-23)/6)
// loop requires 9 tics
#if	_SFR_IO_REG_P(UART_TX_PORT)
 #define LOOP_TICS 9
#else
 #define LOOP_TICS 10
#endif
#if FLASHEND > 0x1ffff
 #define RCALL_TICS 9
#else
 #define RCALL_TICS 7
#endif
#define CLOCKS_PER_BIT ((F_CPU-((((2*RCALL_TICS+LOOP_TICS)*2-1)*BAUD_RATE)/2))/BAUD_RATE)
#define UART_B_VALUE ((CLOCKS_PER_BIT)/6)
#define UART_R_VALUE ((CLOCKS_PER_BIT/2) - (UART_B_VALUE*3))
 #if UART_B_VALUE > 255
  // try with double rcall uartDelay_single
  #undef CLOCKS_PER_BIT
  #undef UART_B_VALUE
  #undef UART_R_VALUE
  #define DoubleDelay
  #define CLOCKS_PER_BIT ( (F_CPU-((((4*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
  #define UART_B_VALUE ((CLOCKS_PER_BIT)/12)
  #define UART_R_VALUE ((CLOCKS_PER_BIT/4) - (UART_B_VALUE*3))
  #if UART_B_VALUE > 255
   // try with double double rcall uartDelay_single
   #undef CLOCKS_PER_BIT
   #undef UART_B_VALUE
   #undef UART_R_VALUE
   #define QuadDelay
   #define CLOCKS_PER_BIT ( (F_CPU-((((8*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
   #define UART_B_VALUE ((CLOCKS_PER_BIT)/24)
   #define UART_R_VALUE ((CLOCKS_PER_BIT/8) - (UART_B_VALUE*3))
   #if UART_B_VALUE > 255
    #error Baud rate too slow for soft UART
   #endif
  #endif	/* QuadDelay */
 #endif		/* DoubleDelay */
 #if UART_B_VALUE < 1
#error Baud rate too fast for soft UART
 #endif

; rcall uartDelay take 7 + UART_B_VALUE*3 + UART_R_VALUE  clock tics
; use r25 for counting
uartDelay:
#ifdef QuadDelay
	rcall	uartDelay_double
#endif
#ifdef DoubleDelay
uartDelay_double:
	rcall	uartDelay_single
#endif
uartDelay_single:
	ldi	25, UART_B_VALUE
lud:
	dec	r25
	brne	lud
; With UART_B_VALUE we can match the half bit period with multiples of 3 clock tics.
; We can add one or two clock tics for better match the required time
#if UART_R_VALUE > 0
	nop		; one additional instruction 
#endif
#if UART_R_VALUE > 1
	nop		; two additional instructions
#endif
	ret

;**********************************************************
;       .endfunc
