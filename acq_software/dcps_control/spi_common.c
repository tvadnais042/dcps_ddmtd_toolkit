#include <stdlib.h>
#include <stdio.h>
#include "spi_common.h"
#include <stdint.h>
#include <inttypes.h>



//Printing 16 bits...
void print_bits(int size,int64_t Data)
{
  char Result[size];
  for(int i=0; i< size;i++)
  {
    Result[i] = (Data >>i ) & 1; //Take the Least Significant Bit after shifting
  }


  printf("%2u bits::: MSB: ",size);
  for(int i=1;i<=size;i++ )
  {
    printf("%i",(int)Result[size-i]);
    if((i % 4 == 0 ) && (i != 0 ))printf(" ");
    // if((i % 8 == 0 ) && (i != 0 ))printf("\n");
  }
  printf(":LSB");

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
  // bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0); 
  // bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);	//kHz
  // bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_);	// 50MHz
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);     // 6 MHz
  bcm2835_spi_chipSelect(BCM2835_SPI_CS1);			// Chip-Select 0
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);	// Value of CS when active
}

void init_addr()
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
  // bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0); 
  // bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);	//kHz
  // bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_);	// 50MHz
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


int print_nWords(void* virtual_address, int byte_count, int mod_num)  
{
    // int mod_num = 8;
    int word_byte = 4;
    char *p = virtual_address;
    int offset;
    printf("\n");
    uint val1;

    for (offset = 0; offset < byte_count; offset=offset+word_byte) {
        

        if(offset % (4*mod_num) == 0 & (offset != 0) ) {printf("\n",offset);} //


        // val1 = (uint)(0xffffffff&((p[0+offset]&0b11111111)<<24|p[1+offset]<<16|p[2+offset]<<8|p[3+offset]));
        val1 = (uint)(0xffffffff&((p[3+offset]&0xFF)<<24|p[2+offset]<<16|p[1+offset]<<8|p[0+offset]));

        // printf("0x%12x",(val1));
        print_bits(32,(int64_t)val1);
        // printf("%" PRIu64,val1);



        printf(" ");

        }
    
    printf("\n");
    printf("\n");

    return 0;
}


int set_value_bit(char* mem, int position, int value_bit) //position starts from zero
{


    int byte_no = ((int)position) / 8;
    int byte_pos = position % 8;

    // printf("%u,%u \n",byte_no,byte_pos);

    if (value_bit == 0) mem[byte_no] = mem[byte_no] & (~(0x1 << byte_pos));
    else if (value_bit == 1) mem[byte_no] = mem[byte_no] | ((0x1 << byte_pos));
    else return 0;
      
    return 0;


}

int get_value_bit(char* mem, int position)
{

  int byte_no = ((int)position) / 8;
  int byte_pos = position % 8;
  return 0x1&(mem[byte_no]>>byte_pos);
}

int reverse_bits(char* in_buff, char* out_buff,int size)
{
    for(int i=0; i < size; i=i+1)
    {
        set_value_bit(out_buff,i,get_value_bit(in_buff,size-i-1));
    }
}
