; you must inculde this file with the GNU C-Preprocessor instruction #include
; The #include should be placed before the serial input or serial output functions.

; The following macros must be set:
; F_CPU  = operating frequency of the AVR
; BAUD_RATE = desired Baud rate of serial output and/or input.
; LOOP_TICS = the count of loop-tics without the rcall uartDelay for one bit.
;		The loop-tics should be the same for both bit conditions (0 or 1).
;
; With this #include are some MACROS set:
; DOUBLE_DELAY_CALL is set to the function name which wast time to get a full time bit length.
; SINGLE_DELAY_CALL is set to the function name which wast time to get a half time bit length.
;			both names should be used with the serial bit output loop
; BIT_CLOCKS_0  is set to the total count of tics for the first delay loop generated.
; BIT_CLOCKS_1  is set to the total count of tics for the second delay loop generated.
; BIT_CLOCKS_2  is set to the total count of tics for the third delay loop generated.
; BIT_CLOCKS_3  is set to the total count of tics for the fourth delay loop generated.
;               This file will only generate a new loop, if the count of tics is different.
;
; The inner count loop can only count up to 255. If a lower Baud rate is requested,
; the inner loop call is automatically called 2x, 4x, 8x, 16x, 32x or 64x.
;

// AVR305 equation: #define UART_B_VALUE (((F_CPU/BAUD_RATE)-23)/6)
// loop requires 9,10 or 11 tics

#undef LOOP_TICS	/* new LOOP_TICS will be determined with UART_PORT address and INVERS_UART */
#if	(UART_PORT < (0x40 + __SFR_OFFSET))
 ; for this Port we can use IN and OUT commands
 #ifdef INVERS_UART
  #define LOOP_TICS 10
 #else
  #define LOOP_TICS 9
 #endif
#else
 ; (UART_PORT >= (0x40 + __SFR_OFFSET))
 ; for this Port we must use LDS and STS commands
 #ifdef INVERS_UART
  #define LOOP_TICS 11
 #else
  #define LOOP_TICS 10
 #endif
#endif

#undef RCALL_TICS		/* can be redefined as constant value, depends only on processor type */
#if FLASHEND > 0x1ffff
 #define RCALL_TICS 9		/* sum of tics for rcall and ret if more than 128kbyte flash */
#else
 #define RCALL_TICS 7		/* sum of tics for rcall and ret  if less than 128kbyte flash */
#endif

