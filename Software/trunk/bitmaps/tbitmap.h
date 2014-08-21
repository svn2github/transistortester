#include <avr/pgmspace.h>

struct tbitmap {
   unsigned char width; // Bitmap width in bit
   unsigned char height;// Bitmap height in bit
   const unsigned char *data;
};

