#include "dcps1_lib.h"





int construct_packet_dcps1(char* cmd_buf, int delay_step)
{
     memset(cmd_buf, 0, NUM_BYTES);
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

void set_dcps_delay_dcps1(int delay)
{
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0); 
    bcm2835_spi_chipSelect(BCM2835_SPI_CS1); // Changing to FPGA
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);	// Value of CS when active


    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_LSBFIRST);
    // bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_set_speed_hz(100000);
    // bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);    
    // printf("%u SPI Speed \n",BCM2835_SPI_CLOCK_DIVIDER_65536);




    usleep(100);

    char*  cmd_buf  = malloc(NUM_BYTES);
    char*  rev_cmd_buf  = malloc(NUM_BYTES);
    char*  data_buf = malloc(NUM_BYTES);

    construct_packet_dcps1(cmd_buf,delay);
    print_nWords(cmd_buf,NUM_BYTES,1);
    reverse_bits(cmd_buf,rev_cmd_buf,NUM_BYTES*8);
    // print_nWords(rev_cmd_buf,NUM_BYTES,1);

    bcm2835_spi_transfernb(rev_cmd_buf, data_buf, NUM_BYTES);

    free(data_buf);
    free(cmd_buf);
    free(rev_cmd_buf);

}

int select_channel_dcps1(int channel)
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


}
