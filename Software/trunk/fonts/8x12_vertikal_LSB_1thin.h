// table of the bits for the 8x12 character set
// each byte hold 8 bits of a row, the upper bit is 1, the bit for the 8th line is 128
 #ifdef LCD_CYRILLIC                                      
  #define CHAR_COUNT12 (Cyr_ja + 16)
 #else
  #define CHAR_COUNT12 128
 #endif
const unsigned char PROGMEM font[CHAR_COUNT12][16]={
 /* 0x00 Resistor3  */
{ 0x20,0xF8,0x88,0x88,0x88,0x88,0xF8,0x20,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x01 Diode1  */
{ 0x20,0xFF,0xFE,0xFC,0xF8,0x70,0xFF,0x20,
  0x00,0x07,0x03,0x01,0x00,0x00,0x07,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x02 Diode2  */
{ 0x20,0xFF,0x70,0xF8,0xFC,0xFE,0xFF,0x20,
  0x00,0x07,0x00,0x00,0x01,0x03,0x07,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x03 Capacitor  */
{ 0x20,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x20,
  0x00,0x07,0x07,0x00,0x00,0x07,0x07,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x04 Omega  */
{ 0x38,0x44,0x82,0x02,0x82,0x44,0x38,0x00,
  0x02,0x02,0x03,0x00,0x03,0x02,0x02,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x05 mu  */
{ 0x00,0xF8,0x00,0x00,0x00,0x00,0xE0,0x00,
  0x08,0x07,0x04,0x00,0x04,0x02,0x07,0x04
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x06 Resistor1  */
{ 0x04,0x04,0x04,0x04,0x04,0x04,0xFC,0x20,
  0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x07 Resistor2  */
{ 0x20,0xFC,0x04,0x04,0x04,0x04,0x04,0x04,
  0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x08  */
{ 0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x09  */
{ 0xE0,0x00,0x00,0xC0,0x00,0x00,0xC0,0x00,
  0x00,0x01,0x01,0x00,0x01,0x01,0x00,0x01
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x0a  */
{ 0x00,0xC0,0x00,0x00,0xC0,0x00,0x00,0xE0,
  0x01,0x00,0x01,0x01,0x00,0x01,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x0b  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x0c  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x0d  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x0e  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x0f  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x10 Cry_D */
{ 0x00,0xFE,0x01,0x01,0x01,0xFF,0x00,0x00,
  0x03,0x01,0x01,0x01,0x01,0x01,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x11 Cyr_C */
{ 0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,
  0x01,0x01,0x01,0x01,0x01,0x03,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x12 Cyr_Schtsch*/
{ 0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,
  0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x03
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x13 Cyr_d */
{ 0x00,0xF0,0x08,0x08,0x08,0xF8,0x00,0x00,
  0x03,0x01,0x01,0x01,0x01,0x01,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x14 ,Cyr_f */
{ 0x70,0x88,0x88,0xFC,0x88,0x88,0x70,0x00,
  0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x15 Cyr_c */
{ 0xF8,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,
  0x01,0x01,0x01,0x01,0x01,0x03,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x16 Cyr_scht */
{ 0xF8,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,
  0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x03
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x17  */
{ 0x00,0x88,0x8C,0xFE,0xFE,0x8C,0x88,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x18  */
{ 0x00,0x08,0x0C,0xFE,0x0C,0x08,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x19  */
{ 0x00,0x80,0x80,0xFE,0x80,0x80,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x1a  */
{ 0x20,0x20,0x20,0x20,0xA8,0x70,0x20,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x1b  */
{ 0x10,0x38,0x54,0x10,0x10,0x10,0x10,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x1c  */
{ 0xF0,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x1d  */
{ 0x10,0x38,0x54,0x10,0x10,0x54,0x38,0x10,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x1e  */
{ 0x00,0x60,0x78,0x7E,0x78,0x60,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x1f  */
{ 0x06,0x1E,0x7E,0x7E,0x7E,0x1E,0x06,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x20 ' ' */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x21 '!' */
{ 0x00,0x06,0x7F,0x06,0x00,0x00,0x00,0x00,
  0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x22 '"' */
{ 0x00,0x07,0x0F,0x00,0x00,0x0F,0x07,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x23 '#' */
{ 0x88,0xFE,0x88,0x88,0x88,0xFE,0x88,0x00,
  0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x24 '$' */
{ 0x18,0x24,0x24,0xFF,0x24,0x24,0xC4,
  0x01,0x01,0x01,0x07,0x01,0x01,0x00
  },  /* x=0, y=0, w=7, h=16 */
	
 /* 0x25 '%' */
{ 0x18,0x18,0x80,0x40,0x20,0x10,0x08,0x00,
  0x02,0x01,0x00,0x00,0x00,0x03,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x26 '&' */
{ 0xEC,0x12,0x32,0x52,0xCC,0x80,0x60,0x00,
  0x01,0x02,0x02,0x02,0x00,0x03,0x02,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x27 ''' */
{ 0x00,0x08,0x07,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x28 '(' */
{ 0x00,0x70,0x88,0x04,0x02,0x00,0x00,0x00,
  0x00,0x00,0x00,0x01,0x02,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x29 ')' */
{ 0x00,0x02,0x04,0x88,0x70,0x00,0x00,0x00,
  0x00,0x02,0x01,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x2a '*' */
{ 0x20,0xA8,0x70,0x20,0x70,0xA8,0x20,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x2b '+' */
{ 0x20,0x20,0x20,0xF8,0x20,0x20,0x20,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x2c ',' */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x04,0x03,0x03,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x2d '-' */
{ 0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x2e '.' */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x2f '/' */
{ 0x00,0x80,0x40,0x20,0x10,0x08,0x06,0x00,
  0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x30 '0' */
{ 0xFE,0x41,0x21,0x11,0x09,0xFE,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x31 '1' */
{ 0x00,0x08,0x04,0x02,0xFF,0x00,0x00,0x00,
  0x00,0x00,0x02,0x02,0x03,0x02,0x02,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x32 '2' */
{ 0x06,0x81,0x41,0x21,0x11,0x0E,0x00,0x00,
  0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x33 '3' */
{ 0x02,0x01,0x11,0x11,0x11,0xEE,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x34 '4' */
{ 0x60,0x50,0x48,0x44,0x42,0xFF,0x40,0x00,
  0x00,0x00,0x00,0x00,0x02,0x03,0x02,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x35 '5' */
{ 0x9F,0x11,0x11,0x11,0x11,0x11,0xE1,0x00,
  0x00,0x01,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x36 '6' */
{ 0xFC,0x22,0x11,0x11,0x11,0x11,0xE1,0x00,
  0x01,0x02,0x02,0x02,0x02,0x02,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x37 '7' */
{ 0x07,0x01,0x01,0xC1,0x21,0x11,0x0F,0x00,
  0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x38 '8' */
{ 0xC6,0x29,0x11,0x11,0x11,0x29,0xC6,0x00,
  0x01,0x02,0x02,0x02,0x02,0x02,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x39 '9' */
{ 0x0E,0x11,0x11,0x11,0x11,0x91,0x7E,0x00,
  0x00,0x02,0x02,0x02,0x01,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x3a ':' */
{ 0x00,0x00,0xCC,0xCC,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x3b ';' */
{ 0x00,0x00,0x98,0x98,0x00,0x00,0x00,0x00,
  0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x3c '<' */
{ 0x20,0x50,0x88,0x04,0x02,0x00,0x00,0x00,
  0x00,0x00,0x00,0x01,0x02,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x3d '=' */
{ 0x00,0x50,0x50,0x50,0x50,0x50,0x50,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x3e '>' */
{ 0x00,0x02,0x04,0x88,0x50,0x20,0x00,0x00,
  0x00,0x02,0x01,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x3f '?' */
{ 0x04,0x02,0x02,0xC2,0x22,0x12,0x0C,0x00,
  0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x40 '@' */
{ 0xFE,0x01,0x11,0x29,0x29,0x29,0x3E,0x00,
  0x01,0x02,0x02,0x02,0x02,0x02,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x41 'A' */
{ 0xFC,0x22,0x21,0x21,0x22,0xFC,0x00,0x00,
  0x03,0x00,0x00,0x00,0x00,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x42 'B' */
{ 0x01,0xFF,0x11,0x11,0x11,0x11,0xEE,0x00,
  0x02,0x03,0x02,0x02,0x02,0x02,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x43 'C' */
{ 0xFC,0x02,0x01,0x01,0x01,0x01,0x86,0x00,
  0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x44 'D' */
{ 0x01,0xFF,0x01,0x01,0x01,0x02,0xFC,0x00,
  0x02,0x03,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x45 'E' */
{ 0x01,0xFF,0x11,0x11,0x11,0x39,0x03,0x00,
  0x02,0x03,0x02,0x02,0x02,0x02,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x46 'F' */
{ 0x01,0xFF,0x11,0x11,0x11,0x11,0x03,0x00,
  0x02,0x03,0x02,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x47 'G' */
{ 0xFC,0x02,0x01,0x01,0x21,0x21,0xE6,0x00,
  0x00,0x01,0x02,0x02,0x02,0x02,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x48 'H' */
{ 0xFF,0x10,0x10,0x10,0x10,0xFF,0x00,0x00,
  0x03,0x00,0x00,0x00,0x00,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x49 'I' */
{ 0x00,0x00,0x01,0xFF,0x01,0x00,0x00,0x00,
  0x00,0x00,0x02,0x03,0x02,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x4a 'J' */
{ 0x80,0x00,0x00,0x00,0x01,0xFF,0x01,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x4b 'K' */
{ 0x01,0xFF,0x10,0x10,0x28,0x44,0x83,0x00,
  0x02,0x03,0x00,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x4c 'L' */
{ 0x01,0xFF,0x01,0x00,0x00,0x00,0x80,0x00,
  0x02,0x03,0x02,0x02,0x02,0x02,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x4d 'M' */
{ 0xFF,0x02,0x0C,0x30,0x0C,0x02,0xFF,0x00,
  0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x4e 'N' */
{ 0xFF,0x04,0x08,0x30,0x40,0x80,0xFF,0x00,
  0x03,0x00,0x00,0x00,0x00,0x01,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x4f 'O' */
{ 0xFC,0x02,0x01,0x01,0x01,0x02,0xFC,0x00,
  0x00,0x01,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x50 'P' */
{ 0x01,0xFF,0x11,0x11,0x11,0x11,0x0E,0x00,
  0x02,0x03,0x02,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x51 'Q' */
{ 0xFC,0x02,0x01,0x01,0x81,0x02,0xFC,0x00,
  0x00,0x01,0x02,0x02,0x02,0x01,0x02,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x52 'R' */
{ 0x01,0xFF,0x11,0x11,0x11,0x31,0xCE,0x00,
  0x02,0x03,0x00,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x53 'S' */
{ 0x86,0x09,0x11,0x21,0x41,0x86,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x54 'T' */
{ 0x03,0x01,0x01,0xFF,0x01,0x01,0x03,0x00,
  0x00,0x00,0x02,0x03,0x02,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x55 'U' */
{ 0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,
  0x00,0x01,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x56 'V' */
{ 0x7F,0x80,0x00,0x00,0x00,0x80,0x7F,0x00,
  0x00,0x00,0x01,0x02,0x01,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x57 'W' */
{ 0xFF,0x00,0xC0,0x30,0xC0,0x00,0xFF,0x00,
  0x03,0x01,0x00,0x00,0x00,0x01,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x58 'X' */
{ 0xC7,0x28,0x10,0x10,0x10,0x28,0xC7,0x00,
  0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x59 'Y' */
{ 0x07,0x08,0x10,0xE0,0x10,0x08,0x07,0x00,
  0x00,0x00,0x02,0x03,0x02,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x5a 'Z' */
{ 0x87,0x41,0x21,0x11,0x09,0x05,0x83,0x00,
  0x03,0x02,0x02,0x02,0x02,0x02,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x5b '[' */
{ 0x00,0x00,0xFF,0x01,0x01,0x01,0x00,0x00,
  0x00,0x00,0x03,0x02,0x02,0x02,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x5c '\' */
{ 0x06,0x08,0x10,0x20,0x40,0x80,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x5d ']' */
{ 0x00,0x00,0x01,0x01,0xFF,0x00,0x00,0x00,
  0x00,0x00,0x02,0x02,0x03,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x5e '^' */
{ 0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x5f '_' */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x60 '`' */
{ 0x00,0x00,0x03,0x04,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x61 'a' */
{ 0x80,0x50,0x50,0x50,0x50,0xE0,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x02,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x62 'b' */
{ 0x02,0xFE,0x12,0x10,0x10,0x10,0xE0,0x00,
  0x02,0x03,0x02,0x02,0x02,0x02,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x63 'c' */
{ 0xE0,0x10,0x10,0x10,0x10,0x20,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x64 'd' */
{ 0xE0,0x10,0x10,0x10,0x12,0xFE,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x03,0x02,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x65 'e' */
{ 0xE0,0x50,0x50,0x50,0x50,0x60,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x66 'f' */
{ 0x20,0xFC,0x22,0x22,0x22,0x04,0x00,0x00,
  0x02,0x03,0x02,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x67 'g' */
{ 0x60,0x90,0x90,0x90,0x90,0xF0,0x10,0x00,
  0x02,0x04,0x04,0x04,0x04,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x68 'h' */
{ 0x02,0xFE,0x20,0x20,0x20,0x20,0xC0,0x00,
  0x02,0x03,0x02,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x69 'i' */
{ 0x00,0x00,0x08,0xFB,0x08,0x00,0x00,0x00,
  0x00,0x00,0x02,0x03,0x02,0x02,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x6a 'j' */
{ 0x80,0x00,0x08,0x08,0x0B,0xF8,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x6b 'k' */
{ 0x02,0xFE,0x40,0x40,0x40,0xA0,0x10,0x00,
  0x02,0x03,0x00,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x6c 'l' */
{ 0x00,0x04,0x04,0xFC,0x00,0x00,0x00,0x00,
  0x00,0x02,0x02,0x03,0x02,0x02,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x6d 'm' */
{ 0xF0,0x20,0x10,0xE0,0x10,0x10,0xE0,0x00,
  0x03,0x00,0x00,0x01,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x6e 'n' */
{ 0xF0,0x20,0x10,0x10,0x10,0xE0,0x00,0x00,
  0x03,0x00,0x00,0x00,0x00,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x6f 'o' */
{ 0xE0,0x10,0x10,0x10,0x10,0xE0,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x70 'p' */
{ 0x10,0xF0,0x20,0x10,0x10,0x10,0xE0,0x00,
  0x04,0x07,0x05,0x01,0x01,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x71 'q' */
{ 0xE0,0x10,0x10,0x10,0x20,0xF0,0x10,0x00,
  0x00,0x01,0x01,0x01,0x05,0x07,0x04,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x72 'r' */
{ 0x10,0xF0,0x20,0x10,0x10,0x10,0x60,0x00,
  0x02,0x03,0x02,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x73 's' */
{ 0x30,0x50,0x50,0x90,0x90,0x20,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x74 't' */
{ 0x10,0xFC,0x10,0x10,0x00,0x00,0x00,0x00,
  0x00,0x01,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x75 'u' */
{ 0xF0,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x76 'v' */
{ 0x70,0x80,0x00,0x00,0x00,0x80,0x70,0x00,
  0x00,0x00,0x01,0x02,0x01,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x77 'w' */
{ 0xF0,0x00,0x00,0xE0,0x00,0x00,0xF0,0x00,
  0x00,0x03,0x01,0x00,0x01,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x78 'x' */
{ 0x10,0x20,0xC0,0xC0,0xC0,0x20,0x10,0x00,
  0x02,0x01,0x00,0x00,0x00,0x01,0x02,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x79 'y' */
{ 0x70,0x80,0x80,0x80,0x80,0x70,0x00,0x00,
  0x04,0x04,0x04,0x02,0x01,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x7a 'z' */
{ 0x30,0x10,0x90,0x50,0x30,0x10,0x00,0x00,
  0x02,0x03,0x02,0x02,0x02,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x7b '{' */
{ 0x20,0x50,0x8E,0x01,0x01,0x01,0x00,0x00,
  0x00,0x00,0x03,0x04,0x04,0x04,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x7c '|' */
{ 0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x7d '}' */
{ 0x01,0x01,0x01,0x8E,0x50,0x20,0x00,0x00,
  0x04,0x04,0x04,0x03,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x7e '~' */
{ 0x06,0x01,0x01,0x02,0x04,0x04,0x02,0x01,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x7f  */
{ 0xE0,0x90,0x88,0x84,0x88,0x90,0xE0,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 #if 0
 /* 0x80  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x81  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x82  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x83  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x84  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x85  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x86  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x87  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x88  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x89  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x8a  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x8b  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x8c  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x8d  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x8e  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x8f  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x90  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x91  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x92  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x93  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x94  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x95  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x96  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x97  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x98  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x99  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x9a  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x9b  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x9c  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x9d  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x9e  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0x9f  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 #endif                                                                                           
#ifdef LCD_CYRILLIC                       	                                                  
 /* 0xa0, Cyr_B  */
{ 0x01,0xFF,0x11,0x11,0x11,0x11,0xE3,0x00,
  0x02,0x03,0x02,0x02,0x02,0x02,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xa1, Cyr_G  */
{ 0x01,0xFF,0x01,0x01,0x01,0x01,0x07,0x00,
  0x02,0x03,0x02,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xa2, Cyr_Jo  */
{ 0x02,0xFF,0x23,0x22,0x23,0x73,0x06,0x00,
  0x02,0x03,0x02,0x02,0x02,0x02,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xa3, Cyr_Zsch */
{ 0x06,0xD8,0x20,0xFE,0x20,0xD8,0x06,0x00,
  0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xa4, Cyr_Z */
{ 0x00,0x8C,0x02,0x22,0x22,0x22,0xDC,0x00,
  0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xa5, Cyr_I */
{ 0xFF,0x00,0x80,0x70,0x08,0x04,0xFF,0x00,
  0x07,0x03,0x00,0x00,0x00,0x00,0x07,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xa6, Cyr_J  */
{ 0xFC,0x01,0x82,0x42,0x22,0x11,0xFC,0x00,
  0x03,0x01,0x00,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xa7, Cyr_L  */
{ 0x00,0xF8,0x04,0x02,0x01,0x01,0xFF,0x00,
  0x02,0x01,0x00,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xa8, Cyr_P  */
{ 0xFF,0x01,0x01,0x01,0x01,0x01,0xFF,0x00,
  0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xa9, Cyr_U  */
{ 0x3F,0x40,0x40,0x40,0x40,0xFF,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xaa, Cyr_F  */
{ 0x7C,0x82,0x82,0xFF,0x82,0x82,0x7C,0x00,
  0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xab, Cyr_Tsch  */
{ 0x1F,0x20,0x20,0x20,0x20,0x20,0xFF,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xac, Cyr_Sch  */
{ 0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,
  0x03,0x02,0x02,0x03,0x02,0x02,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xad, Cyr_HH */
{ 0x03,0xFF,0x20,0x20,0x20,0x20,0xC0,0x00,
  0x00,0x03,0x02,0x02,0x02,0x02,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xae, Cyr_Y */
{ 0xFF,0x20,0x20,0xE0,0xC0,0xE0,0xFF,0x00,
  0x03,0x02,0x02,0x03,0x01,0x03,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xaf, Cyr_E */
{ 0x86,0x01,0x01,0x11,0x11,0x12,0xFC,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xb0, Cyr_Ju */
{ 0xFF,0x20,0x20,0xFE,0x21,0x01,0x01,0xFE,
  0x03,0x00,0x00,0x01,0x02,0x02,0x02,0x01
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xb1, Cyr_Ja */
{ 0xC6,0x29,0x11,0x11,0x11,0xFF,0x01,0x00,
  0x03,0x00,0x00,0x00,0x00,0x03,0x02,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xb2, Cyr_b */
{ 0xE0,0x50,0x50,0x50,0x50,0x98,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xb3, Cyr_v */
{ 0xF0,0x50,0x50,0x50,0x50,0xA0,0x00,0x00,
  0x03,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xb4, Cyr_g */
{ 0xF0,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
  0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xb5, Cyr_jo */
{ 0xE0,0x56,0x50,0x50,0x56,0x60,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xb6, Cyr_zsch */
{ 0x30,0xC0,0xC0,0xF0,0xC0,0xC0,0x30,0x00,
  0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xb7, Cyr_z */
{ 0x20,0x10,0x50,0x50,0x50,0xA0,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xb8, Cyr_i */
{ 0xF0,0x00,0x80,0x80,0x40,0xF0,0x00,0x00,
  0x03,0x01,0x00,0x00,0x00,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xb9, Cyr_j */
{ 0xF0,0x82,0x84,0x84,0xC2,0xF0,0x00,0x00,
  0x03,0x01,0x00,0x00,0x00,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xba, Cyr_k */
{ 0xF0,0x40,0x40,0xC0,0xA0,0x10,0x00,0x00,
  0x03,0x00,0x00,0x00,0x03,0x02,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xbb, Cyr_l */
{ 0x00,0xC0,0x20,0x10,0x10,0xF0,0x00,0x00,
  0x02,0x03,0x00,0x00,0x02,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xbc, Cyr_m */
{ 0xF0,0x20,0x40,0x80,0x40,0x20,0xF0,0x00,
  0x03,0x00,0x00,0x01,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xbd, Cyr_n */
{ 0xF0,0x40,0x40,0x40,0x40,0xF0,0x00,0x00,
  0x03,0x00,0x00,0x00,0x00,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xbe, Cyr_p */
{ 0xF0,0x10,0x10,0x10,0x10,0xF0,0x00,0x00,
  0x03,0x00,0x00,0x00,0x00,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xbf, Cyr_t */
{ 0x30,0x10,0x10,0xF0,0x10,0x10,0x30,0x00,
  0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xc0, Cyr_tsch */
{ 0x70,0x80,0x80,0x80,0x80,0xF0,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xc1, Cyr_sch */
{ 0xF0,0x00,0x00,0xF0,0x00,0x00,0xF0,0x00,
  0x03,0x02,0x02,0x03,0x02,0x02,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xc2, Cyr_hh */
{ 0x30,0xF0,0x40,0x40,0x40,0x40,0x80,0x00,
  0x00,0x03,0x02,0x02,0x02,0x02,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xc3, Cyr_y */
{ 0xF0,0x40,0x40,0xC0,0x80,0x40,0xF0,0x00,
  0x03,0x02,0x02,0x01,0x00,0x00,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xc4, Cyr_ww */
{ 0xF0,0x40,0x40,0x40,0x40,0x80,0x00,0x00,
  0x03,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xc5, Cyr_e */
{ 0x20,0x30,0x50,0x50,0x50,0xE0,0x00,0x00,
  0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xc6, Cyr_ju */
{ 0xE0,0x80,0xC0,0x20,0x20,0x20,0xC0,0x00,
  0x03,0x00,0x01,0x02,0x02,0x02,0x01,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xc7, Cyr_ja */
{ 0x60,0x90,0x90,0x90,0x90,0xF0,0x00,0x00,
  0x02,0x01,0x00,0x00,0x00,0x03,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 #if 0
 /* 0xc8  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xc9  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xca  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xcb  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xcc  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xcd  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xce  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xcf  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xd0  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xd1  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xd2  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xd3  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xd4  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xd5  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xd6  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xd7  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xd8  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xd9  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xda  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xdb  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xdc  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xdd  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xde  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xdf  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xe0, Cyr_D */
{ 0x00,0x80,0x7F,0x00,0x00,0xFF,0x00,0x00,
  0x07,0x01,0x01,0x01,0x01,0x01,0x07,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xe1, Cyr_C */
{ 0x02,0xFE,0x02,0x00,0x02,0xFE,0x02,0x00,
  0x01,0x01,0x01,0x01,0x01,0x05,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xe2, Cyr_Schtsch */
{ 0x00,0xFF,0x00,0xFE,0x00,0xFF,0x00,0x00,
  0x01,0x01,0x01,0x01,0x01,0x05,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xe3, Cyr_d */
{ 0x00,0x80,0x7C,0x02,0x01,0xFF,0x01,0x00,
  0x07,0x01,0x01,0x01,0x01,0x01,0x07,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xe4, Cyr_f */
{ 0x70,0x88,0x05,0xFF,0x05,0x88,0x70,0x00,
  0x00,0x00,0x05,0x07,0x05,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xe5, Cyr_c */
{ 0x01,0xFF,0x01,0x00,0x01,0xFF,0x01,0x00,
  0x01,0x01,0x01,0x01,0x01,0x05,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xe6, Cyr_schtsch */
{ 0x01,0xFF,0x01,0xFC,0x01,0xFF,0x01,0x00,
  0x01,0x01,0x01,0x01,0x01,0x05,0x03,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xe7  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xe8  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xe9  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xea  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xeb  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xec  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xed  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xee  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xef  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xf0  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xf1  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xf2  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xf3  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xf4  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xf5  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xf6  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xf7  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xf8  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xf9  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xfa  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xfb  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xfc  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xfd  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xfe  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 /* 0xff  */
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  },  /* x=0, y=0, w=8, h=16 */
	
 #endif                                         
#endif                                    
};
