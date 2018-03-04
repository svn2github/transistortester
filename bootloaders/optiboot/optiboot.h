/*
 * optiboot.h
 * optiboot helper defining the default pin assignments (LED, SOFT_UART)
 * for the various chips that are supported.  This also has some ugly macros
 * for selecting among various UARTs and LED possibilities using command-line
 * defines like "UART=2 LED=B5"
 *
 * reorganized 2016 by K.-H. Kuebbeler
 * optiboot.h is separated from pin_defs.h  2018 by K.-H. Kuebbeler 
 * Copyright 2013-2015 by Bill Westfield.
 * Copyright 2010 by Peter Knight.
 * This software is licensed under version 2 of the Gnu Public Licence.
 * See optiboot.c for details.
 */

#ifndef EEARL
 /* sometimes, if EEARH is missing because of limited EEprom space,
    the EEARL is named EEAR
  */
 #define EEARL EEAR	
#else
 #ifndef EEAR
  #define EEAR EEARL
 #endif
#endif

#if !defined(SELFPRGEN) && defined(SPMEN)
 #define SELFPRGEN SPMEN                /* use different name of SELFPRGEN bit */
#endif

#ifndef SPMCSR
 #if defined(SPMCR)
  #define SPMCSR SPMCR                   /* use different name of SPM register */
 #endif
#endif

#if !defined(WDCE) 
 #if defined(WDTOE)
  #define WDCE		WDTOE
 #elif defined WDE
  #define WDCE		WDE
 #endif
#endif

#ifndef MCUCSR
 #if defined(MCUSR)
  #define MCUCSR MCUSR
 #endif
#endif

#ifndef RAMSTART
 #define RAMSTART (0x100)
#endif

/* We now compute the NRWWSTART address from FLASHEND and BOOT_PAGE_LEN */
#ifndef BOOT_PAGE_LEN
 #ifndef NO_WARNING
  #warning "BOOT_PAGE_LEN is not set"
 #endif
 #if FLASHEND >= 0xffff
  #define BOOT_PAGE_LEN 1024
 #elif FLASHEND >= 0x7fff
  #define BOOT_PAGE_LEN 512
 #elif FLASHEND >= 0x1fff
  #define BOOT_PAGE_LEN 256
 #else
  #define BOOT_PAGE_LEN 32
 #endif
#endif


#ifndef NRWWSTART
 #if BOOT_PAGE_LEN <= SPM_PAGESIZE
  /* I know no device, where the BOOT_PAGE_LEN is less or equal to SPM_PAGESIZE */
  #define NRWWSTART 0		/* device has no Boot Partition */
 #else
  /* the total Bootloader area (8 Boot pages) is NRWW */
  #ifdef __ASSEMBLER__
   #define NRWWSTART  (((FLASHEND+1UL)  - (BOOT_PAGE_LEN * 8)) & 0xffff)
  #else
   #define NRWWSTART  (((FLASHEND+1UL)  - (BOOT_PAGE_LEN * 8)) & 0xffff)
  #endif
 #endif
#endif
