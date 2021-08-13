#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>



#define BYTES_PER_PAGE 256 // For Nexys Video
#define MAX_BYTES 32000000
#define MAX_TRIALS 3  //Changed from 5 to 2

#define CHIP_ID 0x10219 // CHIP ID for Nexys Video



#include "spi_common.h"
#include "Si5344_REG.h"






#include "NexysDDMTD.h"

// Send a 32-bit spi_write command, which writes 16 bits into the address and returns the Result



int main()
{


	 
  // Set Ballpark and Page on IO interface
  int ballpark;
  int page;
  ballpark=(0x04);
  page=(0x07);
  init_addr();
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);     // 6 MHz
  spi_MCP_io(ballpark, page);

  // Now we are talking to the chosen PLL	
  // Startup the SPI interface on the Pi.

  bcm2835_spi_chipSelect(BCM2835_SPI_CS1); // Changing to
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);	// Value of CS when active
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);     // 6 MHz

  // spi_si5344_write(0x0B24,0xC0);
  // printf("0x%02x is the value read\n",spi_si5344_read(0x0B24));

  // unsigned int microseconds = 100000;

  for (int i=0;i< SI5344_REVD_REG_CONFIG_NUM_REGS; i=i+1)
  {

    spi_si5344_write(si5344_revd_registers[i].address,si5344_revd_registers[i].value);
    //Making sure these are written properly
    if (spi_si5344_read(si5344_revd_registers[i].address) != si5344_revd_registers[i].value) printf("address = 0x%04x, value = 0x%02x ; Value returned = 0x%02x   \n",si5344_revd_registers[i].address,si5344_revd_registers[i].value ,spi_si5344_read(si5344_revd_registers[i].address) );
  }

  // spi_NexyDDMTD_io(0x101,0x1);
  // bcm2835_spi_chipSelect(BCM2835_SPI_CS1); // Changing to
  // bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);	// Value of CS when active
  //
  // set2page(0x05);
  // read4addr(0x1);

  end_spi();


  return(0);

}// Main ends here
