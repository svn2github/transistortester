 ; init_uart_auto_baud is part of optiboot 
 ;
 ; This part of assembler code tries to detect the
 ; STK_GET_SYNC (0x30 = 0b00110000) at the RX PIN,
 ; which should be the first character received

#if defined(UART_SRC) && defined(UART_SEL)
 ; version for m8, m16, m32 for example,
 ; which have double function for register UART_SRC (UCSRC).
 ; This processor family has no double register for the 12-bit scaler.
 ; Without the bit UART_SEL (URSEL) set in the UART_SRC (UCSRC) register
 ; we can write the upper BAUD_DIV to register UART_SRC
 #define UART_SRRH UART_SRC
#endif

#ifdef TCNT1H
 #define CNT16_CNTH  TCNT1H
 #define CNT16_CNTL  TCNT1L
 #define CNT16_CCRB  TCCR1B
 #define CNT16_OCREGL OCR1AL
 #define CNT16_OCREGH OCR1AH
 #define OCFLAG OCF1A

#elif defined(TCNT0H)
 #define CNT16_CNTH  TCNT0H
 #define CNT16_CNTL  TCNT0L
 #define CNT16_CCRB  TCCR0B
 #define CNT16_OCREGL OCR0A
 #define CNT16_OCREGH OCR0B
 #define OCFLAG OCF0A
	ldi	r24, (1<<TCW0)		; switch counter 0 to 16-Bit (tiny861)
	AOUT	TCCR0A, r24

#else 
   #error "AutoBaud Function is only possible with 16-Bit counter 1!"
#endif

#if !defined(TIFR1) && defined(TIFR)
 #define TIFR1 TIFR
#endif

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
#endif	/* defined(UART_SRC) && defined(UART_SEL) */

next_try:
  ; use the 16-Bit counter to measure Baud time
  ; prepare the counter 1
	AOUT	CNT16_CCRB, r1		; Stop counter 1 with /8 scaler
	ldi	r24, -1
	AOUT	CNT16_CNTH, r24		; set initial counter to -1
	AOUT	CNT16_CNTL, r24
	wdr				; watchdog timer reset

#if BAUD_RATE < 60
  ; simple detection of the baud-rate
 #if LED_START_FLASHES >= 0
wt_rx0low:
	ASBIS	UART_RX_PIN, UART_RX_BIT	; Look if RX is still low
	rjmp	wt_rx0low			; wait for at least one 1 read
 #endif
; wait, if the UART-RX-Bit is low
wt_rx0s:
	ASBIC	UART_RX_PIN, UART_RX_BIT	; Look if RX is still high
	rjmp	wt_rx0s
	; Probably start bit is found, at least a 1 to 0 transition.
	; STK500 protocol send a '3'=0x30 followed by ' '=0x20.
	; P is a pause condition (STOP bit = 1) and S is a START bit (0), 
	; the 0 and 1 represent the expected data bits.
	; the full bit sequence send is PS00001100PS00000100PPP
	;                                ^      ^  ^      ^
	;                                1      2  3      4
	; Every of the marked postion is a 1 to 0 transition!
	; If we begin now with the time measurement, we get the following result
	; for the next two bit changes:
	; Position 1:  5B, 7B (,9B)
	; Position 2:  2B, 3B+d (,9B+d)
	; Position 3:  6B, 7B (,9B)
	; Position 4:  2B, 3B+Delay
	; B is the unknown Baud time and d can be a short delay of the next Start-bit.
	; The Delay is a long time delay to the next transmission retry,
	; if the sender get no answer.
	; If we begin the time measurement at the next transition, we
	; get only the following time results:
	; Position 1: 2B (,4B)
	; Position 2: 1B+d (,6B+d)
	; Position 3: 1B  (,3B)
	; Position 4: 1B+Delay
	; I see no easy way to prevent the wrong baud-rate detection for each
	; of the possible start conditions. So we check here only a upper time limit
	; for the position 4 for saving flash memory (BAUD_RATE > 49).
	; A full plausibility check is done for a Boot-Page size of more than 512 Byte.

	ldi	r24, (1<<CS11)			; start command for counter with /8 scaler
