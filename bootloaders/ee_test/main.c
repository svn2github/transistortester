	#include <avr/io.h>
	#include <avr/sleep.h>
// #include <stdlib.h>
// #include <string.h>
	#include <avr/eeprom.h>
	#include <avr/pgmspace.h>
	#include <avr/wdt.h>
	#include <math.h>
	#include <stdlib.h>
	#include <string.h>

	#define MAIN_C
	#include "wait1000ms.h"
	#include "uart_defs.h"
	#include "find_ctr.h"



const unsigned char Hello1[] PROGMEM = "Hello World from Flash!";
const unsigned char External[] PROGMEM = "External ";
const unsigned char WatchDog[] PROGMEM = "Watch-dog ";
const unsigned char BrownOut[] PROGMEM = "Brown-Out ";
const unsigned char PowerOn[] PROGMEM = "PowerOn ";
const unsigned char Interrupt[] PROGMEM = "Interrupt";

const unsigned char HW_UART[] PROGMEM = "HW_UART #";
const unsigned char SW_UART[] PROGMEM = "Soft_UART";
const unsigned char OscCal[] PROGMEM = "RC-Oscillator Calibration Byte is 0x";

const unsigned char Hello2[] EEMEM = "Hello World from EEprom!";
const unsigned char PrefixTab[] PROGMEM = { 'f','p','n','u','m',0,'k','M'}; // f,p,n,u,m,-,k,M

void putch(char data);
void putch_1(char data);

void uart_mem_string(const unsigned char *data) {
        unsigned char cc;
	for (unsigned char ii=0;ii<40;ii++) {
	  cc = pgm_read_byte(data);
	  if (cc == 0) return;
          putch(cc);
	  data++;
        }
}
void uart_ee_string(const unsigned char *data) {
        unsigned char cc;
	for (unsigned char ii=0;ii<40;ii++) {
	  cc = eeprom_read_byte(data);
	  if (cc == 0) return;
          putch(cc);
	  data++;
        }
}
void uart_string(char *data) {
        unsigned char cc;
	for (unsigned char ii=0;ii<40;ii++) {
	  cc = *data;
	  if (cc == 0) return;
          putch(cc);
	  data++;
        }
}
void uart_newline(void) {
          putch('\n');
          putch('\r');
	wait1s();
}

 void hex_putch(unsigned char ch) {
	if (ch < 10) putch('0'+ch);
	else          putch('A'-10+ch);
}
#if SOFT_UART == 0
 void putch(char ch) {
  while (!(UART_SRA & _BV(UDRE0)));
  UART_UDR = ch;
}
#endif

/* ************************************************************************
 *   display of values and units
 * ************************************************************************ */

/*
 *  display value and unit
 *  - max. 7 digits excluding "." and unit
 *
 *  requires:
 *  - value
 *  - exponent of factor related to base unit (value * 10^x)
 *    e.g: p = 10^-12 -> -12
 *  - unit character (0 = none)
 *  digits = 2 to 4 
 *  for option LONG_OUTPUT  digits can also be 5, 6 and 7
 *  Flag 0x10 for output with leading zeros
 *  Flag 0x20 for '+' Output, if not '-' 
 */

