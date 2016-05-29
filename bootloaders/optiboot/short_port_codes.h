/*
 * ------------------------------------------------------------------------
 * A bunch of macros to enable the LED to be specifed as "B5" for bit 5 
 * of port B, and similar.
 */

#ifdef PORTA
#define pA0 0x100
#define pA1 0x101
#define pA2 0x102
#define pA3 0x103
#define pA4 0x104
#define pA5 0x105
#define pA6 0x106
#define pA7 0x107
#endif

#ifdef PORTB
#define pB0 0x200
#define pB1 0x201
#define pB2 0x202
#define pB3 0x203
#define pB4 0x204
#define pB5 0x205
#define pB6 0x206
#define pB7 0x207
#endif

#ifdef PORTC
#define pC0 0x300
#define pC1 0x301
#define pC2 0x302
#define pC3 0x303
#define pC4 0x304
#define pC5 0x305
#define pC6 0x306
#define pC7 0x307
#endif

#ifdef PORTD
#define pD0 0x400
#define pD1 0x401
#define pD2 0x402
#define pD3 0x403
#define pD4 0x404
#define pD5 0x405
#define pD6 0x406
#define pD7 0x407
#endif

#ifdef PORTE
#define pE0 0x500
#define pE1 0x501
#define pE2 0x502
#define pE3 0x503
#define pE4 0x504
#define pE5 0x505
#define pE6 0x506
#define pE7 0x507
#endif

#ifdef PORTF
#define pF0 0x600
#define pF1 0x601
#define pF2 0x602
#define pF3 0x603
#define pF4 0x604
#define pF5 0x605
#define pF6 0x606
#define pF7 0x607
#endif

#ifdef PORTG
#define pG0 0x700
#define pG1 0x701
#define pG2 0x702
#define pG3 0x703
#define pG4 0x704
#define pG5 0x705
#define pG6 0x706
#define pG7 0x707
#endif

#ifdef PORTH
#define pH0 0x800
#define pH1 0x801
#define pH2 0x802
#define pH3 0x803
#define pH4 0x804
#define pH5 0x805
#define pH6 0x806
#define pH7 0x807
#endif

#ifdef PORTJ
#define pJ0 0xA00
#define pJ1 0xA01
#define pJ2 0xA02
#define pJ3 0xA03
#define pJ4 0xA04
#define pJ5 0xA05
#define pJ6 0xA06
#define pJ7 0xA07
#endif

#ifdef PORTK
#define pK0 0xB00
#define pK1 0xB01
#define pK2 0xB02
#define pK3 0xB03
#define pK4 0xB04
#define pK5 0xB05
#define pK6 0xB06
#define pK7 0xB07
#endif

#ifdef PORTL
#define pL0 0xC00
#define pL1 0xC01
#define pL2 0xC02
#define pL3 0xC03
#define pL4 0xC04
#define pL5 0xC05
#define pL6 0xC06
#define pL7 0xC07
#endif
