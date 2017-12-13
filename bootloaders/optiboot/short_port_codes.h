/*
 * ------------------------------------------------------------------------
 * A bunch of macros to enable the LED to be specifed as "B5" for bit 5 
 * of port B, and similar.
 */

#ifdef PORTA
#define nA0 0x100
#define nA1 0x101
#define nA2 0x102
#define nA3 0x103
#define nA4 0x104
#define nA5 0x105
#define nA6 0x106
#define nA7 0x107
#else
#define nA0 0x1100
#define nA1 0x1101
#define nA2 0x1102
#define nA3 0x1103
#define nA4 0x1104
#define nA5 0x1105
#define nA6 0x1106
#define nA7 0x1107
#endif

#ifdef PORTB
#define nB0 0x200
#define nB1 0x201
#define nB2 0x202
#define nB3 0x203
#define nB4 0x204
#define nB5 0x205
#define nB6 0x206
#define nB7 0x207
#else
#define nB0 0x1200
#define nB1 0x1201
#define nB2 0x1202
#define nB3 0x1203
#define nB4 0x1204
#define nB5 0x1205
#define nB6 0x1206
#define nB7 0x1207
#endif

#ifdef PORTC
#define nC0 0x300
#define nC1 0x301
#define nC2 0x302
#define nC3 0x303
#define nC4 0x304
#define nC5 0x305
#define nC6 0x306
#define nC7 0x307
#else
#define nC0 0x1300
#define nC1 0x1301
#define nC2 0x1302
#define nC3 0x1303
#define nC4 0x1304
#define nC5 0x1305
#define nC6 0x1306
#define nC7 0x1307
#endif

#ifdef PORTD
#define nD0 0x400
#define nD1 0x401
#define nD2 0x402
#define nD3 0x403
#define nD4 0x404
#define nD5 0x405
#define nD6 0x406
#define nD7 0x407
#else
#define nD0 0x1400
#define nD1 0x1401
#define nD2 0x1402
#define nD3 0x1403
#define nD4 0x1404
#define nD5 0x1405
#define nD6 0x1406
#define nD7 0x1407
#endif

#ifdef PORTE
#define nE0 0x500
#define nE1 0x501
#define nE2 0x502
#define nE3 0x503
#define nE4 0x504
#define nE5 0x505
#define nE6 0x506
#define nE7 0x507
#else
#define nE0 0x1500
#define nE1 0x1501
#define nE2 0x1502
#define nE3 0x1503
#define nE4 0x1504
#define nE5 0x1505
#define nE6 0x1506
#define nE7 0x1507
#endif

#ifdef PORTF
#define nF0 0x600
#define nF1 0x601
#define nF2 0x602
#define nF3 0x603
#define nF4 0x604
#define nF5 0x605
#define nF6 0x606
#define nF7 0x607
#else
#define nF0 0x1600
#define nF1 0x1601
#define nF2 0x1602
#define nF3 0x1603
#define nF4 0x1604
#define nF5 0x1605
#define nF6 0x1606
#define nF7 0x1607
#endif

#ifdef PORTG
#define nG0 0x700
#define nG1 0x701
#define nG2 0x702
#define nG3 0x703
#define nG4 0x704
#define nG5 0x705
#define nG6 0x706
#define nG7 0x707
#else
#define nG0 0x1700
#define nG1 0x1701
#define nG2 0x1702
#define nG3 0x1703
#define nG4 0x1704
#define nG5 0x1705
#define nG6 0x1706
#define nG7 0x1707
#endif

#ifdef PORTH
#define nH0 0x800
#define nH1 0x801
#define nH2 0x802
#define nH3 0x803
#define nH4 0x804
#define nH5 0x805
#define nH6 0x806
#define nH7 0x807
#else
#define nH0 0x1800
#define nH1 0x1801
#define nH2 0x1802
#define nH3 0x1803
#define nH4 0x1804
#define nH5 0x1805
#define nH6 0x1806
#define nH7 0x1807
#endif

#ifdef PORTJ
#define nJ0 0xA00
#define nJ1 0xA01
#define nJ2 0xA02
#define nJ3 0xA03
#define nJ4 0xA04
#define nJ5 0xA05
#define nJ6 0xA06
#define nJ7 0xA07
#else
#define nJ0 0x1A00
#define nJ1 0x1A01
#define nJ2 0x1A02
#define nJ3 0x1A03
#define nJ4 0x1A04
#define nJ5 0x1A05
#define nJ6 0x1A06
#define nJ7 0x1A07
#endif

#ifdef PORTK
#define nK0 0xB00
#define nK1 0xB01
#define nK2 0xB02
#define nK3 0xB03
#define nK4 0xB04
#define nK5 0xB05
#define nK6 0xB06
#define nK7 0xB07
#else
#define nK0 0x1B00
#define nK1 0x1B01
#define nK2 0x1B02
#define nK3 0x1B03
#define nK4 0x1B04
#define nK5 0x1B05
#define nK6 0x1B06
#define nK7 0x1B07
#endif

#ifdef PORTL
#define nL0 0xC00
#define nL1 0xC01
#define nL2 0xC02
#define nL3 0xC03
#define nL4 0xC04
#define nL5 0xC05
#define nL6 0xC06
#define nL7 0xC07
#else
#define nL0 0x1C00
#define nL1 0x1C01
#define nL2 0x1C02
#define nL3 0x1C03
#define nL4 0x1C04
#define nL5 0x1C05
#define nL6 0x1C06
#define nL7 0x1C07
#endif
