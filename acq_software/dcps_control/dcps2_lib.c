#include "dcps2_lib.h"





int construct_packet_dcps2(char* cmd_buf,uint fine_delay_step,uint coarse_delay)
{


    memset(cmd_buf, 0, NUM_BYTES);
    uint val = 0;
    for(int i=0; i< 5; i++)
    {
        val = 1&(coarse_delay>>i);
        printf("%u bit is  %u \n",i+1,val);
        set_value_bit(cmd_buf,i,val); //C1
        set_value_bit(cmd_buf,i+5,0b1&~(val)); //L1
        set_value_bit(cmd_buf,i+10,val); //C2
        set_value_bit(cmd_buf,i+15,0b1&~(val)); //L2


    }


    for(int i=0; i< 54; i++)
        {
            if(i < fine_delay_step)
            {   
                //Activate
                set_value_bit(cmd_buf,i+20,1); //C
                set_value_bit(cmd_buf,i+74,0); //L
            }
            else
            {
                //Deactivate
                set_value_bit(cmd_buf,i+20,0); //C
                set_value_bit(cmd_buf,i+74,1); //L
            }

        }    
        return 0;
}

void set_dcps_delay_dcps2(int fine_delay,int coarse_delay)
{
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0); 
    bcm2835_spi_chipSelect(BCM2835_SPI_CS1); // Changing to FPGA
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);	// Value of CS when active


    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_LSBFIRST);
    // bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_set_speed_hz(100000);
    // bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);    
    // printf("%u SPI Speed \n",BCM2835_SPI_CLOCK_DIVIDER_65536);




    usleep(10000);

    char*  cmd_buf  = malloc(NUM_BYTES);
    char*  rev_cmd_buf  = malloc(NUM_BYTES);
    char*  data_buf = malloc(NUM_BYTES);

    construct_packet_dcps2(cmd_buf,fine_delay,coarse_delay);
    print_nWords(cmd_buf,NUM_BYTES,1);
    // print_bitwise(cmd_buf);
    reverse_bits(cmd_buf,rev_cmd_buf,NUM_BYTES*8);
    // print_nWords(rev_cmd_buf,NUM_BYTES,1);
   
   for (int i=0; i< 1; i++)
   {
    printf("cmd_buf Forward \n");
    bcm2835_spi_transfernb(cmd_buf, data_buf, NUM_BYTES);
    // printf("cmd_buf Reversed \n");
    // bcm2835_spi_transfernb(rev_cmd_buf, data_buf, NUM_BYTES);
    usleep(10000);
   }
   


    free(data_buf);
    free(cmd_buf);
    free(rev_cmd_buf);

}

int select_channel_dcps2(int channel)
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


    case 0:
        // Selecting Fiber 5
        digitalWrite (DAT0, 0) ;       // On
        digitalWrite (DAT1, 0) ;       // On
        digitalWrite (DAT2, 0) ;       // On
        digitalWrite (DAT3, 0) ;       // On
        printf("Selected Fiber 0 edited\n");
        break;

    case 1:
        // Selecting Fiber 1
        digitalWrite (DAT0, 1) ;       // On
        digitalWrite (DAT1, 0) ;       // On
        digitalWrite (DAT2, 0) ;       // On
        digitalWrite (DAT3, 0) ;       // On
        printf("Selected Fiber 1 edited\n");
        break;

    case 2:
        // Selecting Fiber 2
        digitalWrite (DAT0, 0) ;       // On
        digitalWrite (DAT1, 1) ;       // On
        digitalWrite (DAT2, 0) ;       // On
        digitalWrite (DAT3, 0) ;       // On
        printf("Selected Fiber 2 edited\n");
        break;

    case 3:
        // Selecting Fiber 3
        digitalWrite (DAT0, 1) ;       // On
        digitalWrite (DAT1, 1) ;       // On
        digitalWrite (DAT2, 0) ;       // On
        digitalWrite (DAT3, 0) ;       // On
        printf("Selected Fiber 3 edited\n");
        break;

    case 4:
        // Selecting Fiber 4
        digitalWrite (DAT0, 0) ;       // On
        digitalWrite (DAT1, 0) ;       // On
        digitalWrite (DAT2, 1) ;       // On
        digitalWrite (DAT3, 0) ;       // On
        printf("Selected Fiber 4 edited\n");
        break;
    case 5:
        // Selecting Fiber 5
        digitalWrite (DAT0, 1) ;       // On
        digitalWrite (DAT1, 0) ;       // On
        digitalWrite (DAT2, 1) ;       // On
        digitalWrite (DAT3, 0) ;       // On
        printf("Selected Fiber 5 edited\n");
        break;

    // case 6:
    //     // Selecting Fiber 6
    //     digitalWrite (DAT0, 0) ;       // On
    //     digitalWrite (DAT1, 1) ;       // On
    //     digitalWrite (DAT2, 1) ;       // On
    //     digitalWrite (DAT3, 0) ;       // On
    //     printf("Selected Fiber 6 edited\n");
    //     break;


    // case 7:
    //     // Selecting Fiber 7 NC
    //     digitalWrite (DAT0, 1) ;       // On
    //     digitalWrite (DAT1, 1) ;       // On
    //     digitalWrite (DAT2, 1) ;       // On
    //     digitalWrite (DAT3, 0) ;       // On
    //     printf("Selected Fiber 7 edited\n");
    //     break;

    // case 10:
    //     // // // Selecting Fiber 10
    //     digitalWrite (DAT0, 0) ;       // On
    //     digitalWrite (DAT1, 1) ;       // On
    //     digitalWrite (DAT2, 0) ;       // On
    //     digitalWrite (DAT3, 1) ;       // On
    //     printf("Selected Fiber 10 \n");
    //     break;
    
    default:
        printf("Invalid Fibre selected => %u \n",channel);
        return -1;
        break;
    }

    return 0;


}




void print_bitwise(char* cmd_buf){
    int total = 0;
    for(int i=0; i< NUM_BYTES;i++)
    {
        for(int j=0; j<8;j++ )
        {
            printf("%03u-->%u \n\n",total+1,(uint)(0b1&(cmd_buf[i]>>j)));
            total = total +1;
        }
    }
}