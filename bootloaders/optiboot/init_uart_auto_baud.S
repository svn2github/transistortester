 ; init_uart_auto_baud is part of optiboot 
 ;
 ; This part of assembler code tries to detect the
 ; STK_GET_SYNC (0x30 = 0b00110000) at the RX PIN,
 ; which should be the first character received


#ifdef TCNT1H
  ; use the 16-Bit counter to measure Baud time
  ; prepare the counter 1
	AOUT	TCCR1B, r1		; Stop counter 1 with /8 scaler
	ldi	r24, -1
	AOUT	TCNT1H, r24		; set initial counter to -1
	AOUT	TCNT1L, r24
	ldi	r24, (1<<U2X0)		; UART double speed mode
	AOUT	UART_SRA, r24
   ; prepare the UART
  #if defined(UART_SRC) && defined(UART_SEL)
	; version for m8, m16, m32 for example (with double function UCSRC)
	ldi	r23, (1<<UART_SEL)|(1<<UCSZ01)|(1<<UCSZ00)	;config UART
	AOUT	UART_SRC, r23
  #else
    /* no ATmega8_16_32 */
   #ifndef __AVR_ATmega163__
	ldi	r23, (1<<UCSZ00)|(1<<UCSZ01)	;0x06
	AOUT	UART_SRC, r23
   #endif
  #endif	/* defined(UCSRC) && defined(URSEL) */

 #if FLASHEND < 0x10000
wt_rx0s:
	ASBIC	UART_RX_PIN, UART_RX_BIT	; Look if RX is still high
	rjmp	wt_rx0s
	; begin of start bit is found
	ldi	r24, (1<<CS11)			; start command for counter with /8 scaler
wt_rx1s:
	ASBIS	UART_RX_PIN, UART_RX_BIT	; Look if RX is still low
	rjmp	wt_rx1s
	; begin of first "1" data bit is found after S0000, if it was a STK_GET_SYNC, 0x30
	AOUT	TCCR1B, r24		; Start counter 1 with /8 scaler
wt_rx0bs:
	ASBIC	UART_RX_PIN, UART_RX_BIT	; Look if RX is still high
	rjmp	wt_rx0bs
	AIN	r24, TCNT1L			; read counter after second '1' bit is finished
	AIN	r25, TCNT1H
	; because we have measured the time of two bits,
	; we must divide by 2 and subtract 1 to get the final UBRR
	; ((two_bit_time + 1) / 2) - 1  is equal to
	; (two_bit_time - 1) / 2 , the -1 is done by preset of counter! 
	lsr	r25
	ror	r24		; rotate through carry

 ; Transmission of byte is not finished, we must wait for last two "0" Bits
wt_rx1bs:
	ASBIS	UART_RX_PIN, UART_RX_BIT	; Look if RX is still low
	rjmp	wt_rx1bs
	; now we can start the UART
  #if defined(UCSRC) && defined(URSEL)
	; version for m8, m16, m32 for example (with double function UCSRC)
  	; This processor family has no double register for the 12-bit scaler
	AOUT	UART_SRRL, r25
	AOUT	UCSRC, r24		; without (1<<URSEL) we write the upper BAUD_DIV
  #else
    /* no ATmega8_16_32 */
	AOUT	UART_SRRL, r24
	AOUT	UART_SRRH, r25
  #endif	/* defined(UCSRC) && defined(URSEL) */
 #else
  ;------------------------------------------------------------------------------------
  ; the bootpage should have at least 1024 Bytes, we have enough space for exact analye
	ldi	r24, (1<<CS11)			; start command for counter with /8 scaler
wt_rx0l:
	ASBIC	UART_RX_PIN, UART_RX_BIT	; Look if RX is still high
	rjmp	wt_rx0l
	; start bit is found
	AOUT	TCCR1B, r24		; Start counter 1 with /8 scaler, begin measurement
wt_rx1l:
	ASBIS	UART_RX_PIN, UART_RX_BIT	; Look if RX is still low
	rjmp	wt_rx1l
	; now we should have start-bit and 4 data bits 0
	AIN	r10, TCNT1L			; read counter after 'S0000'
	AIN	r11, TCNT1H
wt_rx0bl:
	ASBIC	UART_RX_PIN, UART_RX_BIT	; Look if RX is still high
	rjmp	wt_rx0bl
	; now we should have start-bit + 4 data 0 bits + 2 date 1 bits
	AIN	r12, TCNT1L			; read counter after 'S000011'
	AIN	r13, TCNT1H
 ; Transmission of byte is not finished, we must wait for last two "0" Bits
wt_rx1bs:
	ASBIS	UART_RX_PIN, UART_RX_BIT	; Look if RX is still low
	rjmp	wt_rx1bs
	AIN	r26, TCNT1L		; read counter after 'S00001100', full 8 Bit transmission with Start bit
	AIN	r27, TCNT1H
	sbiw	r26, 2
	sub	r26, r10		; build time diff for total of 4 bits 1100
	sbc	r27, r11
	sub	r12, r10		; build time diff for the two '1' bits
	sbc	r13, r11
 ; test for nearly the same time r14:15 and r12:13
	lsr	r27			; r26 = (11 time + 00 time) / 2
	ror	r26
	movw	r24, r12
	sub	r24, r26		; build difference to 11 time
	sbc	r25, r27
	brpl	isposdif
	rjmp	wt_rx0l
isposdif:
	subi	r24, 2		; should set carry, if r24:r25 was 0 or 1 before
	sbc	r25, r1		
carry_chk:
	brcc	wt_rx0l		; wait for next data word.
 ; we can spend more space to build a mean value of r12:r13 and r14:r15
 ; now we check, that the time for Start-Bit and four data bits is higher than the sum of the last 4 bits.
	sub	r10, r26
	sbc	r11, r27
	sub	r10, r12
	sbc	r11, r13
	brmi	wt_rx0l		; can not be the 0b000001100 data
	; because we have measured the time of two bits,
	; we must divide by 2 to get the final UBRR
	; ((two_bit_time + 1) / 2) - 1  is equal to
	; (two_bit_time - 1) / 2 
	lsr	r27		; /2
	ror	r26		; rotate through carry

	; now we can start the UART
  #if defined(UCSRC) && defined(URSEL)
	; version for m8, m16, m32 for example (with double function UCSRC)
  	; This processor family has no double register for the 12-bit scaler
	AOUT	UART_SRRL, r26
	AOUT	UCSRC, r27		; without (1<<URSEL) we write the upper BAUD_DIV
  #else
    /* no ATmega8_16_32 */
	AOUT	UART_SRRL, r26
	AOUT	UART_SRRH, r27
  #endif	/* defined(UCSRC) && defined(URSEL) */
 #endif

 #ifdef UART_ONE_WIRE
	ldi	r24, (1<<RXEN0)		;0x10	
 #else
	ldi	r24, (1<<RXEN0)|(1<<TXEN0)	;0x18	
 #endif
	AOUT	UART_SRB, r24
 #if TEST_OUTPUT == 1
	rjmp	test_out	; output 'U'=0b01010101 for speed meaasuring
 #else
	rjmp	ver_put		;  rcall verifySpace; rjmp put_ok
 #endif
#else 
   #error "AutoBaud Function is only possible with 16-Bit counter 1!"
#endif