wt_rx1s:
	ASBIS	UART_RX_PIN, UART_RX_BIT	; Look if RX is still low
	rjmp	wt_rx1s
	; begin of first "1" data bit is found after S0000, if it was a STK_GET_SYNC, 0x30
	AOUT	CNT16_CCRB, r24		; Start counter 1 with /8 scaler
 #if BAUD_RATE > 49
	; the optional time-limit check is only done, if the BAUD_RATE is set > 49 
	ldi	r24, hi8(4864)		; Set upper limit
	AOUT	CNT16_OCREGH, r24
	AOUT	CNT16_OCREGL, r1		; lower bits to 0
  #if TIFR1 < (0x20 + __SFR_OFFSET)
	sbi	_SFR_IO_ADDR(TIFR1), OCFLAG	; Clear Compare A Flag
  #else
	ldi	r26, (1<<OCFLAG)
	AOUT	TIFR1, r26		; clear Compare A Flag
  #endif
 #endif	/* BAUD_RATE > 49 */
wt_rx0bs:
 #if BAUD_RATE > 49
	ASBIC	TIFR1, OCFLAG	; Look if time limit is reached, Compare A Flag
	rjmp	next_try		; upper limit for 2x Baud-time is reached
 #endif
	ASBIC	UART_RX_PIN, UART_RX_BIT	; Look if RX is still high
	rjmp	wt_rx0bs
	AIN	r24, CNT16_CNTL			; read counter after second '1' bit is finished
	AIN	r25, CNT16_CNTH
	; because we have measured the time of two bits,
	; we must divide by 2 and subtract 1 to get the final UBRR
	; ((two_bit_time + 1) / 2) - 1  is equal to
	; (two_bit_time - 1) / 2 , the -1 is done by preset of counter! 
	; The -1 is done with counter preset to -1
	lsr	r25
	ror	r24		; rotate through carry

 ; Transmission of byte is not finished, we must wait for last two "0" Bits
wt_rx1bs:
	ASBIS	UART_RX_PIN, UART_RX_BIT	; Look if RX is still low
	rjmp	wt_rx1bs
	; now we can start the UART
	AOUT	UART_SRRL, r24
	AOUT	UART_SRRH, r25
 #undef DELAY_NEXT_REQUEST
#else
  ;------------------------------------------------------------------------------------
  ; you assume enough space for exact analye for BAUD_RATE >= 60
	ldi	r24, (1<<CS11)			; start command for counter with /8 scaler
 #if LED_START_FLASHES >= 0
wt_rx1low:
	ASBIS	UART_RX_PIN, UART_RX_BIT	; Look if RX is still low
	rjmp	wt_rx1low			; wait for at least one 1 read
 #endif
wt_rx0l:
	ASBIC	UART_RX_PIN, UART_RX_BIT	; Look if RX is still high
	rjmp	wt_rx0l
	; Probably start bit is found, at least a 1 to 0 transition.
	; STK500 protocol send a '3'=0x30 followed by ' '=0x20.
	; P is a pause condition (STOP bit = 1) and S is a START bit (0). 
	; the full bit sequence send is PS00001100PS00000100PPP
	;                                ^      ^  ^      ^
	;                                1      2  3      4
	; Every of the marked postion is a 1 to 0 transition!
	; We start the counter to measure the time of the next 3 bit changes.
	; This result to 5B, 7B and 9B time measurements for the marked "1" transition,
	; where B is the baud time.
	; For the "2" transition you get 2B+d, 3B+d and 9B+d for the time measurement,
	; where d is a possible delay of the next start bit.
	; For the "3" transition you get 6B, 7B and 9B as time measurement result.
	; For the "4" transition you get 2B and a unassigned result for the following
	; measurements, because the Transmitter wait for a reply.
	; The best way to solve this problem is to monitor the counter time for
	; exceed of a 4*(2B) limit.

	AOUT	CNT16_CCRB, r24		; Start counter 1 with /8 scaler, begin measurement
