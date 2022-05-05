
#include <wiringPi.h>
#define BCM2835_NO_DELAY_COMPATIBILITY

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>


#include "spi_common.h"
#include "NexysDDMTD.h"
// #include "dcps1_lib.h"
#include "dcps2_lib.h"










int main(int argc, char** argv)
{
    int fine_delay,coarse_delay;
    int channel;
    if(argc == 4)
        {
            fine_delay=atoi(argv[1]);
            coarse_delay=atoi(argv[2]);
            channel=atoi(argv[3]);

            printf("%u fine delay step selected \n",fine_delay);
            printf("%u coarse delay step selected \n",coarse_delay);

            printf("%u channel selected \n",channel);
            if(fine_delay > 32 ) {printf(" Please select a value below 32\n"); return 0;}
        } 
    else
        {
            printf("Please supply number of fine delay steps as 1st argument, coarse delay step as 2nd,  channel as 3rd argument\n");
            return 0;
        }


    if(select_channel_dcps2(channel)==-1){
        printf("Exiting with GPIO issue \n");
        return 0;
    }

    // Set Ballpark and Page on IO interface
    int ballpark;
    int page;
    ballpark=(0x00); // For FPGA
    page=(0x00); // Doesn't matter
    init_addr();
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32);    
    spi_MCP_io(ballpark, page); //Setting Ballpark

    usleep(100);
    set_dcps_delay_dcps2(fine_delay,coarse_delay); 
    end_spi();
    return 0;
}






