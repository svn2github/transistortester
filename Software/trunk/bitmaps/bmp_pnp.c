
#include "tbitmap.h"
// only update for NPN at location 14,16

//*****************************************************************************
// Bitmap:       bmp_pnp
// Width:        6
// Height:       8
// Memory usage: 8 bytes
//*****************************************************************************

//*****************************************************************************
//
// The data for the bitmapbmp_pnp
//
//*****************************************************************************
static const unsigned char bmp_pnp_data[12 * 1] PROGMEM ={
	/* 0x01, 0x01, 0x7f, 0x7f, 0x03, 0x07,*/
        0xfe, 0x7c, 
	0x3c, 0x7c, 0xec, 0xc4
};

//*****************************************************************************
//
// The bitmap definition
//
//*****************************************************************************
const struct tbitmap g_bmp_pnp PROGMEM =
{
	//
	// The width of the bitmap.
	//
	6,

	//
	// The height of the bitmap.
	//
	8,

	//
	// A pointer to the table containing the bitmap data.
	//
	bmp_pnp_data
};