void DisplayValue(unsigned long Value, int8_t Exponent, unsigned char Unit, uint8_t xdigits)
{

  char OutBuffer[14];
  unsigned long     Limit;
  unsigned char     Prefix;             /* prefix character */
  unsigned char     Offset;             /* exponent of offset to next 10^3 step */
  uint8_t           Index;              /* index ID */
  uint8_t           digits;             /* xdigits without option */
  uint8_t           Length;             /* string length */
  uint8_t           Rshift;             /* right shift of significant bits with leading '0' */


  digits = xdigits & 0x0f;
  for(Prefix=0;Prefix<6;Prefix++) OutBuffer[Prefix] = '0';

  Limit = 100;                          /* scale value down to 2 digits */
  if (digits == 3) Limit = 1000;        /* scale value down to 3 digits */
  if (digits == 4) Limit = 10000;       /* scale value down to 4 digits */
  if (digits == 5) Limit = 100000;      /* scale value down to 5 digits */
  if (digits == 6) Limit = 1000000;     /* scale value down to 6 digits */
  if (digits == 7) Limit = 10000000;    /* scale value down to 7 digits */

  while (Value >= Limit)
  {
    Value += 5;                         /* for automatic rounding */
    // perhaps TODO: the above is not really correct, can do double rounding (2000.45 -> 2000.5 -> 2001)
    Value = Value / 10;                 /* scale down by 10^1 */
    Exponent++;                         /* increase exponent by 1 */
  }


  /*
   *  determine prefix
   */

  Index = ((unsigned char)(Exponent+17))/3;
  Offset = ((unsigned char)(6-Exponent))%3;

  /* convert value into string */

  ultoa(Value, &OutBuffer[6], 10);      // sprintf(&OutBuffer[6],"%ld%c",Value,(char)0);

  Length = strlen(&OutBuffer[6]);

  if (Length > (4+Offset))
    {
      Index++;                  /* take next prefix for better readable string */
      Offset += 3;              /* decimal point 3 to the left */
    }

  Prefix = pgm_read_byte((unsigned char *)(&PrefixTab[Index]));   /* look up prefix in table */

  /*
   *  display value
   */

  /* position of dot */
  if (((xdigits & 0x10) != 0) && (digits > Length)) {
     Rshift = (digits - Length);        // use previous filled '0' characters
  } else {
     Rshift = 0;
  }

  Exponent = (Length + Rshift) - Offset;                /* calculate position */
  if (Exponent <= 0)                    /* we have to prepend "0." */
  {
    /* 0: factor 10 / -1: factor 100 */
//    putch('0');
    putch('.');

    Rshift = Offset - Length;
  }



  if (Offset == 0) Exponent = -8;       /* disable dot if not needed */

  /* adjust position to array or disable dot if set to 0 */


  /* display value and add dot if requested */
  Index = 0;
  while (Index < (Length+Rshift))               /* loop through string */
  {
    putch(OutBuffer[Index+6-Rshift]);                /* display char */
    Index++;                            /* next one */
    if (Index == Exponent) {
      putch('.');                    /* display dot */
    }
  }

  /* display prefix and unit */

  if (Prefix != 0) {
     putch(Prefix);
  }

  if (Unit != 0) {
      putch(Unit);
  }
  return;
}

 
//
	//begin of Test program
int main(void) {

 // setup Counter 0 for frequency measurement
#if defined(TST_TCCR_A)
	TST_TCCR_A = TST_TCCR_A_SET;	// toggle OC0A on compare match
#endif
#if defined(__AVR_ATtiny48__) || defined(__AVR_ATtiny88__)
	OCR1AH = 0;
	OCR1AL = 0xff;		// set OCR1A to 255 to simulate 8-Bit counter
#endif
#if defined(TST_TCCR_B)
        CNT_ENABLE_DDR |= (1<<CNT_ENABLE_PIN);	// enable output
	TST_TCCR_B = TST_TCCR_B_SET;	// run with full clock speed
#endif

 // setup UART
#if defined(UART_SRA) && (SOFT_UART == 0) 
 // setup the correct BAUD_RATE divider for Clock-frequency F_CPU
 #define BAUD_DIV ((F_CPU + (BAUD_RATE * 4L)) / (BAUD_RATE * 8L) - 1)
 #if BAUD_DIV > 255
  #undef BAUD_DIV
  #define BAUD_DIV ((F_CPU + (BAUD_RATE * 8L)) / (BAUD_RATE * 16L) - 1)
  #if BAUD_DIV > 4095
   #error Unachievable baud rate (too slow) BAUD_RATE
  #endif // baud rate slow check
        UART_SRA = (0<<U2X0);
 #else
        UART_SRA = (1<<U2X0);
 #endif
        UART_SRB = (1<<RXEN0)|(1<<TXEN0);
 #if defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined (__AVR_ATmega32__)
        UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);	// config UART
        UBRRL = (uint8_t)BAUD_DIV;	// set the lower bits of the scaler
        UCSRC = BAUD_DIV / 256;		// set upper bits of scaler (without URSEL)
 #else
        UART_SRC = (1<<UCSZ00)|(1<<UCSZ01);		// config UART
	UART_SRRL = (uint8_t)BAUD_DIV;	// set the lower bits of scaler
	UART_SRRH = BAUD_DIV / 256;	// set the higher bits of scaler 
 #endif

