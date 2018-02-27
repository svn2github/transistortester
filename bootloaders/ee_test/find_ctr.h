/*
 * find_ctr.h
 * optiboot helper defining the default pin assignments for a 8-Bit counter
 * (OC0, OC0A or OC2, OC2A)
 * for the various chips that are supported. 
 *
 * by K.-H. Kuebbeler
 */


/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || \
    defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || \
    defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || \
    defined(__AVR_ATmega48__) || defined(__AVR_ATmega48P__) || \
    defined(__AVR_ATmega88__) || defined(__AVR_ATmega88P__) || \
    defined(__AVR_ATmega48__) || defined(__AVR_ATmega48P__)
  #define TST_COUNTER_PIN "PD6"
  #define CNT_ENABLE_DDR  DDRD
  #define CNT_ENABLE_PIN  DDD6
  #define TST_TCCR_A TCCR0A
  #define TST_TCCR_A_SET ((0<<COM0A1) | (1<<COM0A0))
  #define TST_TCCR_B TCCR0B
  #define TST_TCCR_B_SET (1<<CS00)
  #define MAX_OSCCAL 255
#endif		/* __AVR_ATmega168__  ... */

/*------------------------------------------------------------------------ */
#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega8A__)
  #define TST_COUNTER_PIN "PB3"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB3
  #define TST_TCCR_B TCCR2
  #define TST_TCCR_B_SET ((1<<COM20) | (1<<CS20))
  #define MAX_OSCCAL 255
#endif		/* __AVR_ATmega8__  ... */

/*------------------------------------------------------------------------ */
#if  defined(__AVR_ATmega8515__) 
  #define TST_COUNTER_PIN "PB0"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB0
  #define TST_TCCR_B TCCR0
  #define TST_TCCR_B_SET ((1<<COM00) | (1<<CS00))
  #define MAX_OSCCAL 255
#endif		/* __AVR_ATmega8515__  ... */

/*------------------------------------------------------------------------ */
#if  defined(__AVR_ATmega8535__)
  #define TST_COUNTER_PIN "PD7"
  #define CNT_ENABLE_DDR  DDRD
  #define CNT_ENABLE_PIN  DDD7
  #define TST_TCCR_B TCCR2
  #define TST_TCCR_B_SET ((1<<COM20) | (1<<CS20))
  #define MAX_OSCCAL 255
#endif		/* __AVR_ATmega8535__  ... */

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny24__) ||\
    defined(__AVR_ATtiny84A__) || defined(__AVR_ATtiny44A__) || defined(__AVR_ATtiny24__) 
  #define TST_COUNTER_PIN "PB2"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB2
  #define TST_TCCR_A TCCR0A
  #define TST_TCCR_A_SET ((0<<COM0A1) | (1<<COM0A0))
  #define TST_TCCR_B TCCR0B
  #define TST_TCCR_B_SET (1<<CS00)
  #define MAX_OSCCAL 255
#endif	/* __AVR_ATtiny44__ || __AVR_ATtiny84__ */

/*------------------------------------------------------------------------ */
/* support for attiny841 and attiny441 */
#if defined(__AVR_ATtiny841__) || defined(__AVR_ATtiny441__) 
  #define TST_COUNTER_PIN "PB2"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB2
  #define TST_TCCR_A TCCR0A
  #define TST_TCCR_A_SET ((0<<COM0A1) | (1<<COM0A0))
  #define TST_TCCR_B TCCR0B
  #define TST_TCCR_B_SET (1<<CS00)
  #define MAX_OSCCAL 255
#endif		/* __AVR_ATiny841__  .. */

/*------------------------------------------------------------------------ */

