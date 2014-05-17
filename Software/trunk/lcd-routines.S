#ifndef __ASSEMBLER__
 #define __ASSEMBLER__
#endif
#include <avr/io.h>
#include <avr/common.h>
#include <avr/eeprom.h>
#include "config.h"
#include "part_defs.h"
#include "lcd_defines.h"

#define RCALL rcall
 .section .text

  .global lcd_data
  .func lcd_data

 .global lcd_testpin
 .global lcd_space

;// send space character to LCD
;void lcd_space(void) {
lcd_space:
 	ldi	r24, 0xef	;0x20 - 0x31
;                           + '1' = ' '

;// sends numeric character (Pin Number) to the LCD 
;// from binary 0 we send ASCII 1 ....
;void lcd_testpin(unsigned char temp) {
lcd_testpin:
 	subi	r24, -'1'	; 0xCF
;       run to lcd_data ....

;// sends data byte to the LCD 
;void lcd_data(unsigned char temp1) {
lcd_data:
 	push	r17
 	mov	r17, r24
 	ldi	r24, 0x01	; 1
#ifdef WITH_UART
 	mov	r22, r17
 	RCALL	_lcd_hw_write		; lcd_write_data(temp1);	// set RS to 1
 	RCALL	wait50us
; switch(temp1) {
 	cpi	r17, 0x08	; 8
 	brcc	ad246 
 	cpi	r17, LCD_CHAR_RESIS2	; 6
 	brcc	ad268 
 	cpi	r17, LCD_CHAR_DIODE2	; 2
 	breq	ad254 
 	cpi	r17, LCD_CHAR_CAP	; 3
 	breq	ad25e
 	cpi	r17, LCD_CHAR_DIODE1	; 1
 	brne	ad280 
 	rjmp	ad250 
ad246:
 	cpi	r17, LCD_CHAR_U	; 228
 	breq	ad26c 
 	cpi	r17, LCD_CHAR_OMEGA	; 244
 	brne	ad280
 	rjmp	ad270 
ad250:
;   case LCD_CHAR_DIODE1:
 	ldi	r24, '>'	; 0x3E
 	rjmp	ad260 		; uart_putc('>'); uart_putc('|');
ad254:
;   case LCD_CHAR_DIODE2:
 	ldi	r24, '|'	; 0x7C
 	RCALL	uart_putc	; uart_putc('|');
 	ldi	r24, '<'	; 0x3C	
 	rjmp	d_putc_ret		; uart_putc('<');
ad25e:
;   case LCD_CHAR_CAP:
 	ldi	r24, '|'	; 0x7C  uart_putc('|');
ad260:
 	RCALL	uart_putc
 	ldi	r24, '|'	; 0x7C	
 	rjmp	d_putc_ret		; uart_putc('|');
ad268:
;   case LCD_CHAR_RESIS1:
;   case LCD_CHAR_RESIS2:
 	ldi	r24, 'R'	; 0x52
 	rjmp	d_putc_ret		; uart_putc('R');
;//    case LCD_CHAR_DEGREE:	// degree sign
;//    	uart_putc(0xf8);	// codepage 437 or 850 has degree
ad26c:
;    case LCD_CHAR_U:		//µ
 	ldi	r24, 'u'	; 0x75	
 	rjmp	d_putc_ret		; uart_putc('u');	// better use the ASCII u , uart_putc(0xe6);	// codepage 437 or 850 has my
ad270:
;    case LCD_CHAR_OMEGA:	//Omega
//	uart_putc(0xea);	// only codepage 437 has Omega
 	ldi	r24, 'O'	; 0x4F
 	RCALL	uart_putc	; uart_putc('O');
 	ldi	r24, 'h'	; 0x68
 	RCALL	uart_putc	; uart_putc('h');
 	ldi	r24, 'm'	; 0x6D
 	rjmp	d_putc_ret		; uart_putc('m');

;    default:
ad280:
 	mov	r24, r17	; uart_putc(temp1);
d_putc_ret:
 	RCALL	uart_putc
 	pop	r17
 	ret
#else
        rjmp	to_hw_write		; lcd_write_data(temp1); return;
#endif
 .endfunc



#ifdef WITH_UART
 .global uart_newline
 .func uart_newline
;void uart_newline(void) {
uart_newline:
 	ldi	r24, 0x0D	; 13
 	RCALL	uart_putc	; uart_putc('\r');
 	ldi	r24, 0x0A	; 10
 	RCALL	uart_putc	; uart_putc('\n');
 	ret
 .endfunc
#endif
 
 
 .global lcd_command
 .func lcd_command

;// sends a command to the LCD
;void lcd_command(unsigned char temp1) {
lcd_command:
 	push	r17
 	mov	r17, r24
 	ldi	r24, 0x00	; 0
to_hw_write:
 	mov	r22, r17
 	RCALL	_lcd_hw_write	; lcd_write_cmd(temp1);		// set RS to 0
 	RCALL	wait50us
#ifdef WITH_UART
 	cpi	r17, 0x80	; 128
 	breq	ad2c0		; if((temp1 == 0x80)  ||
 	cpi	r17, 0xC0	; 192
 	brne	c_putc_ret	; if(                 || (temp1 == 0xC0)) 
ad2c0:
 	RCALL	uart_newline	; uart_newline();
#endif
c_putc_ret:
 	pop	r17
 	ret
 .endfunc

 
 .global lcd_clear
 .func lcd_clear
;// send the command to clear the display 
 
; void lcd_clear(void) {
lcd_clear:
 	ldi	r24, 0x01	; 1
 	RCALL	lcd_command	; lcd_command(CLEAR_DISPLAY);
#ifdef INHIBIT_SLEEP_MODE
	RCALL	wait10ms		; wait10ms()
#else
 	ldi	r24, 2		; 2
 	RCALL	sleep_5ms	; wait_about10ms();
#endif
#ifdef WITH_UART
 	RCALL	uart_newline	; uart_newline();
#endif
 	ldi	r24, 0x80	; 128
 	RCALL	lcd_command	; lcd_line1();	// set cursor to Line1 Column 1, (only for OLED-Display)
 	ret
 .endfunc

 .global lcd_init
 .func lcd_init
 .extern wait1ms
#ifdef INHIBIT_SLEEP_MODE
 .extern wait30ms
 .extern wait10ms
 .extern wait5ms
#else
 .extern sleep_5ms
#endif
 
;// Initialise: 
;// Must be called first .
 
;void lcd_init(void) {
lcd_init:
#ifdef INHIBIT_SLEEP_MODE
	RCALL	wait30ms	; wait30ms();
#else
 	ldi	r24, 6		; 0x06
 	RCALL	sleep_5ms	; wait_about30ms();
#endif
;  // to initialise, send 3 times to be shure to be in 8 Bit mode
 	ldi	r24, 0x80	; 128
 	ldi	r22, 0x30	; 48
 	RCALL	_lcd_hw_write	; lcd_write_init(1);
#ifdef INHIBIT_SLEEP_MODE
	RCALL	wait5ms		; wait5ms();
#else
 	ldi	r24, 1		; 0x01
 	RCALL	sleep_5ms	; wait_about5ms();
#endif
   
 	ldi	r24, 0x80	; 128
 	ldi	r22, 0x30	; 48
 	RCALL	_lcd_hw_write	; lcd_write_init(1);
 	RCALL	wait1ms		; wait1ms();

 	ldi	r24, 0x80	; 128
 	ldi	r22, 0x30	; 48
 	RCALL	_lcd_hw_write	; lcd_write_init(1);
 	RCALL	wait1ms		; wait1ms();

 	ldi	r24, 0x80	; 128
 	ldi	r22, 0x20	; 32
 	RCALL	_lcd_hw_write	; lcd_write_init(0);	// switch to 4 Bit mode
#ifdef INHIBIT_SLEEP_MODE
	RCALL	wait10ms		; wait10ms();
#else
 	ldi	r24, 2		; 0x02	
 	RCALL	sleep_5ms	; wait_about10ms();
#endif
#ifdef LCD_DOGM
 	ldi	r24, (CMD_SetIFOptions | 0x09) ; 0x28  4Bit / 2 rows / 5x7 / Intr. table 1
 	RCALL	lcd_command	; lcd_command(CMD_SetIFOptions | 0x08);	// 4Bit / 2 rows / 5x7
 	ldi	r24, (CMD1_SetBias | 0x0c)	; // 1/4 bias     (5V)
 	RCALL	lcd_command	; lcd_command(CMD1_SetBias | 0x0c);		// 1/4 bias     (5V)
 	ldi	r24, (CMD1_PowerControl | 0x02)	; // booster off / set contrast C5:C4 = 2
 	RCALL	lcd_command	; lcd_command(CMD1_PowerControl | 0x02);	// booster off / set contrast C5:C4 = 2
 	ldi	r24, (CMD1_FollowerControl | 0x09) ; // Follower on / Rab2:0 = 1
 	RCALL	lcd_command	; lcd_command(CMD1_FollowerControl | 0x09);	// Follower on / Rab2:0 = 1
 	ldi	r24, (CMD1_SetContrast | 0x04)	; // set contrast C3:0 = 4
 	RCALL	lcd_command	; lcd_command(CMD1_SetContrast | 0x04);	// set contrast C3:0 = 4
#endif
 	ldi	r24, (CMD_SetIFOptions | 0x08) ; 0x28  4Bit / 2 rows / 5x7
 	RCALL	lcd_command	; lcd_command(CMD_SetIFOptions | 0x08);	// 4Bit / 2 rows / 5x7

 	ldi	r24, (CMD_SetDisplayAndCursor | 0x04) ; 0xc0 // Display on / Cursor off / no Blinking
 	RCALL	lcd_command	; lcd_command(CMD_SetDisplayAndCursor | 0x04); // Display on / Cursor off / no Blinking

 	ldi	r24, (CMD_SetEntryMode | 0x02)	; 0x06 // increment / no Scroll    
 	RCALL	lcd_command	; lcd_command(CMD_SetEntryMode | 0x02);	// increment / no Scroll    
 	RCALL	lcd_clear	; lcd_clear();
 	ret
 .endfunc

 
 .global lcd_string
 .func lcd_string
 .extern lcd_data
 
;// writes a string to the LCD 
 
;void lcd_string(char *data) {
lcd_string:
 	push	r14
 	push	r15
 	push	r28
 	push	r29
 	mov	r14, r24
 	movw	r28, r14
 	movw	r14, r28
 	mov	r15, r25
 	movw	r28, r14
 	rjmp	ad352		;  while(*data) 
ad34e:
 	RCALL	lcd_data	; lcd_data(*data);
 
ad352:
 	ld	r24, Y+
 	and	r24, r24
 	brne	ad34e		; while(*data) 
 	pop	r29
 	pop	r28
 	pop	r15
 	pop	r14
 	ret
 .endfunc


#ifdef use_lcd_pgm
 .global lcd_pgm_string
 .func lcd_pgm_string
 .extern lcd_data

;//Load string from PGM  and send to LCD 
;void lcd_pgm_string(const unsigned char *data) {
lcd_pgm_string:
 	push	r28
 	push	r29
 	movw	r28, r24
;   while(1) {
str_loop:
 	movw	r30, r28
 	lpm	r24, Z+		; cc = pgm_read_byte(data);
 	and	r24, r24
 	breq	str_end 	; if((cc==0) || 
 	cpi	r24, 0x80	; 128
 	breq	str_end		; if(        || (cc==128))  
 	RCALL	lcd_data	; lcd_data(cc);
 	adiw	r28, 0x01	; data++;
 	rjmp	str_loop 

str_end:
 	pop	r29
 	pop	r28
 	ret
 .endfunc
#endif

#ifdef USE_EEPROM
 .global lcd_fix_string
 .func lcd_fix_string
 .extern eeprom_read_byte

;//Load string from PGM or EEprom and send to LCD 
; void lcd_fix_string(const unsigned char *data) 
lcd_fix_string:
 	push	r28
 	push	r29
 	movw	r28, r24
;    while(1) 
fix_loop:
#ifdef USE_EEPROM
 	movw	r24, r28
 	ACALL	eeprom_read_byte; cc = MEM_read_byte(data);
#else
	movw	r30,r28
	lpm	r24,Z+
#endif
 	and	r24, r24
 	breq	fix_end		; if((cc==0) || 
 	cpi	r24, 0x80	; 128
 	breq	fix_end		; if(        || (cc==128)) 
 	RCALL	lcd_data	; lcd_data(cc);
 	adiw	r28, 0x01	; data++;
 	rjmp	fix_loop 
fix_end:
 	pop	r29
 	pop	r28
 	ret
 .endfunc
#endif

 .global lcd_fix_customchar
 .func lcd_fix_customchar
 .extern lcd_data
 .extern eeprom_read_byte

;// load custom character from PGM or EEprom and send to LCD
;void lcd_fix_customchar(const unsigned char *chardata) 
lcd_fix_customchar:
 	push	r16
 	push	r17
 	push	r28
 	push	r29
 	movw	r16, r24
 	ldi	r28, 0x00	; 0
 	ldi	r29, 0x00	; 0
;    for(uint8_t i=0;i<8;i++) {
ad3b2:
#ifdef USE_EEPROM
 	movw	r24, r16
 	add	r24, r28
 	adc	r25, r29
 	ACALL	eeprom_read_byte	; MEM_read_byte(chardata);
#else
	movw	r30,r16
	add	r30, r28
	adc	r31, r29
	lpm	r24,Z+			; MEM_read_byte(chardata);
#endif
 	RCALL	lcd_data		; lcd_data(MEM_read_byte(chardata));
 	adiw	r28, 0x01	; 1

 	cpi	r28, 0x08	; 8
 	cpc	r29, r1
 	brne	ad3b2		; for(uint8_t i=0;i<8;i++) 

 	pop	r29
 	pop	r28
 	pop	r17
 	pop	r16
 	ret
 .endfunc

#ifdef LCD_CLEAR

 .global lcd_clear_line
 .func lcd_clear_line
 .extern lcd_space

; // writes 20 spaces to LCD-Display, Cursor must be positioned to first column
; void lcd_clear_line(void) {
lcd_clear_line:
 	push	r17
 	ldi	r17, 0x14	; 20
; for (ll=0;ll<20;ll++) {
clr_lop:
 	RCALL	lcd_space	; lcd_space();
 	subi	r17, 0x01	; 1

 	brne	clr_lop		; for (ll=0;ll<20;ll++) 

 	pop	r17
 	ret
 .endfunc
#endif

 .global lcd_line1
lcd_line1:
 .func lcd_line1
 	ldi	r24, 0x80	; 128
 	RCALL	lcd_command	; lcd_line1();	// set cursor to Line1
 	ret
 .endfunc

 .global lcd_line2
 .func lcd_line2
lcd_line2:
 	ldi	r24, 0xc0	; 192
 	RCALL	lcd_command	; lcd_line2();	// set cursor to Line2
 	ret
 .endfunc

 .global lcd_line3
 .func lcd_line3
lcd_line3:
 	ldi	r24, 0x94	; 148
 	RCALL	lcd_command	; lcd_line3();	// set cursor to Line3
 	ret
 .endfunc

 .global lcd_line4
 .func lcd_line4
lcd_line4:
 	ldi	r24, 0xd4	; 212
 	RCALL	lcd_command	; lcd_line4();	// set cursor to Line4
 	ret
 .endfunc

 .global lcd_powersave
 .func lcd_powersave
lcd_powersave:
 	ret
 .endfunc

