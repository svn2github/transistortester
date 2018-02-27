

// setup some Macros for Assembly language use to simplify the port access
#if defined(__ASSEMBLER__) && (__ASSEMBLER__ != 33)

/* define AOUT macro */
/* AOUT select automatically the right instruction "out" or "sts" depending on argument. */
	.macro	AOUT adr, reg
	.if	_SFR_IO_REG_P(\adr)
	out	_SFR_IO_ADDR(\adr), \reg
	.else
	sts	_SFR_MEM_ADDR(\adr), \reg
	.endif
	.endm
/* define AIN macro */
/* AIN select automatically the right instruction "in" or "lds" depending on argument. */
	.macro	AIN reg, adr
	.if	_SFR_IO_REG_P(\adr)
	in	\reg, _SFR_IO_ADDR(\adr)
	.else
	lds	\reg, _SFR_MEM_ADDR(\adr)
	.endif
	.endm
/* define ASBIC macro */
/* AIN select automatically the right instruction "sbic" or "lds; sbrc" depending on argument. */
	.macro	ASBIC adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbic	_SFR_IO_ADDR(\adr), \bit
	.else
	 .if	_SFR_IO_REG_P(\adr)
	in	r0, _SFR_IO_ADDR(\adr)
	 .else
	lds	r0, _SFR_MEM_ADDR(\adr)
	 .endif
	sbrc	r0, \bit
	.endif
	.endm
/* define ASBIS macro */
/* AIN select automatically the right instruction "sbis" or "lds; sbrs" depending on argument. */
	.macro	ASBIS adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbis	_SFR_IO_ADDR(\adr), \bit
	.else
	 .if	_SFR_IO_REG_P(\adr)
	in	r0, _SFR_IO_ADDR(\adr)
	 .else
	lds	r0, _SFR_MEM_ADDR(\adr)
	 .endif
	sbrs	r0, \bit
	.endif
	.endm
/* define ASBI macro */
/* AIN select automatically the right instruction "sbi" or "lds; sbr; sts" depending on argument. */
	.macro	ASBI adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbi	_SFR_IO_ADDR(\adr), \bit
	.else
	 .if	_SFR_IO_REG_P(\adr)
	in	r25, _SFR_IO_ADDR(\adr)
	sbr	r25, \bit
	out	_SFR_IO_ADDR(\adr), r25
	 .else
	lds	r25, _SFR_MEM_ADDR(\adr)
	sbr	r25, \bit
	sts	_SFR_MEM_ADDR(\adr), r25
	 .endif
	.endif
	.endm
/* define ACBI macro */
/* AIN select automatically the right instruction "sbi" or "lds; cbr; sts" depending on argument. */
	.macro	ACBI adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	cbi	_SFR_IO_ADDR(\adr), \bit
	.else
	 .if	_SFR_IO_REG_P(\adr)
	in	r25, _SFR_IO_ADDR(\adr)
	cbr	r25, \bit
	out	_SFR_IO_ADDR(\adr), r25
	 .else
	lds	r25, _SFR_MEM_ADDR(\adr)
	cbr	r25, \bit
	sts	_SFR_MEM_ADDR(\adr), r25
	 .endif
	.endif
	.endm
#endif
