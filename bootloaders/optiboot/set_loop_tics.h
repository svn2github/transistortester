// set_loop_tics.h
// loop requires 9,10 or 11 tics depending on options and IO address
// you must define the UART_PORT makro to a valid IO port

#undef LOOP_TICS	/* new LOOP_TICS will be determined with UART_PORT address and INVERS_UART */
#if	(UART_PORT < (0x40 + __SFR_OFFSET))
 // for this Port we can use IN and OUT commands
 #ifdef INVERS_UART
  #define LOOP_TICS 10
 #else
  #define LOOP_TICS 9
 #endif
#else
 // (UART_PORT >= (0x40 + __SFR_OFFSET))
 // for this Port we must use LDS and STS commands
 #ifdef INVERS_UART
  #define LOOP_TICS 11
 #else
  #define LOOP_TICS 10
 #endif
#endif