; Now we know all clocktics needed for generating the bit sequence,
; let's take a look, how many clock tics must be wasted with a loop to get the BAUD time.
#undef CLOCKS_PER_BIT
#undef DelayMul
#undef UART_B_VALUE
#undef UART_R_VALUE
#define DelayMul 1
#define CLOCKS_PER_BIT ((F_CPU-((((2*RCALL_TICS+LOOP_TICS)*2-1)*BAUD_RATE)/2))/BAUD_RATE)
; CLOCKS_PER_BIT is now the total clock tics required for matching the BAUD time.
#if CLOCKS_PER_BIT < 0
#error Baudrate is too high for this CPU clock frequency, please select a lower Baudrate!
#endif
#define UART_B_VALUE ((CLOCKS_PER_BIT)/6)	/* this is the required loop counter */
#define UART_R_VALUE ((CLOCKS_PER_BIT/2) - (UART_B_VALUE*3))	/* the remainder tics not serviced */
#if UART_B_VALUE > 255
 // try with double rcall BASE_DELAY_CALL
 #undef CLOCKS_PER_BIT
 #undef UART_B_VALUE
 #undef UART_R_VALUE
 #undef DelayMul
 #define DelayMul 2
 #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
 #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
 #define UART_R_VALUE ((CLOCKS_PER_BIT/(2*DelayMul)) - (UART_B_VALUE*3))
 #define DelayMul 2
 #if UART_B_VALUE > 255
  // try with double double rcall uartDelay_2
  #undef CLOCKS_PER_BIT
  #undef UART_B_VALUE
  #undef UART_R_VALUE
  #undef DelayMul
  #define DelayMul 4
  #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
  #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
  #define UART_R_VALUE ((CLOCKS_PER_BIT/(2*DelayMul)) - (UART_B_VALUE*3))
  #if UART_B_VALUE > 255
   // try with double double rcall uartDelay_4
   #undef CLOCKS_PER_BIT
   #undef UART_B_VALUE
   #undef UART_R_VALUE
   #undef DelayMul
   #define DelayMul 8
   #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
   #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
   #define UART_R_VALUE ((CLOCKS_PER_BIT/(2*DelayMul)) - (UART_B_VALUE*3))
   #if UART_B_VALUE > 255
    // try with double double rcall uartDelay_8
    #undef CLOCKS_PER_BIT
    #undef UART_B_VALUE
    #undef UART_R_VALUE
    #undef DelayMul
    #define DelayMul 16
    #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
    #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
    #define UART_R_VALUE ((CLOCKS_PER_BIT/(2*DelayMul)) - (UART_B_VALUE*3))
    #if UART_B_VALUE > 255
     // try with double double rcall uartDelay_16
     #undef CLOCKS_PER_BIT
     #undef UART_B_VALUE
     #undef UART_R_VALUE
     #undef DelayMul
     #define DelayMul 32
     #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
     #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
     #define UART_R_VALUE ((CLOCKS_PER_BIT/(6*DelayMul)) - (UART_B_VALUE*3))
     #if UART_B_VALUE > 255
      // try with double double rcall uartDelay_32
      #undef CLOCKS_PER_BIT
      #undef UART_B_VALUE
      #undef UART_R_VALUE
      #undef DelayMul
      #define DelayMul 64
      #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
      #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
      #define UART_R_VALUE ((CLOCKS_PER_BIT/(6*DelayMul)) - (UART_B_VALUE*3))
      #if UART_B_VALUE > 255
       #error Baud rate too slow for soft UART
      #endif
     #endif	/* DelayMul = 64 */
    #endif	/* DelayMul = 32 */
   #endif	/* DelayMul = 16 */
  #endif	/* DelayMul = 8 */
 #endif		/* DelayMul = 4 */
#endif		/* DelayMul = 2 */
; We don't know, if any delay routine has the same time,
; so we will check first with the C-Preprocessor.
#undef DOUBLE_DELAY_CALL
#undef SINGLE_DELAY_CALL
#undef BASE_DELAY_CALL
#define NEW_DELAY_CODE_REQUIRED
#if (CLOCKS_PER_BIT * DelayMul) == BIT_CLOCKS_0
 #define DOUBLE_DELAY_CALL double_uartDelay_0
 #define SINGLE_DELAY_CALL single_uartDelay_0
 #define BASE_DELAY_CALL half_uartDelay_0
 #undef NEW_DELAY_CODE_REQUIRED
#endif
#if (CLOCKS_PER_BIT * DelayMul) == BIT_CLOCKS_1
 #define DOUBLE_DELAY_CALL double_uartDelay_1
 #define SINGLE_DELAY_CALL single_uartDelay_1
 #define BASE_DELAY_CALL half_uartDelay_1
 #undef NEW_DELAY_CODE_REQUIRED
#endif
#if (CLOCKS_PER_BIT * DelayMul) == BIT_CLOCKS_2
 #define DOUBLE_DELAY_CALL double_uartDelay_2
 #define SINGLE_DELAY_CALL single_uartDelay_2
 #define BASE_DELAY_CALL half_uartDelay_2
 #undef NEW_DELAY_CODE_REQUIRED
#endif
#if (CLOCKS_PER_BIT * DelayMul) == BIT_CLOCKS_3
 #define DOUBLE_DELAY_CALL double_uartDelay_3
 #define SINGLE_DELAY_CALL single_uartDelay_3
 #define BASE_DELAY_CALL half_uartDelay_3
 #undef NEW_DELAY_CODE_REQUIRED
