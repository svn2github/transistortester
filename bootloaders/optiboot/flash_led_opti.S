; file flash_led_opti can be insorted to optiboot at the requested location

#if (LED_START_FLASHES) != 0
 ; Flash the LED is requested
 #if (LED_START_FLASHES > 1) || (LED_START_FLASHES < -1)
  ; Flash the LED is requested more than once, loop is required
	ldi	r21, LED_START_FLASHES
fl_lop:
 #endif
	ASBI	LED_PORT, LEDbit	; set LED-Pin high, LED on
	rcall	wait_T1ov
  #if Check_RX != 0		/* Check for RX Start bit is detected */
   #if BAUD_RATE < 100
	brcs	RX_was_high	; break loop, RX Start Bit detected, skip low wait
   #else
	brcs	fl_lop_end		; break loop if RX Start bit detected
   #endif
  #endif
	ACBI	LED_PORT, LEDbit	; set LED-Pin low, LED off
	rcall	wait_T1ov
 #if (LED_START_FLASHES > 1) || (LED_START_FLASHES < -1)
  #if Check_RX != 0		/* Check for RX Start bit is detected */
   #if BAUD_RATE < 100
	brcs	RX_was_high	; break loop, RX Start Bit detected, skip low wait
   #else
	brcs	fl_lop_end		; break loop if RX Start bit detected
   #endif
  #endif
  #if LED_START_FLASHES < 0
	inc	r21		; while (++count)
  #else 
	subi	r21, 1
  #endif
	brne	fl_lop		; while (--count)
 #endif
fl_lop_end:
#endif	/* LED_START_FLASHES != 0 */

