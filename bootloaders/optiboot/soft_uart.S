
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
;
; the two functions getch and putch can serve a half duplex
; serial communication with the baud rate specified with BAUD_RATE.
; The clock frequency F_CPU and features of the selected port 
; are respected to get the nearest possible real baud rate.
;
; The Option QuickStopBit let the function putch return
; after output of the last data bit. The serial output is set to 1
; for the begin of the stop bit,
; but the Baud-time of the stop bit is not monitored correctly.
; So the program has more time to watch the serial input.
; The next output of a start bit is delayed for one Baud-time,
; so that sequential serial output is timed correctly.
#define QuickStopBit


;**********************************************************
putch:	/*  void putch(char ch) */
	; r24 hold the data for serial output
	; use r22, r23, r25
	rcall	double_uartDelay	; work simular to a second stop bit
	ldi	r22, 10
;	ldi	r19, 0
#if	UART_TX_PORT >= (0x20 + __SFR_OFFSET)
 #if	UART_TX_PORT < (0x40 + __SFR_OFFSET)
	in	r23, _SFR_IO_ADDR(UART_TX_PORT)
 #else
	lds	r23, UART_TX_PORT
 #endif
#endif
#ifdef INVERS_UART
	clc			; clear carry for start bit
#else
	com	r24
	sec			; set carry for start bit
#endif
puplop:
#ifdef QuickStopBit
	rcall	double_uartDelay	; takes 2*(7 + UART_B_VALUE*3 + UART_R_VALUE clock tics)
#endif
	brcc	set_tx		; 1/2 clock tics
#if	UART_TX_PORT < (0x20 + __SFR_OFFSET)
	cbi	_SFR_IO_ADDR(UART_TX_PORT), UART_TX_BIT	; 1+2
	rjmp	pup2		; 1+2+2 = 5
#else
	cbr	r23, UART_TX_BIT	; 1+1
	sts	UART_TX_PORT, r23	; 1+1+2
	rjmp	pup2		; 1+1+2+2 = 6!!!!
#endif
set_tx:
#if	UART_TX_PORT < (0x20 + __SFR_OFFSET)
	sbi	_SFR_IO_ADDR(UART_TX_PORT), UART_TX_BIT	;2+2
	nop			; 2+2+1 = 5
#else
	sbr	r23, UART_TX_BIT	; 2+1
	sts	UART_TX_PORT, r23	; 2+1+2 = 5
	nop				; 2+1+2+1 = 6
#endif
pup2:
#ifndef QuickStopBit
	rcall	double_uartDelay	; takes 2*(7 + UART_B_VALUE*3 + UART_R_VALUE clock tics)
#endif
#ifdef INVERS_UART
	sec			; 5+1 set carry for stop bit
	ror	r24		; 5+1+1 shift right with carry
#else
	lsr	r24		; 5+1
#endif
	dec	r22		; 5+1+1 decrement don't touch the carry
	brne	puplop		; 5+1+1+2 = 9, total 9 +(2*7) = 23 Clock tics
      	ret

;**********************************************************
	/* call getch fetch a character from serial interface */
	; return value: r24 = new character read
	; use r22, r25 (soft)
getch:  
#if (LED_DATA_FLASH > 0) && defined(LED_PORT) && defined(LEDbit)
	ASBI	LED_PORT, LEDbit
#endif
	ldi	r22, 9
;	ldi	r19, 0
wait_start:
 #if UART_RX_PIN < (0x20 + __SFR_OFFSET)
  #ifdef INVERS_UART
	sbis	_SFR_IO_ADDR(UART_RX_PIN), UART_RX_BIT
  #else
        sbic    _SFR_IO_ADDR(UART_RX_PIN), UART_RX_BIT
  #endif
 #else
  #if UART_RX_PIN < (0x40 + __SFR_OFFSET)
        in      r25, _SFR_IO_ADDR(UART_RX_PIN)
  #else
        lds     r25, UART_RX_PIN
  #endif
  #ifdef INVERS_UART
        sbrs    r25, UART_RX_BIT
  #else
        sbrc    r25, UART_RX_BIT
  #endif
 #endif
	rjmp	wait_start	; RX bit still set, wait
	rcall	uartDelay	; wait half BAUD time
guplop:
	rcall	double_uartDelay	; takes 2*(7 + UART_B_VALUE*3 + UART_R_VALUE clock tics)
  #ifdef INVERS_UART
	sec			; 1 set carry
  #else
	clc			; 1 clear carry  
  #endif
 #if UART_RX_PIN < (0x20 + __SFR_OFFSET)
        sbic    _SFR_IO_ADDR(UART_RX_PIN), UART_RX_BIT  ; 1+1
 #else
  #if UART_RX_PIN < (0x40 + __SFR_OFFSET)
        in      r25, _SFR_IO_ADDR(UART_RX_PIN)  ; 1+1
  #else
        lds     r25, UART_RX_PIN                ; 1+2
  #endif
        sbrc    r25, UART_RX_BIT                ; 1+1+1 or 1+1+2
 #endif
  #ifdef INVERS_UART
	clc			; 1+1+1 clear carry
  #else
	sec			; 1+1+1 set carry
  #endif
	dec	r22		; 1+1+1+1
	breq	fin_g		; 1+1+1+1+1
	ror	r24		; 1+1+1+1+1+1 =6
  #if UART_RX_PIN < (0x40 + __SFR_OFFSET)
        nop                     ; 6+1 = 7  (make loop same as putch)
  #endif
  #ifdef INVERS_UART
	nop			; 6+1+1 = 8 for invers mode
  #endif
	rjmp	guplop		; 7+2 + 2*7 clock tics (22 + UART_B_VALUE*6 + UART_R_VALUE*2)