/* Support for ATtiny88 and ATtiny48 */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny88__) || defined(__AVR_ATtiny48__)
  #define TST_COUNTER_PIN "PB1"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB1
  #define TST_TCCR_A TCCR1A
  #define TST_TCCR_A_SET ((0<<COM1A1) | (1<<COM1A0))
  #define TST_TCCR_B TCCR1B
  // use mode 4 (CTC) with OCR1A = 0xff to simulate 8-Bit counter
  #define TST_TCCR_B_SET (0<<WGM13) | (1<<WGM12) | (1<<CS10)
  #define MAX_CNTR1 255
  #define MAX_OSCCAL 255
#endif	/* __AVR_ATtiny88__ || __AVR_ATtiny48__ */

/* Support for ATtiny87 and ATtiny167 */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
  #define TST_COUNTER_PIN "PA2"
  #define CNT_ENABLE_DDR  DDRA
  #define CNT_ENABLE_PIN  DDA2
  #define TST_TCCR_A TCCR0A
  #define TST_TCCR_A_SET ((0<<COM0A1) | (1<<COM0A0))
  #define TST_TCCR_B TCCR0B
  #define TST_TCCR_B_SET (1<<CS00)
  #define MAX_OSCCAL 255
#endif	/* __AVR_ATtiny87__ || __AVR_ATtiny167__ */


/* Support for ATtiny85 family*/
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny25__)
  #define TST_COUNTER_PIN "PB0"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB0
  #define TST_TCCR_A TCCR0A
  #define TST_TCCR_A_SET ((0<<COM0A1) | (1<<COM0A0))
  #define TST_TCCR_B TCCR0B
  #define TST_TCCR_B_SET (1<<CS00)
  #define MAX_OSCCAL 255
#endif	/* __AVR_ATtiny85__  */

/* Support for ATtiny 26x family*/
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny861__) || defined(__AVR_ATtiny461__) || defined(__AVR_ATtiny261__) || \
    defined(__AVR_ATtiny861A__) || defined(__AVR_ATtiny461A__) || defined(__AVR_ATtiny261A__) 
  #define TST_COUNTER_PIN "PB3"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB3
  #define TST_TCCR_A TCCR1A
  #define TST_TCCR_A_SET ((0<<COM1B1) | (1<<COM1B0))
  #define TST_TCCR_B TCCR1B
  #define TST_TCCR_B_SET (1<<CS10)
  #define MAX_OSCCAL 255
#endif	/* __AVR_ATtiny86x__  */

/* Support for ATtiny4313 */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny4313__) || defined(__AVR_ATtiny2313__) || \
    defined(__AVR_ATtiny4313A__) || defined(__AVR_ATtiny2313A__)
  #define TST_COUNTER_PIN "PB2"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB2
  #define TST_TCCR_A TCCR0A
  #define TST_TCCR_A_SET ((0<<COM0A1) | (1<<COM0A0))
  #define TST_TCCR_B TCCR0B
  #define TST_TCCR_B_SET (1<<CS00)
  #define MAX_OSCCAL 127
#endif	/* __AVR_ATtiny4313__ */

/* Support for ATtiny1634 */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny1634__)
  #define TST_COUNTER_PIN "PC0"
  #define CNT_ENABLE_DDR  DDRC
  #define CNT_ENABLE_PIN  DDRC0
  #define TST_TCCR_A TCCR0A
  #define TST_TCCR_A_SET ((0<<COM0A1) | (1<<COM0A0))
  #define TST_TCCR_B TCCR0B
  #define TST_TCCR_B_SET (1<<CS00)
  #define MAX_OSCCAL 255
#endif	/* __AVR_ATtiny1634__ */

/*------------------------------------------------------------------------ */
/* Sanguino support (and other 40pin DIP cpus) */
#if defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || \
    defined(__AVR_ATmega164PA__) || \
    defined(__AVR_ATmega324__) || defined(__AVR_ATmega324P__) || \
    defined(__AVR_ATmega324PA__) || \
    defined(__AVR_ATmega644__) || defined(__AVR_ATmega644P__) || \
    defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644PA__) || \
    defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || \
    defined(__AVR_ATmega1284A__) 
  #define TST_COUNTER_PIN "PD7"
  #define CNT_ENABLE_DDR  DDRD
  #define CNT_ENABLE_PIN  DDD7
  #define TST_TCCR_A TCCR2A
  #define TST_TCCR_A_SET ((0<<COM2A1) | (1<<COM2A0))
  #define TST_TCCR_B TCCR2B
  #define TST_TCCR_B_SET  (1<<CS20)
  #define MAX_OSCCAL 255
