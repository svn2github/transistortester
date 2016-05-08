/*
 * A minimal SPI API.
 *
 * Licensed under AGPLv3.
 */

#define SPI_DDR		DDRB
#define SCK_PIN		(1 << 5)
#define MISO_PIN	(1 << 4)
#define MOSI_PIN	(1 << 3)
#define SS_PIN		(1 << 2)

static void spi_mode(uint8_t mode) {
	/* Enable SPI master with configuration byte specified */
	SPCR = 0;
	SPCR = (mode & 0x7F) | (1 << SPE) | (1 << MSTR);
	SPSR = 1 << SPI2X; /* double speed */
	(void) SPSR;
	(void) SPDR;
}

static void spi_init(void) {
	/* Initialize the SPI pins: SCK & MOSI as outputs, MISO as input */
	SPI_DDR |= SCK_PIN | MOSI_PIN;
	SPI_DDR &= ~MISO_PIN;
	/* Must also pre-set SS to output, otherwise it's going to bite us */
	SPI_DDR |= SS_PIN;

	/* Enable SPI Master, MSB, SPI mode 0, FOSC/4 */
	spi_mode(0);
}

static uint8_t spi_transfer(uint8_t value) {
	uint8_t cnt = 0xff;
	SPDR = value;
	while (cnt -- && !(SPSR & (1 << SPIF)));
	return SPDR;
}