wt_rx1l:
	ASBIS	UART_RX_PIN, UART_RX_BIT	; Look if RX is still low
	rjmp	wt_rx1l
	; now we should have start-bit and 4 data bits 0
	AIN	r10, CNT16_CNTL			; read counter after 'S0000'
	AIN	r11, CNT16_CNTH
	movw	r26, r10
	add	r26, r26		; * 2
	adc	r27, r27
	add	r26, r26		; * 2
	adc	r27, r27
	AOUT	CNT16_OCREGH, r27
	AOUT	CNT16_OCREGL, r26
 #if TIFR1 < (0x20 + __SFR_OFFSET)
	sbi	_SFR_IO_ADDR(TIFR1), OCFLAG
 #else
	ldi	r26, (1<<OCFLAG)
	AOUT	TIFR1, r26
 #endif

wt_rx0bl:
	ASBIC	TIFR1, OCFLAG	; Look if time limit is reached
	rjmp	next_try		; 4x first time must be greater than actual time
	ASBIC	UART_RX_PIN, UART_RX_BIT	; Look if RX is still high
	rjmp	wt_rx0bl
	; now we should have start-bit + 4 data 0 bits + 2 date 1 bits
	AIN	r12, CNT16_CNTL			; read counter after 'S000011'
	AIN	r13, CNT16_CNTH
 ; Transmission of byte is not finished, we must wait for last two "0" Bits
wt_rx1bs:
	ASBIS	UART_RX_PIN, UART_RX_BIT	; Look if RX is still low
	rjmp	wt_rx1bs
	AIN	r26, CNT16_CNTL		; read counter after 'S00001100', full 8 Bit transmission with Start bit
	AIN	r27, CNT16_CNTH

	movw	r24, r26
	sub	r24, r10		; S00001100-S0000 = 1100 time
	sbc	r25, r11
	cp	r24, r10		; S0000 > 1100 ?
	cpc	r24, r11
	brcs	delay_next_try		; 5x must be greater than 4x Baud time
	
	sub	r26, r12		; build time diff  S00001100 - S000011 = 00
	sbc	r27, r13

 #if BAUD_RATE >= 80
	; we use a four bit time (1100) for baud-rate calculation.
	movw	r28, r12		; S000011
	adiw	r28, 4			; 
	sub	r28, r10		; build time diff  S000011 - S0000 = 11
	sbc	r29, r11
	cp	r26, r28		; 11 + d > 00 ?
	cpc	r27, r29
	brcc	next_try		; wait for next data word.
	; we have allready the sum of the 11 and 00 time in r24:25
	; because we have measured the time of four bits,
	; we must divide by 4 to get the final UBRR
	; ((four_bit_time + 2) / 4) - 1  is equal to
	; (four_bit_time - 2) / 4 
	sbiw	r24, 2		; subtract 2 from the four bit time
	lsr	r25		; /2
	ror	r24		; rotate through carry
	lsr	r25		; /2
	ror	r24		; rotate through carry
	; now we can start the UART
	AOUT	UART_SRRL, r24
	AOUT	UART_SRRH, r25

 #else		/* 60 <= BAUDRATE < 80 */
	; We have the time of the 00 bits in r26:r27
	; because we have measured the time of two bits,
	; we must divide by 2 to get the final UBRR
	; ((two_bit_time + 1) / 2) - 1  is equal to
	; (two_bit_time - 1) / 2 
	sbiw	r26, 1		; subtract 1 from the two bit time
	lsr	r27		; /2
	ror	r26		; rotate through carry

	; now we can start the UART
	AOUT	UART_SRRL, r26
	AOUT	UART_SRRH, r27
 #endif	/* BAUD_RATE  >= 80 */
 #define DELAY_NEXT_REQUEST
#endif		/* BAUD_RATE < 60 */

#ifdef UART_ONE_WIRE
	ldi	r24, (1<<RXEN0)		;0x10	
#else
	ldi	r24, (1<<RXEN0)|(1<<TXEN0)	;0x18	
#endif
	AOUT	UART_SRB, r24
#if TEST_OUTPUT == 1
	rjmp	test_out	; output 'U'= S10101010P for speed measuring
#else
	rjmp	ver_put		;  rcall verifySpace; rjmp put_ok
#endif

#ifdef DELAY_NEXT_REQUEST
delay_next_try:
	ASBIC	UART_RX_PIN, UART_RX_BIT	; Look if RX is still high
	rjmp	delay_next_try
	; RX=0 can be a data 0 bit or a start bit. We hope,that is is a data bit.
	rjmp	next_try			; wait for next stop bit
#endif 


