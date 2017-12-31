/*
 * baudcheck.c
 * Mar, 2013 by Bill Westfield (WestfW@yahoo.com)
 * Exercises in executing arithmetic code on a system that we can't count
 * on having the usual languages or tools installed.
 *
 * This little "C program" is run through the C preprocessor using the same
 * arguments as our "real" target (which should assure that it gets the
 * same values for clock speed and desired baud rate), and produces as
 * output a shell script that can be run through bash, and THAT in turn
 * writes the desired output...
 *
 * Note that the C-style comments are stripped by the C preprocessor.
 * Added support for special SOFT_UART by K.-H. Kuebbeler (kh_kuebbeler@web.de)
 */

/*
 * First strip any trailing "L" from the defined constants.  To do this
 * we need to make the constants into shell variables first.
 */
// bpsx=BAUD_RATE
// bps=${bpsx/L/}
// bps=${bpsx/U/}
// determine the count of loop tics

#if	1	/* usually the Port address is lower than 0x40 */
 #ifdef INVERS_UART
  #define LOOP_TICS 10
 #else
  #define LOOP_TICS 9
 #endif
#else
 // loop can only use STS and LDS
 #ifdef INVERS_UART
  #define LOOP_TICS 11
 #else
  #define LOOP_TICS 10
 #endif
#endif

#ifndef BAUD_RATE
 #error "in check_baudrate.c is BAUD_RATE not set"
#endif
bps=`$ECHO_CMD BAUD_RATE | $TR_CMD -d LU`
#ifndef F_CPU
 #error "in check_baudrate.c is F_CPU not set"
#endif
// fcpux=F_CPU
// fcpu=${fcpux/L/}
// fcpu=${fcpux/U/}
fcpu=`$ECHO_CMD F_CPU | $TR_CMD -d LU`

// $ECHO_CMD f_cpu = $fcpu, baud = $bps
/*
 * Compute the divisor
 */
$ECHO_CMD ---------------------------------------------------------------------------
#if SOFT_UART > 0
 #if FLASHEND > 0x1ffff
  #define RCALL_TICS 9
 #else
  #define RCALL_TICS 7
 #endif
 #define DelayMul 1
 #define CLOCKS_PER_BIT ((F_CPU-((((2*RCALL_TICS+LOOP_TICS)*2-1)*BAUD_RATE)/2))/BAUD_RATE)
 #if CLOCKS_PER_BIT < 0
  #undef RCALL_TICS
  #undef CLOCKS_PER_BIT
  #define RCALL_TICS 0
  #define CLOCKS_PER_BIT ((F_CPU-((((2*RCALL_TICS+LOOP_TICS)*2-1)*BAUD_RATE)/2))/BAUD_RATE)
 #else
  #define UART_B_VALUE ((CLOCKS_PER_BIT)/6)
  #if UART_B_VALUE > 255
   // try with double rcall uartDelay_single
   #undef CLOCKS_PER_BIT
   #undef UART_B_VALUE
   #undef DelayMul
   #define DelayMul 2
   #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+LOOP_TICS)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
   #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
   #if UART_B_VALUE > 255
    // compute with 4x rcall uartDelay_single
    #undef CLOCKS_PER_BIT
    #undef UART_B_VALUE
    #undef DelayMul
    #define DelayMul 4
    #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+LOOP_TICS)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
    #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
    #if UART_B_VALUE > 255
     // compute with 8x rcall uartDelay_single
     #undef CLOCKS_PER_BIT
     #undef UART_B_VALUE
     #undef DelayMul
     #define DelayMul 8
     #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+LOOP_TICS)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
     #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
     #if UART_B_VALUE > 255
      // compute with 16 rcall uartDelay_single
      #undef CLOCKS_PER_BIT
      #undef UART_B_VALUE
      #undef DelayMul
      #define DelayMul 16
      #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+LOOP_TICS)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
      #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
      #if UART_B_VALUE > 255
       // compute with 32 rcall uartDelay_single
       #undef CLOCKS_PER_BIT
       #undef UART_B_VALUE
       #undef DelayMul
       #define DelayMul 32
       #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+LOOP_TICS)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
       #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
       #if UART_B_VALUE > 255
        // compute with 64 rcall uartDelay_single
        #undef CLOCKS_PER_BIT
        #undef UART_B_VALUE
        #undef DelayMul
        #define DelayMul 64
        #define CLOCKS_PER_BIT ( (F_CPU-(((((2*DelayMul)*RCALL_TICS+LOOP_TICS)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
        #define UART_B_VALUE ((CLOCKS_PER_BIT)/(6*DelayMul))
       #endif        /* DelayMul 64*/
      #endif        /* DelayMul 32 */
     #endif        /* DelayMul 16 */
    #endif        /* DelayMul 8 */
   #endif        /* DelayMul 4 */
  #endif         /* DelayMul 2 */
 #endif 	/* CLOCKS_PER_BIT < 0 */

