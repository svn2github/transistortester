
#ifndef __ASSEMBLER__
 #define __ASSEMBLER__
#endif
#include <avr/io.h>
#include "uart_defs.h"


;***************************************************************
	.section .text
	.func soft_uart
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

#if SOFT_UART > 0
 ; soft putch() uses registers r22,r23 and r25
 ; #define SOFT_UART_RX_PORT UART_RX_PORT
 ; #define SOFT_UART_RX_BIT UART_RX_BIT
 #define SOFT_UART_TX_PORT UART_TX_PORT
 #define SOFT_UART_TX_BIT UART_TX_BIT
 #define NO_SOFT_UART_RX
 ; #define FORCE_ONE_WIRE_MODE
 #include "soft_uart.S"

 ; use the Pin 2 of the UART_TX_PORT as second TX
 ; You can use this port with putch_1(char c)
 #define SOFT_UART_NUMBER 1
 #define SOFT_UART_TX_PORT UART_TX_PORT
 #define SOFT_UART_TX_BIT 2	/* set second TX to Bit 2 of same TX-Port */
 #define NO_SOFT_UART_RX
 ; #define FORCE_ONE_WIRE_MODE
 #include "soft_uart.S"
#endif


;**********************************************************
;       .endfunc
