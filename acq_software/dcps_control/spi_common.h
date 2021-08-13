#include <bcm2835.h>

// Initialize the SPI interface.
void init_spi(void);

// For choosing ballpark and page 
void init_addr(void);

// Close the SPI interface.
void end_spi(void);

// Send a 32-bit spi_read command, and keep the 16 bits that are returned.
int spi_get_16bits(int addr);

// Send a 32-bit spi_write command, which writes 16 bits into the address.
int spi_put_16bits(int addr, int value);

// printing bits...
void print_bits(int size,int64_t Data);

//printing n words
int print_nWords(void* virtual_address, int byte_count, int mod_num);  

// set single bit of a memory, useful in constructing packets
int set_value_bit(char* mem, int position, int value_bit);
//get the single bit value
int get_value_bit(char* mem, int position);
int reverse_bits(char* in_buff, char* out_buff,int size); //Size in bits
