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
bpsx=BAUD_RATE
bps=${bpsx/L/}
bps=${bpsx/U/}
fcpux=F_CPU
fcpu=${fcpux/L/}
fcpu=${fcpux/U/}

// echo f_cpu = $fcpu, baud = $bps
/*
 * Compute the divisor
 */
#ifdef SOFT_UART
 #if FLASHEND > 0x1ffff
  #define RCALL_TICS 9
 #else
  #define RCALL_TICS 7
 #endif
 #define CLOCKS_PER_BIT ((F_CPU-((((2*RCALL_TICS+9)*2-1)*BAUD_RATE)/2))/BAUD_RATE)
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
   // try with double rcall uartDelay_single
   #undef CLOCKS_PER_BIT
   #undef UART_B_VALUE
   #undef UART_R_VALUE
   #define QuadDelay
   #define CLOCKS_PER_BIT ( (F_CPU-((((8*RCALL_TICS+9)*2-1)*BAUD_RATE)/2) )/BAUD_RATE)
   #define UART_B_VALUE ((CLOCKS_PER_BIT)/24)
   #define UART_R_VALUE ((CLOCKS_PER_BIT/8) - (UART_B_VALUE*3))
   UartBV=$(( UART_B_VALUE ))
   UartRV=$(( UART_R_VALUE ))
   UartDelay=$(( (7 + (UartBV*3) + UartRV)*4 )) 
  #else
   UartBV=$(( UART_B_VALUE ))
   UartRV=$(( UART_R_VALUE ))
   UartDelay=$(( (7 + (UartBV*3) + UartRV)*2 )) 
  #endif        /* QuadDelay */
 #else
  UartBV=$(( UART_B_VALUE ))
  UartRV=$(( UART_R_VALUE ))
  UartDelay=$(( 7 + (UartBV*3) + UartRV )) 
 #endif         /* DoubleDelay */
BAUD_ACTUAL=$(( ($fcpu / (9 + ($UartDelay*2))) ))
BAUD_ERROR=$(( (( 100*($BAUD_ACTUAL- $bps) ) / $bps) ))
ERR_TS=$(( ((( 1000*($BAUD_ACTUAL - $bps) ) / $bps) - $BAUD_ERROR * 10) ))
ERR_TENTHS=$(( ERR_TS > 0 ? ERR_TS: -ERR_TS ))
echo BAUD RATE CHECK: Desired: $bps,  SoftUART_Real: $BAUD_ACTUAL, Error=$BAUD_ERROR.$ERR_TENTHS\%
#else
BAUD_SETTING=$(( ( ( ( ($fcpu + ($bps * 4)) / ($bps * 8)) ) - 1) ))
// echo baud setting = $BAUD_SETTING

/*
 * Based on the computer divisor, calculate the actual bitrate,
 * And the error.  Since we're all integers, we have to calculate
 * the tenths part of the error separately.
 */
BAUD_ACTUAL=$(( ($fcpu/(8 * (($BAUD_SETTING)+1))) ))
BAUD_ERROR=$(( (( 100*($BAUD_ACTUAL - $bps) ) / $bps) ))
ERR_TS=$(( ((( 1000*($BAUD_ACTUAL - $bps) ) / $bps) - $BAUD_ERROR * 10) ))
ERR_TENTHS=$(( ERR_TS > 0 ? ERR_TS: -ERR_TS ))

/*
 * Print a nice message containing the info we've calculated
 */
echo BAUD RATE CHECK: Desired: $bps,  Real: $BAUD_ACTUAL, UBRRL = $BAUD_SETTING, Error=$BAUD_ERROR.$ERR_TENTHS\%
#endif




