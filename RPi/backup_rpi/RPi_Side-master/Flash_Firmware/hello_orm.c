/*

gcc -O hello_orm.c orm.c spi_common.c -l bcm2835 -o hello_orm.exe

*/

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>

#include "orm.h"
#include "spi_common.h"

int main()
{
  // Startup the SPI interface on the Pi.
  init_spi();

  // Test the constant registers, for debug.
  int constant0, constant1;
  constant0 = ORM_get_constant0();
  constant1 = ORM_get_constant1();
  fprintf(stderr,"constant = 0x%04x 0x%04x\n",
	  (int)constant1, (int)constant0);
  
  // Test the dummy registers, for debug.
  int dummy0, dummy1;
  ORM_put_dummy0(0x0005);
  ORM_put_dummy1(0xDEAD);
  dummy0 = ORM_get_dummy0();
  dummy1 = ORM_get_dummy1();
  fprintf(stderr,"dummy = 0x%04x 0x%04x\n",
	  (int)dummy1, (int)dummy0);
  
  end_spi();
  return(0);    
  
}// Main ends here