delay_mul=$(( DelayMul ))
clocks=$(( (CLOCKS_PER_BIT / DelayMul) ))
UartDelay=$(( (((RCALL_TICS*2) + (CLOCKS_PER_BIT/DelayMul)) * DelayMul) + LOOP_TICS ))
 #if BAUD_RATE > 10000
$ECHO_CMD BAUD RATE CHECK: Desired: $bps,  SoftUART_Real: `$ECHO_CMD "scale=0;($fcpu / $UartDelay)" | $BC_CMD`, Delay: $clocks*$delay_mul, Error=`$ECHO_CMD "scale=2;(100*(($fcpu / $UartDelay)- $bps) ) / $bps"| $BC_CMD`\%
 #elif BAUD_RATE > 1000
$ECHO_CMD BAUD RATE CHECK: Desired: $bps,  SoftUART_Real: `$ECHO_CMD "scale=1;($fcpu / $UartDelay)" | $BC_CMD`, Delay: $clocks*$delay_mul, Error=`$ECHO_CMD "scale=2;(100*(($fcpu / $UartDelay)- $bps) ) / $bps"| $BC_CMD`\%
 #else
$ECHO_CMD BAUD RATE CHECK: Desired: $bps,  SoftUART_Real: `$ECHO_CMD "scale=2;($fcpu / $UartDelay)" | $BC_CMD`, Delay: $clocks*$delay_mul, Error=`$ECHO_CMD "scale=2;(100*(($fcpu / $UartDelay)- $bps) ) / $bps"| $BC_CMD`\%
 #endif
#else
// for hardware UART
 #define BAUD_DIV  ( ( ( F_CPU / 4L / BAUD_RATE )  - 1) / 2) 
 #if (BAUD_DIV > 255) && (BAUD_DIV < 2046)
BAUD_SETTING=$((  ( ( ($fcpu / 8 / $bps) - 1) / 2) ))
UartDelay=$(( (16 * ((BAUD_SETTING) +1)) ))
/*
 * Based on the computer divisor, calculate the actual bitrate,
 * And the error.  Since we're all integers, we have to calculate
 * the tenths part of the error separately.
 */
// BAUD_ACTUAL=$(( ($fcpu/(16 * (($BAUD_SETTING)+1))) ))

 #else
BAUD_SETTING=$(( ( ( ($fcpu / 4 / $bps ) - 1) / 2) ))
UartDelay=$(( (8 * ((BAUD_SETTING) +1)) ))
/*
 * Based on the computer divisor, calculate the actual bitrate,
 * And the error.  Since we're all integers, we have to calculate
 * the tenths part of the error separately.
 */
//BAUD_ACTUAL=$(( ($fcpu/(8 * (($BAUD_SETTING)+1))) ))

 #endif
// $ECHO_CMD baud setting = $BAUD_SETTING

/*
 * Print a nice message containing the info we've calculated
 */
 #if BAUD_RATE > 10000
$ECHO_CMD BAUD RATE CHECK: Desired: $bps,  Real: `$ECHO_CMD "scale=0;($fcpu / $UartDelay)" | $BC_CMD`, UBRR = $BAUD_SETTING, Error=`$ECHO_CMD "scale=2;(100*(($fcpu / $UartDelay) - $bps) ) / $bps"| $BC_CMD`\%
 #elif BAUD_RATE > 1000
$ECHO_CMD BAUD RATE CHECK: Desired: $bps,  Real: `$ECHO_CMD "scale=1;($fcpu / $UartDelay)" | $BC_CMD`, UBRR = $BAUD_SETTING, Error=`$ECHO_CMD "scale=2;(100*(($fcpu / $UartDelay) - $bps) ) / $bps"| $BC_CMD`\%
 #else
$ECHO_CMD BAUD RATE CHECK: Desired: $bps,  Real: `$ECHO_CMD "scale=2;($fcpu / $UartDelay)" | $BC_CMD`, UBRR = $BAUD_SETTING, Error=`$ECHO_CMD "scale=2;(100*(($fcpu / $UartDelay) - $bps) ) / $bps"| $BC_CMD`\%
 #endif
#endif	/* SOFT_UART */
$ECHO_CMD ---------------------------------------------------------------------------



