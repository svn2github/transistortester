/* wast_bytes.S generates a sequence of words in section text. */
/* A sequence of 7 different words is repeated as often as */
/* the Byte count value BIGPROGRAM specifies */
/* Currently a sequence of 0,1,2,3,4,5,6 is generated. */
/* The only sense is to test the bootloader for higher addresses. */

#ifndef __ASSEMBLER__
 #define __ASSEMBLER__
#endif
	.section .text
	.func wast_bytes

#define REPETITION_COUNT ((BIGPROGRAM+1)/14)

	.rept	REPETITION_COUNT
        .word	0x0000
        .word	0x0001
        .word	0x0002
        .word	0x0003
        .word	0x0004
        .word	0x0005
        .word	0x0006
	.endr
#if  (BIGPROGRAM - (REPETITION_COUNT*14)) > 0
	.word	0x0000
#endif
#if  (BIGPROGRAM - (REPETITION_COUNT*14)) > 2
	.word	0x0001
#endif
#if  (BIGPROGRAM - (REPETITION_COUNT*14)) > 4
	.word	0x0002
#endif
#if  (BIGPROGRAM - (REPETITION_COUNT*14)) > 6
	.word	0x0003
#endif
#if  (BIGPROGRAM - (REPETITION_COUNT*14)) > 8
	.word	0x0004
#endif
#if  (BIGPROGRAM - (REPETITION_COUNT*14)) > 10
	.word	0x0005
#endif
#if  (BIGPROGRAM - (REPETITION_COUNT*14)) > 12
	.word	0x0006
#endif

	.endfunc
