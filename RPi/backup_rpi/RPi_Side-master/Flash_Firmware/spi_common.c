#include <stdlib.h>
#include <stdio.h>
#include "spi_common.h"


//Printing 16 bits...
void print16(int Data)
{
  char Result[16];
  for(int i=0; i< 16;i++)
  {
    Result[i] = (Data >>i ) & 1; //Take the Least Significant Bit after shifting
  }
  for(int i=0;i<16;i++ )
  {
    printf("%i",(int)Result[15-i]);
    if(i == 7)printf("\t");
  }
  printf("\n");


}




// Send a 32-bit spi_read command, and keep the 16 bits that are returned.
int spi_get_16bits(int addr)
{
  char cmd[4], data[4];
  unsigned spi_read, spi_auto_inc, spi_addr, spi_command;
  int result;

  // Create the 32-bit command word.
  spi_read = 1;
  spi_auto_inc = 0;
  spi_addr = addr & 0x3FF; //Taking the 0b1111111111 of the address
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20); //Constructing the command...
  cmd[0] = spi_command >> 24;//Taking the first 8 bits
  cmd[1] = spi_command >> 16;//Taking the next 8 bits
  cmd[2] = spi_command >> 8;//Taking the next 8 bits
  cmd[3] = spi_command >> 0;//Taking the next 8 bits

  // Send the command.
  bcm2835_spi_transfernb(cmd, data, 4); // input buffer, output buffer, and length of input and output buffer....

  result = (data[2]<<8) | data[3];
  return (result);
}

// Send a 32-bit spi_write command, which writes 16 bits into the address.
int spi_put_16bits(int addr, int value)
{
  char cmd[4], data[4];
  unsigned spi_read, spi_auto_inc, spi_addr, spi_command;

  // Create the 32-bit command word.
  spi_read = 0;
  spi_auto_inc = 0;
  spi_addr = addr & 0x3FF;
  spi_command = (spi_read<<31)|(spi_auto_inc<<30)|(spi_addr<<20)|
    (value & 0xFFFF);
  cmd[0] = spi_command >> 24;
  cmd[1] = spi_command >> 16;
  cmd[2] = spi_command >> 8;
  cmd[3] = spi_command >> 0;

  // Send the command.
  bcm2835_spi_transfernb(cmd, data, 4);
  return (0);
}

// Initialize the SPI interface.
void init_spi()
{
  if(!bcm2835_init())
  {
    printf("bcm2825_init failed. You most likely are not running as root.\n");
    exit(1);
  }

  if(!bcm2835_spi_begin())
  {
    printf("bcm2825_spi_begin failed. You most likely are not running as root.\n");
    exit(1);
  }

  bcm2835_spi_begin();
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
  //bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);	// 1.5625 MHz
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);     // 6 MHz
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);			// Chip-Select 0
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);	// Value of CS when active
}


// Close the SPI interface.
void end_spi()
{
  bcm2835_spi_end();
  bcm2835_close();
}
