
#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

//Talking to si5324 via spi
int set_addr(int address);
char read4addr(int address); // Need to set page, only reads 8bit address...
int write2addr(int address,int value); // Works within the page so 8 bit address
int set2page(int value); // sets the page to the 8 bit value
int spi_si5344_write(unsigned int address,unsigned char value); // Writes 8 bits into the 16 bit register
int spi_si5344_read(unsigned int address); // Writes 8 bits into the 16 bit register

// MCP SPI
void spi_MCP_io(int ballpark, int page);

//Nexys SPI
int spi_NexyDDMTD_io(int addr, int data);
