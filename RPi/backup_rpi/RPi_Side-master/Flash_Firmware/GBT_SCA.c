//
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <bcm2835.h>
#include "spi_common.h"




int main() {
    // Setting up SPI
    init_spi();
    // Reading chip ID so we know everything is working OK
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);		// CS0 is for talking to eht Peripheral interface...

    for (int i=0; i<8 ; i++) spi_put_16bits(0x170 + i,0xF000);
    spi_put_16bits(0X131, 1);
    for (int i=0; i<8 ; i++) print16(spi_get_16bits(0x180 + i)); printf("\n");


    // Closing Connection
    end_spi();
    return 0;
}