fin_g:
     	wdr		; watchdogReset();
#if (LED_DATA_FLASH > 0) && defined(LED_PORT) && defined(LEDbit)
	ACBI	LED_PORT, LEDbit
#endif
       	ret


;**********************************************************
// AVR305 equation: #define UART_B_VALUE (((F_CPU/BAUD_RATE)-23)/6)
// loop requires 9 tics
#if	(UART_TX_PORT < (0x20 + __SFR_OFFSET))
 #ifdef INVERS_UART
  #define LOOP_TICS 10
 #else
  #define LOOP_TICS 9
 #endif
#else
 #ifdef INVERS_UART
  #define LOOP_TICS 11
 #else
  #define LOOP_TICS 10
 #endif
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
  // try with double rcall uartDelay_half
  #undef CLOCKS_PER_BIT
  #undef UART_B_VALUE
  #undef UART_R_VALUE
  #define DoubleDelay
  #define CLOCKS_PER_BIT ( (F_CPU-((((4*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
  #define UART_B_VALUE ((CLOCKS_PER_BIT)/12)
  #define UART_R_VALUE ((CLOCKS_PER_BIT/4) - (UART_B_VALUE*3))
  #if UART_B_VALUE > 255
   // try with double double rcall uartDelay_2
   #undef CLOCKS_PER_BIT
   #undef UART_B_VALUE
   #undef UART_R_VALUE
   #define QuadDelay
   #define CLOCKS_PER_BIT ( (F_CPU-((((8*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
   #define UART_B_VALUE ((CLOCKS_PER_BIT)/24)
   #define UART_R_VALUE ((CLOCKS_PER_BIT/8) - (UART_B_VALUE*3))
   #if UART_B_VALUE > 255
    // try with double double rcall uartDelay_4
    #undef CLOCKS_PER_BIT
    #undef UART_B_VALUE
    #undef UART_R_VALUE
    #define OctDelay
    #define CLOCKS_PER_BIT ( (F_CPU-((((16*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
    #define UART_B_VALUE ((CLOCKS_PER_BIT)/48)
    #define UART_R_VALUE ((CLOCKS_PER_BIT/16) - (UART_B_VALUE*3))
    #if UART_B_VALUE > 255
     // try with double double rcall uartDelay_8
     #undef CLOCKS_PER_BIT
     #undef UART_B_VALUE
     #undef UART_R_VALUE
     #define SixteenDelay
     #define CLOCKS_PER_BIT ( (F_CPU-((((32*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
     #define UART_B_VALUE ((CLOCKS_PER_BIT)/96)
     #define UART_R_VALUE ((CLOCKS_PER_BIT/32) - (UART_B_VALUE*3))
     #if UART_B_VALUE > 255
      #error Baud rate too slow for soft UART
     #endif
    #endif	/* SixteenDelay */
   #endif	/* OctDelay */
  #endif	/* QuadDelay */
 #endif		/* DoubleDelay */
 #if UART_B_VALUE < 1
#error Baud rate too fast for soft UART
 #endif

;--------------------------------------------------------------------------------------
; the function double_uartDelay calls the function uartDelay twice to get
; a total delay time of the requested BAUD time.
double_uartDelay:
	rcall	uartDelay	; after first call runs to uartDelay and returns to double_uartDelay
;--------------------------------------------------------------------------------------
; The function uartDelay make a total delay time of the half BAUD time.
uartDelay:
#ifdef SixteenDelay
; The time limit for uartDelay_8 has been reached,
; so  the function uartDelay_8 is called twice to get the requested delay.
        rcall   uartDelay_8
#endif
#ifdef OctDelay
; The time limit for uartDelay_4 has been reached,
; so  the function uartDelay_4 is called twice to get the requested delay.
uartDelay_8:
        rcall   uartDelay_4
#endif
#ifdef QuadDelay
; The time limit for uartDelay_half  and uartDelay_single has been reached,
; so  the function uartDelay_2 is called twice to get the requested delay.
uartDelay_4:
	rcall	uartDelay_2
#endif
#ifdef DoubleDelay
; The time limit for uartDelay_half has been reached,
; so  the function uartDelay_half is called twice to get the requested delay.
uartDelay_2:
	rcall	uartDelay_half
#endif
; rcall uartDelay_half take RCALL_TICS + UART_B_VALUE*3 + UART_R_VALUE  clock tics
; use r25 for counting
uartDelay_half:
	ldi	r25, UART_B_VALUE
lud:
	dec	r25		; important: dec don't change the carry!
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