#endif		/* __AVR_ATmega644P__  .. */

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || \
    defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)
  #define TST_COUNTER_PIN "PD7"
  #define CNT_ENABLE_DDR  DDRD
  #define CNT_ENABLE_PIN  DDD7
  #define TST_TCCR_B TCCR2
  #define TST_TCCR_B_SET ((1<<COM20) | (1<<CS20))
  #define MAX_OSCCAL 255
#endif		/* __AVR_ATmage16__ || AVR_ATmega32__ */


/*------------------------------------------------------------------------ */
/* Support for AT90CAN32_64_128 */
#if defined(__AVR_AT90CAN32__) || defined(__AVR_AT90CAN64__) || defined(__AVR_AT90CAN128__) 
  #define TST_COUNTER_PIN "PB7"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB7
  #define TST_TCCR_B TCCR0A
  #define TST_TCCR_B_SET (1<<COM0A0) | (1<<CS00)
  #define MAX_OSCCAL 127
#endif		/* __AVR_AT90CAN... */

/* Support for AT90PWM2 family */
/*------------------------------------------------------------------------ */
#if defined(__AVR_AT90PWM2__) || defined(__AVR_AT90PWM2B__)
  #define TST_COUNTER_PIN "PD2"
  #define CNT_ENABLE_DDR  DDRD
  #define CNT_ENABLE_PIN  DDD2

/* PD3 (OC0A) is also TXD */
//  #define TST_TCCR_A TCCR0A
//  #define TST_TCCR_A_SET ((0<<COM0A1) | (1<<COM0A0))
//  #define TST_TCCR_B TCCR0B
//  #define TST_TCCR_B_SET (1<<CS00)

  #define TST_TCCR_A TCCR1A
  #define TST_TCCR_A_SET ((0<<COM1A1) | (1<<COM1A0))
  #define TST_TCCR_B TCCR1B
  // use mode 4 (CTC) with OCR1A = 0xff to simulate 8-Bit counter
  #define TST_TCCR_B_SET (0<<WGM13) | (1<<WGM12) | (1<<CS10)
  #define MAX_CNTR1 255
  #define MAX_OSCCAL 127

#endif		/* __AVR_AT90PWM... */

/* Support for AT90PWM3 family */
/*------------------------------------------------------------------------ */
#if defined(__AVR_AT90PWM3__) || defined(__AVR_AT90PWM3B__)
  #define TST_COUNTER_PIN "PC1"
  #define CNT_ENABLE_DDR  DDRC
  #define CNT_ENABLE_PIN  DDD1

  #define TST_TCCR_A TCCR1A
  #define TST_TCCR_A_SET ((0<<COM1B1) | (1<<COM1B0))
  #define TST_TCCR_B TCCR1B
  // use mode 4 (CTC) with OCR1A = 0xff to simulate 8-Bit counter
  #define TST_TCCR_B_SET (0<<WGM13) | (1<<WGM12) | (1<<CS10)
  #define MAX_CNTR1 255
  #define MAX_OSCCAL 127

#endif		/* __AVR_AT90PWM... */

/*------------------------------------------------------------------------ */
/* Support for ATmega64 */
#if defined(__AVR_ATmega64__) || defined(__AVR_ATmega64A__) || \
    defined(__AVR_ATmega128__)
  #define TST_COUNTER_PIN "PB4"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB4
  #define TST_TCCR_B TCCR0
  #define TST_TCCR_B_SET ((1<<COM00) | (1<<CS00))
  #define MAX_OSCCAL 255
