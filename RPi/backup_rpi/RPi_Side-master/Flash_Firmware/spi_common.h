#include <bcm2835.h>

// Initialize the SPI interface.
void init_spi(void);

// Close the SPI interface.
void end_spi(void);

// Send a 32-bit spi_read command, and keep the 16 bits that are returned.
int spi_get_16bits(int addr);

// Send a 32-bit spi_write command, which writes 16 bits into the address.
int spi_put_16bits(int addr, int value);

// printing 16 bits...
void print16(int Data);
