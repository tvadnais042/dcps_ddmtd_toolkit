#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "NexysDDMTD.h"
#include "spi_common.h"



int set_addr(int address) {
  char cmd[2],data[2];  // two Bytes
  cmd[0] = 0b00000000; //Command to set address
  cmd[1] = address; // Page Address Location
  bcm2835_spi_transfernb(cmd, data, 2);

}

char read4addr(int address) // Need to set page, only reads 8bit address...
{
  char cmd[2],data[2];  // two Bytes
  set_addr(address&0xFF); //8 bits only
  cmd[0] = 0b10000000; //Command to Read Data
  bcm2835_spi_transfernb(cmd, data, 2);
  // print_bits(8,data[1]);
  return data[1];
}


int write2addr(int address,int value){ // Works within the page so 8 bit address
  char cmd[2],data[2];  // two Bytes
  //set_addr
  set_addr(address&0xFF); //8 bits only
  // Write the page address
  cmd[0] = 0b01000000; //Command to Write Data
  cmd[1] = value&0xFF; // Write the page address
  bcm2835_spi_transfernb(cmd, data, 2);

}

int set2page(int value) {
    write2addr(0x1,value&0xFF);
}

int spi_si5344_write(unsigned int address,unsigned char value) // Writes 8 bits into the 16 bit register
{
  spi_NexyDDMTD_io(0x101,0x1);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS1); // Changing to
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);	// Value of CS when active



  char cmd[2],data[2];  // two Bytes

  //Changing page address
  unsigned int page;
  page = (address>>8)&(0xFF);
  set2page(page); //write to page register the page you want to go to.
  // if ((int)read4addr(0x1) == page) printf("Success at setting the page to 0x%04x\n",(int)read4addr(0x1) );
  // else printf("Oh No...... Page not set to 0x%04x, the read value is 0x%04x! \n",page,(int)read4addr(0x1));
  write2addr((address&0xFF),value);
  // if ((int)read4addr(address&0xFF) == (int)value) printf("Success at writing  to 0x%04x with the value 0x%02x \n",(int)read4addr(0x1)<<8|address&0xFF,value );
  // else printf("Oh No...... Page not set to 0x%02x, the read value is 0x%02x! \n",(int)value,(int)read4addr(0x1));

  bcm2835_spi_chipSelect(BCM2835_SPI_CS0); // Talking to FPGA
  spi_NexyDDMTD_io(0x101,0x0000); // Making the FPGA connect MEM to RPi from RPi

}


int spi_si5344_read(unsigned int address) // Writes 8 bits into the 16 bit register
{
  spi_NexyDDMTD_io(0x101,0x1);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS1); // Changing to
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);	// Value of CS when active
  char cmd[2],data[2];  // two Bytes

  //Changing page address
  unsigned int page;
  page = (address>>8)&(0xFF);
  set2page(page); //write to page register the page you want to go to.
  // if ((int)read4addr(0x1) == page) printf("Success at setting the page to 0x%04x\n",(int)read4addr(0x1) );
  // else printf("Oh No...... Page not set to 0x%04x, the read value is 0x%04x! \n",page,(int)read4addr(0x1));
  int value = read4addr((address&0xFF));

  bcm2835_spi_chipSelect(BCM2835_SPI_CS0); // Talking to FPGA
  spi_NexyDDMTD_io(0x101,0x0000); // Making the FPGA connect MEM to RPi from RPi
  return value;
}


/////////////////////////////////////////////////
void spi_MCP_io(int ballpark, int page)
{     
	int  addr;
	int  value;
	int  data;
	int  opcode;
	int spi_command;
	char TBUFF[3];
	char RBUFF[3];
	//addr=(ballpark<<4)|(page);
	opcode=0x40;
        addr=0X00;
	data=0X00;

	// First set up IO direction
	TBUFF[0] = opcode;
	TBUFF[1] = addr;
	TBUFF[2] = data;
	bcm2835_spi_transfernb(TBUFF,RBUFF,3);
	// Now disable Sequential Mode
	addr=0x05;
	data=0X22;
	TBUFF[0] = opcode;
	TBUFF[1] = addr;
	TBUFF[2] = data;
	bcm2835_spi_transfernb(TBUFF,RBUFF,3);
	// enable pull up resistors
	addr=0x06;
	data=0XFF;
	TBUFF[0] = opcode;
	TBUFF[1] = addr;
	TBUFF[2] = data;

	bcm2835_spi_transfernb(TBUFF,RBUFF,3);
	// Now Write Ballpak and Page to OLAT
	addr=0X0A;
	data=((ballpark<<4)&0XFF)|(page&0XFF);
	TBUFF[0] = opcode;
	TBUFF[1] = addr;
	TBUFF[2] = data;
	printf("\nTBUFF[2] = %x\n",TBUFF[2]);
        bcm2835_spi_transfernb(TBUFF,RBUFF,3);
	// now do a read
	char BUFFR[2];
	char BUFFT[2];
	opcode=0X41;
	addr=0X09;
	data = 0X01;
        TBUFF[0] = opcode;
	TBUFF[1] = addr;
	TBUFF[2] = data;
	bcm2835_spi_transfernb(TBUFF,RBUFF,3);
	printf("\nRBUFF[0] = %x\n",RBUFF[0]);
	printf("RBUFF[1] = %x\n",RBUFF[1]);
	printf("RBUFF[2] = %x\n",RBUFF[2]);
}


//////////////////////////////////////////////////
int spi_NexyDDMTD_io(int addr, int value)

{
  const int num_Bytes = 8; 
  char cmd[num_Bytes], data[num_Bytes];
  // int result;

  // char is 8 bits
  // int used as 32bits

  int spi_read, spi_auto_inc, spi_addr, spi_command;

  // Create the 32-bit command word.
  spi_command = (addr<<16)|(value & 0xFFFF);
  cmd[0] = (spi_command >> 24)&(0xFF);
  cmd[1] = (spi_command >> 16)&(0xFF);
  cmd[2] = (spi_command >>  8)&(0xFF);
  cmd[3] = (spi_command      )&(0xFF);




  // Send the command.

  bcm2835_spi_transfernb(cmd, data, num_Bytes);


  int output;
  output = data[4]<<24|data[5]<<16|data[6]<<8|data[7];
    // print_bits(32,output);
  // fprintf(stderr,"value = %04d\n",output);
  return output;
  // for (int i=0; i< num_Bytes; i=i+2)
  // {
  //   print_bits(16,data[0+i]<<8|data[1+i]);
  //   fprintf(stderr,"value = %04d\n",(int)(data[0+i]<<8|data[1+i]));
  // }

//
//
//   bcm2835_spi_transfernb(cmd, data, 4);
//
//
// we need to cast it to a 64 bit integer
// (uint64_t)(cmd[0])<<24|cmd[1]<<16|cmd[2]<<8|cmd[3]
//   print_bits(32,(cmd[0])<<24|cmd[1]<<16|cmd[2]<<8|cmd[3]);
//   print_bits(32, data[0]<<24|data[1]<<16|data[2]<<8|data[3]);
//
//
//
//
//
//
//   result = (data[4]<<24)| (data[3]<<16)| (data[2]<<8) | (data[1]);
//   printf("value = 0x%04x,0x%04x,0x%04x,0x%04x\n",(int)data[3],(int)data[2],(int)data[1],(int)data[0]);
//     fprintf(stderr,"value = %04d\n",(int)cmd[2]);
//
//
//
//   result = (data[0]<<8) | data[1];
//   return (result);
}