#endif		/* __AVR_ATmega64__  .. */

/*------------------------------------------------------------------------ */
/* Mega support */
#if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) || \
    defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
  #define TST_COUNTER_PIN "PB7"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB7
  #define TST_TCCR_A TCCR0A
  #define TST_TCCR_A_SET ((0<<COM0A1) | (1<<COM0A0))
  #define TST_TCCR_B TCCR0B
  #define TST_TCCR_B_SET (1<<CS00)
  #define MAX_OSCCAL 255
#endif          /* __AVR_ATmega640__ || __AVR_ATmega1280__ ... */

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega162__) 
  #define TST_COUNTER_PIN "PB0"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB0
  #define TST_TCCR_B TCCR0
  #define TST_TCCR_B_SET ((1<<COM00) | (1<<CS00))
  #define MAX_OSCCAL 127
#endif

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega163__) || defined(__AVR_ATmega323__)
  #define TST_COUNTER_PIN "PD7"
  #define CNT_ENABLE_DDR  DDRD
  #define CNT_ENABLE_PIN  DDD7
  #define TST_TCCR_B TCCR2
  #define TST_TCCR_B_SET ((1<<COM20) | (1<<CS20))
  #define MAX_OSCCAL 255
#endif

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega169__) || defined(__AVR_ATmega169P__) || \
    defined(__AVR_ATmega169A__) || defined(__AVR_ATmega169PA__)
/*------------------------------------------------------------------------ */
  #define TST_COUNTER_PIN "PB4"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB4
  #define TST_TCCR_B TCCR0A
  #define TST_TCCR_B_SET (1<<COM0A0) | (1<<CS00)
  #define MAX_OSCCAL 127
#endif


/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega165__) || defined(__AVR_ATmega165P__) || \
    defined(__AVR_ATmega165A__) || defined(__AVR_ATmega165PA__) || \
    defined(__AVR_ATmega325__) || defined(__AVR_ATmega325P__) || \
    defined(__AVR_ATmega325A__) || defined(__AVR_ATmega325PA__) || \
    defined(__AVR_ATmega3250__) || defined(__AVR_ATmega3250P__) || \
    defined(__AVR_ATmega3250A__) || defined(__AVR_ATmega3250PA__) || \
    defined(__AVR_ATmega645__) || defined(__AVR_ATmega645P__) || \
    defined(__AVR_ATmega645A__) || defined(__AVR_ATmega645PA__) || \
    defined(__AVR_ATmega6450__) || defined(__AVR_ATmega6450P__) || \
    defined(__AVR_ATmega6450A__) || defined(__AVR_ATmega6450PA__) 
/*------------------------------------------------------------------------ */
  #define TST_COUNTER_PIN "PB4"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB4
  #define TST_TCCR_B TCCR0A
  #define TST_TCCR_B_SET (1<<COM0A0) | (1<<CS00)
  #define MAX_OSCCAL 255
#endif
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega329__) || defined(__AVR_ATmega329P__) || \
    defined(__AVR_ATmega329A__) || defined(__AVR_ATmega329PA__) || \
    defined(__AVR_ATmega3290__) || defined(__AVR_ATmega3290P__) || \
    defined(__AVR_ATmega3290A__) || defined(__AVR_ATmega3290PA__) || \
    defined(__AVR_ATmega649__) || defined(__AVR_ATmega649P__) || \
    defined(__AVR_ATmega649A__) || \
    defined(__AVR_ATmega6490__) || defined(__AVR_ATmega6490P__) || \
    defined(__AVR_ATmega6490A__) 
/*------------------------------------------------------------------------ */
  #define TST_COUNTER_PIN "PB4"
  #define CNT_ENABLE_DDR  DDRB
  #define CNT_ENABLE_PIN  DDB4
  #define TST_TCCR_B TCCR0A
  #define TST_TCCR_B_SET (1<<COM0A0) | (1<<CS00)
  #define MAX_OSCCAL 255
#endif