#else
	// prepare serial output, software solution, normal output
 #define UART_TX1_BIT 2			/* second TX (TX1) is bit 2 of TX-Port */
 #if 1
	UART_TX_PORT |= (1<<UART_TX_BIT);		// set output to 1
	UART_TX_DDR |= (1<<UART_TX_BIT);		// enable output
	// setup for putch_1
	UART_TX_PORT |= (1<<UART_TX1_BIT);		
	UART_TX_DDR |= (1<<UART_TX1_BIT);
 #else
	UART_TX_PORT &= ~(1<<UART_TX_BIT);		// clear output to 0, OneWire
	UART_TX_DDR &= ~(1<<UART_TX_BIT);		// set to input mode!, OneWire
	// setup for putch_1
	UART_TX_PORT &= ~(1<<UART_TX1_BIT);		// clear output to 0, OneWire
	UART_TX_DDR &= ~(1<<UART_TX1_BIT);		// set to input mode!, OneWire
 #endif
#endif
	// look for status bits, which has the bootloader moved
	// from MCUSR to GPIOR0
#ifndef GPIOR0
 #define GPIOR0 OCR2      /* use OCR2 , if GPIOR0 is unknown */
#endif
        uart_newline();
        if (GPIOR0 & (1<<PORF)) uart_mem_string(PowerOn);
        if (GPIOR0 & (1<<EXTRF)) uart_mem_string(External);
        if (GPIOR0 & (1<<BORF)) uart_mem_string(BrownOut);
        if (GPIOR0 & (1<<WDRF)) uart_mem_string(WatchDog);
	uart_mem_string(Interrupt);
        uart_newline();
	// further application program can use the GPIOR0 for other purpose

//***************************************************
// output of Calibration byte
#if defined(OSCCAL1) && !defined(OSCCAL)
 #define OSCCAL OSCCAL1
#endif
#ifdef OSCCAL
        uart_mem_string(OscCal);
        hex_putch( OSCCAL / 16);
        hex_putch( OSCCAL & 0x0f);
        putch(' ');
        putch('(');
	DisplayValue((OSCCAL & MAX_OSCCAL),0,')',3);
        uart_newline();
#endif

#if SOFT_UART == 0
        uart_mem_string(HW_UART);
        hex_putch( BAUD_DIV/4096);
	hex_putch( (BAUD_DIV & 0xfff) / 256);
	hex_putch( (BAUD_DIV & 0xff) / 16);
	hex_putch( BAUD_DIV & 0xf);
        putch(' ');
        putch('(');
	DisplayValue((BAUD_DIV,0,')',6);
#else
	uart_mem_string(SW_UART);
#endif
        uart_newline();

#if defined(TST_TCCR_B)
	uart_string("Test Frequency Output at Pin ");
        uart_string(TST_COUNTER_PIN);
	putch(' ');
	DisplayValue((F_CPU*100)/512,-2,'H',6);
	putch('z');
        uart_newline();
#endif
	
        uart_newline();
#if SOFT_UART == 0
        while (1)
#endif
        {
	  uart_mem_string(Hello1);
        uart_newline();
	  uart_ee_string(Hello2);
        uart_newline();
	  uart_string("Hello World with string!");
        uart_newline();
        uart_newline();
        } 
#if	SOFT_UART > 1
	// output 'U' to TX0 and 'W' to TX1
        while (1)
        {
	putch('U');
	wait1ms();
        putch_1('W');
	wait1ms();
        } 
#endif
}