#endif
;
#ifdef NEW_DELAY_CODE_REQUIRED
; let's take a look for a free code generating slot
 #if BIT_CLOCKS_0 == 0
  #define DOUBLE_DELAY_CALL double_uartDelay_0
  #define SINGLE_DELAY_CALL single_uartDelay_0
  #define BASE_DELAY_CALL half_uartDelay_0
  #define BIT_CLOCKS_0 (CLOCKS_PER_BIT * DelayMul)
 #elif BIT_CLOCKS_1 == 0
  #define DOUBLE_DELAY_CALL double_uartDelay_1
  #define SINGLE_DELAY_CALL single_uartDelay_1
  #define BASE_DELAY_CALL half_uartDelay_1
  #define BIT_CLOCKS_1 (CLOCKS_PER_BIT * DelayMul)
 #elif BIT_CLOCKS_2 == 0
  #define DOUBLE_DELAY_CALL double_uartDelay_2
  #define SINGLE_DELAY_CALL single_uartDelay_2
  #define BASE_DELAY_CALL half_uartDelay_2
  #define BIT_CLOCKS_2 (CLOCKS_PER_BIT * DelayMul)
 #elif BIT_CLOCKS_3 == 0
  #define DOUBLE_DELAY_CALL double_uartDelay_3
  #define SINGLE_DELAY_CALL single_uartDelay_3
  #define BASE_DELAY_CALL half_uartDelay_3
  #define BIT_CLOCKS_3 (CLOCKS_PER_BIT * DelayMul)
 #else
  #error Too many different BAUD delays requested by this configuration!
 #endif
;--------------------------------------------------------------------------------------
; the function DOUBLE_DELAY_CALL calls the function uartDelay twice to get
; a total delay time of the requested BAUD time.
DOUBLE_DELAY_CALL :
	rcall	SINGLE_DELAY_CALL	; after first call runs to uartDelay and returns to DOUBLE_DELAY_CALL 
;--------------------------------------------------------------------------------------
; The function uartDelay make a total delay time of the half BAUD time.
 #if DelayMul > 1
	; set the single delay call to the top
SINGLE_DELAY_CALL :
 #endif
 #if DelayMul >= 64
; The time limit for uartDelay_32 has been reached,
; so  the function uartDelay_32 is called twice to get the requested delay.
	rcall	.+0		; double the time of 32x again
 #endif
 #if DelayMul >= 32
; The time limit for uartDelay_16 has been reached,
; so  the function uartDelay_16 is called twice to get the requested delay.
	rcall	.+0		; double the time of 16x again
 #endif
 #if DelayMul >= 16
; The time limit for uartDelay_8 has been reached,
; so  the function uartDelay_8 is called twice to get the requested delay.
	rcall	.+0		; double the time of 8x again
 #endif
 #if DelayMul >= 8
; The time limit for uartDelay_4 has been reached,
; so  the function uartDelay_4 is called twice to get the requested delay.
	rcall	.+0		; double the time of 4x again
 #endif
 #if DelayMul >= 4
; The time limit for BASE_DELAY_CALL  and SINGLE_DELAY_CALL has been reached,
; so  the function uartDelay_2 is called twice to get the requested delay.
	rcall	.+0		; double the time  of 2x again
 #endif
 #if DelayMul >= 2
; The time limit for BASE_DELAY_CALL has been reached,
; so  the function BASE_DELAY_CALL is called twice to get the requested delay.
	rcall	BASE_DELAY_CALL
 #endif
; rcall BASE_DELAY_CALL take RCALL_TICS + UART_B_VALUE*3 + UART_R_VALUE  clock tics
; use r25 for counting
 #if ((CLOCKS_PER_BIT/2) * 2) < CLOCKS_PER_BIT
	nop
 #endif
 #if DelayMul == 1
	; set the single delay call to the basic half delay behind the nop
SINGLE_DELAY_CALL :
 #endif
BASE_DELAY_CALL:
 #if UART_B_VALUE > 0
	ldi	r25, UART_B_VALUE

	dec	r25		; important: dec don't change the carry!
	brne	.-4
 #endif
; With UART_B_VALUE we can match the half bit period with multiples of 3 clock tics.
; We can add one or two clock tics for better match the required time
 #if UART_R_VALUE == 2
	rjmp	.	; one additional instruction with 2 clock tics and no function
 #endif
 #if UART_R_VALUE == 1
	nop		; one additional instruction with 1 clock tic
 #endif
	ret
#endif		/* NEW_DELAY_CODE_REQUIRED  */
