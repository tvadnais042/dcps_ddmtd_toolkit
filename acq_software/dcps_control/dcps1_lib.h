// DCPS 1.0 Library

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


int construct_packet_dcps1(char* cmd_buf, int delay_step); // Construct the packet for DCPS version 1
void set_dcps_delay_dcps1(int delay); //Set DCPS Delay version 1
int select_channel_dcps1(int channel); //Select Channel for DCPS version 1

