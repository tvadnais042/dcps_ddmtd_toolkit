
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





#define MAX_BYTES 32000000
#define MAX_TRIALS 3  //Changed from 5 to 2

#define DAT0 27 // 16 For Nexys Video
#define DAT1 0  // 17 For Nexys Video
#define DAT2 1  // 18 For Nexys Video
#define DAT3 24 // 19 For Nexys Video

#define R_OUTD 0
#define R_OUTG 1
#define R_IND 0
#define R_ING 1





#define NUM_BYTES 256/8
int construct_packet(char* cmd_buf, int delay_step);
void set_dcps_delay(int delay);
int select_channel(int channel);




int main(int argc, char** argv)
{
    int delay_step;
    int channel;
    if(argc == 3)
        {
            delay_step=atoi(argv[1]);
            channel=atoi(argv[2]);

            printf("%u delay step selected \n",delay_step);
            printf("%u channel selected \n",channel);
            if(delay_step >66 ) {printf(" Please select a value below 66\n"); return 0;}
        } 
    else
        {
            
            printf("Please supply number of delay steps as 1st argument and channel as second argument\n");
            return 0;
        }

         

    if(select_channel(channel)==-1) return 0;


    // Set Ballpark and Page on IO interface
    int ballpark;
    int page;
    ballpark=(0x00); // For FPGA
    page=(0x00); // Doesn't matter
    init_addr();
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);    
    spi_MCP_io(ballpark, page); //Setting Ballpark


    usleep(100);
    set_dcps_delay(delay_step);

 


    end_spi();
    return 0;
}



int construct_packet(char* cmd_buf, int delay_step)
{
     memset(cmd_buf, 0,NUM_BYTES );
        for(int i=0; i< 66; i++)
        {
            if(i < delay_step)
            {
                set_value_bit(cmd_buf,i,0);
                set_value_bit(cmd_buf,i+66,1); 
            }
            else
            {
                set_value_bit(cmd_buf,i,1);
                set_value_bit(cmd_buf,i+66,0); 
            }

            
        }    
        //Final MSB settings
        set_value_bit(cmd_buf,255,R_OUTD);
        set_value_bit(cmd_buf,254,R_OUTG);
        set_value_bit(cmd_buf,253,R_IND);
        set_value_bit(cmd_buf,252,R_ING);
        return 0;
}



void set_dcps_delay(int delay)
{
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0); 
    bcm2835_spi_chipSelect(BCM2835_SPI_CS1); // Changing to FPGA
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);	// Value of CS when active


    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_LSBFIRST);
    // bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);

    bcm2835_spi_set_speed_hz(100000);



    usleep(100);

    char*  cmd_buf  = malloc(NUM_BYTES);
    char*  rev_cmd_buf  = malloc(NUM_BYTES);
    char*  data_buf = malloc(NUM_BYTES);

    construct_packet(cmd_buf,delay);
    reverse_bits(cmd_buf,rev_cmd_buf,NUM_BYTES*8);
    bcm2835_spi_transfernb(rev_cmd_buf, data_buf, NUM_BYTES);

    free(data_buf);
    free(cmd_buf);
    free(rev_cmd_buf);
    // print_nWords(rev_cmd_buf,NUM_BYTES,1);

}



int select_channel(int channel)
{

    if (wiringPiSetup () == -1)
    return 1 ;

    //Setting the correct GPIO
    pinMode (DAT0, OUTPUT) ;        
    pinMode (DAT1, OUTPUT) ;        
    pinMode (DAT2, OUTPUT) ;        
    pinMode (DAT3, OUTPUT) ;

    //Selecting correct channel


    switch (channel)
    {
    case 5:
        // Selecting Fiber 5
        digitalWrite (DAT0, 0) ;       // On
        digitalWrite (DAT1, 0) ;       // On
        digitalWrite (DAT2, 1) ;       // On
        digitalWrite (DAT3, 0) ;       // On
        printf("Selected Fiber 5\n");
        break;

    case 10:
        // // // Selecting Fiber 10
        digitalWrite (DAT0, 0) ;       // On
        digitalWrite (DAT1, 1) ;       // On
        digitalWrite (DAT2, 0) ;       // On
        digitalWrite (DAT3, 1) ;       // On
        printf("Selected Fiber 10 \n");
        break;
    
    default:
        printf("Invalid Fibre selected => %u \n",channel);
        return -1;
        break;
    }

    return 0;

    // // // Selecting Fiber 5
    // // digitalWrite (DAT0, 0) ;       // On
    // // digitalWrite (DAT1, 0) ;       // On
    // // digitalWrite (DAT2, 1) ;       // On
    // // digitalWrite (DAT3, 0) ;       // On
    // // printf("Selected Fiber 5\n");

    // // // // Selecting Fiber 10
    // digitalWrite (DAT0, 0) ;       // On
    // digitalWrite (DAT1, 1) ;       // On
    // digitalWrite (DAT2, 0) ;       // On
    // digitalWrite (DAT3, 1) ;       // On
    // printf("Selected Fiber 10 \n");


    // //   // // Selecting Fiber 11
    // // digitalWrite (DAT0, 1) ;       // On
    // // digitalWrite (DAT1, 0) ;       // On
    // // digitalWrite (DAT2, 0) ;       // On
    // // digitalWrite (DAT3, 1) ;       // On
    // // printf("Selected Fiber 11 \n");

}
