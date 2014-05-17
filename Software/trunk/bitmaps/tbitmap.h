#include <avr/pgmspace.h>

struct tbitmap {
   unsigned char type;  // Bitmap type
   unsigned char width; // Bitmap width in bit
   unsigned char height;// Bitmap height in bit
   unsigned char stuffing;
   const unsigned char *data;
};

// Supported Bitmap types
#define BITMAP_UNCOMPRESSED     1

