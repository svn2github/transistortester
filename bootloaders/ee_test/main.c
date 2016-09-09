	#include <avr/io.h>
	#include <avr/sleep.h>
// #include <stdlib.h>
// #include <string.h>
	#include <avr/eeprom.h>
	#include <avr/pgmspace.h>
	#include <avr/wdt.h>
	#include <math.h>

	#define MAIN_C
	#include "wait1000ms.h"
	#include "uart_defs.h"


const unsigned char Hello1[] PROGMEM = "Hello World from Flash!";
const unsigned char External[] PROGMEM = "External ";
const unsigned char WatchDog[] PROGMEM = "Watch-dog ";
const unsigned char BrownOut[] PROGMEM = "Brown-Out ";
const unsigned char PowerOn[] PROGMEM = "PowerOn ";
const unsigned char Interrupt[] PROGMEM = "Interrupt";

const unsigned char Hello2[] EEMEM = "Hello World from EEprom!";

void putch(char data);

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
//
	//begin of Test program
int main(void) {
#if defined(UART_SRA) && (SOFT_UART == 0) 
 // setup the correct BAUD_RATE divider for Clock-frequency F_CPU
 #define BAUD_DIV ((F_CPU + (BAUD_RATE * 4L)) / (BAUD_RATE * 8L) - 1)
 #if BAUD_DIV > 255
  #undef BAUD_DIV
  #define BAUD_DIV ((F_CPU + (BAUD_RATE * 8L)) / (BAUD_RATE * 16L) - 1)
  #if BAUD_DIV > 250
   #error Unachievable baud rate (too slow) BAUD_RATE
  #endif // baud rate slow check
        UART_SRA = (0<<U2X0);
 #else
        UART_SRA = (1<<U2X0);
 #endif
        UART_SRB = (1<<RXEN0)|(1<<TXEN0);
 #if defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined (__AVR_ATmega32__)
        UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);	// config UART
 #else
        UART_SRC = (1<<UCSZ00)|(1<<UCSZ01);		// config UART
 #endif
	UART_SRL = BAUD_DIV;		// set divider for UART

#else
	// prepare serial output, software solution
	UART_TX_PORT |= (1<<UART_TX_BIT);		// set output to 1
	UART_TX_DDR |= (1<<UART_TX_BIT);		// enable output
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
        while (1) {
	  uart_mem_string(Hello1);
        uart_newline();
	  uart_ee_string(Hello2);
        uart_newline();
	  uart_string("Hello World with string!");
        uart_newline();
        } 
}
