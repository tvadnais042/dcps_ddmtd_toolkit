#include <stdio.h>
#include <unistd.h> // for usleep()
#include <stdlib.h>
#include "spi_common.h"
#include <bcm2835.h>

#define VERBOSE1 (0)
#define VERBOSE2 (1)

#define MAX_BITS (128)

#define SCA_AUX_DISABLE (0X12C)
#define SCA_RESETB (0X12D)

#define SCA_ELINK_ENABLE (0X130)
#define SCA_SEND_PACKET1 (0X131)
#define SCA_SEND_PACKET2 (0X132)
#define SCA_SEND_PACKET3 (0X133)

#define SCA_BITS_PACKET0 (0X140)
#define SCA_BITS_PACKET1 (0X141)
#define SCA_BITS_PACKET2 (0X142)
#define SCA_BITS_PACKET3 (0X143)

#define SCA_TX_PACKET0 (0X150)
#define SCA_RX_PACKET0 (0X160)
#define SCA_TX_PACKET1 (0X170)
#define SCA_RX_PACKET1 (0X180)
#define SCA_TX_PACKET2 (0X190)
#define SCA_RX_PACKET2 (0X1A0)
#define SCA_TX_PACKET3 (0X1B0)
#define SCA_RX_PACKET3 (0X1C0)

#define SCA_STATUS  (0x12F)


/*

https://en.wikipedia.org/wiki/High-Level_Data_Link_Control#Synchronous_framing

*/



//Reading Data from the GBT_SCA
void ReadBack(int addr)
{
  printf("Printing From Address 0x%x \n",addr );

  for(int i=0 ; i< 8 ;i++)
  {
    int Data = spi_get_16bits(addr+i);
    print16(Data);
  }
  printf("\n");
  return;
}

// Packet format:
// {SOF,ADRESS,Control:0-7,Transaction ID,Channel,Length,Command,
//  Data,Data,Data,Data,FCS,EOF}

// void spi_put_16bits(int a, int b) {} // for debug

//========================================================================
// Calculate CCITT CRC16. p = x^16 + x^12 + x^5 + x^0
//========================================================================

int calculate_crc(int num_bits, char bit_in[MAX_BITS])
{
  int poly16 = 0x8408;
  int i, crc16;
  crc16 = 0xFFFF;
  for (i=0; i<num_bits; i++) {
    if ((bit_in[i] ^ (crc16&1)) == 1) crc16 = (crc16 >> 1) ^ poly16;
    else crc16 = (crc16>>1);
  }
  crc16 ^= 0xFFFF;
  return(crc16);
}

//========================================================================
// Insert HDLC zeros.
//========================================================================

 int insert_zeros(int num_bits, char bit_in[MAX_BITS], char bit_out[MAX_BITS])
{
  int i, bit_count, one_count;

  // Check num_bits.
  if (num_bits > MAX_BITS) {
    fprintf(stderr,"ERROR: num_bits > MAX_BITS\n");
    return(-1);
  }

  // Initialize.
  for (i=0; i<MAX_BITS; i++) bit_out[i]=0;

  // Insert HDLC zeros.
  bit_count = 0;
  one_count = 0;
  for (i=0; i<num_bits; i++) {
    bit_out[bit_count] = bit_in[i];
    bit_count++;
    if (bit_count >= MAX_BITS) break;
    one_count++;
    if (bit_in[i] == 0) one_count = 0;
    if (one_count >= 5) {
      one_count = 0;
      bit_out[bit_count] = 0;
      bit_count++;
      if (bit_count >= MAX_BITS) break;
    }
  }

  // Check num_bits.
  if (num_bits > MAX_BITS) {
    fprintf(stderr,"ERROR: num_bits > MAX_BITS\n");
    return(-1);
  }

  return(bit_count);
}

//========================================================================
// Print a partial packet, for debug.
//========================================================================

void print_bits(int num_bits, char bit_in[MAX_BITS])
{
  int i, byte, byte_count, bit_count;

  fprintf(stderr,"num_bits = %d\n", num_bits);

  fprintf(stderr,"LSB-to-MSB: ");
  for (i=0; i<num_bits; i++) fprintf(stderr,"%d",(int)bit_in[i]);
  fprintf(stderr,"\n");

  fprintf(stderr,"MSB-to-LSB: ");
  for (i=num_bits-1; i>=0; i--) fprintf(stderr,"%d",(int)bit_in[i]);
  fprintf(stderr,"\n");

  byte_count = 0;
  bit_count = 0;
  byte = 0;
  for (i=0; i<num_bits; i++) {
    byte |= bit_in[i] << bit_count;
    bit_count++;
    if (bit_count == 8) {
      fprintf(stderr,"byte[%2d] = 0x%02x;\n", (int)byte_count, (int)byte);
      byte_count++;
      bit_count = 0;
      byte = 0;
    }
  }
  if ((bit_count > 0) && (bit_count < 8)) {
    fprintf(stderr,"byte[%2d] = 0x%02x;\n", (int)byte_count, (int)byte);
  }
  fprintf(stderr,"\n");

  fprintf(stderr,"\n");
}

//========================================================================
// Blink GBT-SCA LED.
//========================================================================

void blink_led()
{

  int i, j, indx, word_count, bit_count, word;
  char byte[MAX_BITS]; // yeah, too big

  char payld_idle[MAX_BITS];
  char pckt_idle[MAX_BITS];
  int bits_idle;

  char payld_gpio_dir[MAX_BITS];
  char payld2_gpio_dir[MAX_BITS];
  char pckt_gpio_dir[MAX_BITS];
  int bits_gpio_dir;
  int crc_gpio_dir;

  char payld_gpio_on[MAX_BITS];
  char payld2_gpio_on[MAX_BITS];
  char pckt_gpio_on[MAX_BITS];
  int bits_gpio_on;
  int crc_gpio_on;

  char payld_gpio_off[MAX_BITS];
  char payld2_gpio_off[MAX_BITS];
  char pckt_gpio_off[MAX_BITS];
  int bits_gpio_off;
  int crc_gpio_off;

  //========================================================================
  // Construct payloads.
  //========================================================================


// Packet format:
// {ADRESS,Control:0-7,CHAN,Transaction ID,Length,Command,
//  Data,Data,Data,Data,FCS,EOF}

  // // Construct "direction" payload.
  // // {0X00,0X00,0X02,0,4,0X20,0,0,0,0X03}
  // byte[0] = 0x00;
  // byte[1] = 0x00;
  // byte[2] = 0x02;
  // byte[3] = 0x02;
  // byte[4] = 0x04;
  // byte[5] = 0x20;
  // byte[6] = 0x08;
  // byte[7] = 0x08;
  // byte[8] = 0x08;
  // byte[9] = 0x08;
  // indx = 0;
  // for (j=0; j<10; j++) {
  //   for (i=0; i<8; i++)
  //   {
  //     payld_gpio_dir[indx++] = (byte[j]>>i)&1;
  //   }
  // }
  // bits_gpio_dir = indx;



  // Construct "reset" payload.
 byte[0] = 0x00; // address
 byte[1] = 0x8F; // control
 indx = 0;
 for (j=0; j<2; j++) {
   for (i=0; i<8; i++) payld_gpio_dir[indx++] = (byte[j]>>i)&1;
 }
 bits_gpio_dir = indx;


  // Construct "on" payload.
  // {0,0,2,2,4,0X10,0x08,0,0,0}
  byte[0] = 0x00;
  byte[1] = 0x00;
  byte[2] = 0x02;
  byte[3] = 0x02;
  byte[4] = 0x04;
  byte[5] = 0x10;
  byte[6] = 0x08;
  byte[7] = 0x08;
  byte[8] = 0x08;
  byte[9] = 0x08;
  indx = 0;
  for (j=0; j<10; j++) {
    for (i=0; i<8; i++) payld_gpio_on[indx++] = (byte[j]>>i)&1;
  };
  bits_gpio_on = indx;

  // Construct "off" payload.
  // {0,0,2,2,4,0X10,0x00,0,0,0}
  byte[0] = 0x00;
  byte[1] = 0x00;
  byte[2] = 0x02;
  byte[3] = 0x02;
  byte[4] = 0x04;
  byte[5] = 0x10;
  byte[6] = 0x00;
  byte[7] = 0x00;
  byte[8] = 0x00;
  byte[9] = 0x00;
  indx = 0;
  for (j=0; j<10; j++) {
    for (i=0; i<8; i++) payld_gpio_off[indx++] = (byte[j]>>i)&1;
  }
  bits_gpio_off = indx;

  //========================================================================
  // Construct CRCs.
  //========================================================================

  // Construct "direction" crc.
  crc_gpio_dir =  calculate_crc(bits_gpio_dir, payld_gpio_dir);

  // Construct "on" crc.
  crc_gpio_on =  calculate_crc(bits_gpio_on, payld_gpio_on);

  // Construct "off" crc.
  crc_gpio_off =  calculate_crc(bits_gpio_off, payld_gpio_off);

  //========================================================================
  // Construct payloads, including CRC values.
  //========================================================================

  // Modify "direction" payload; {payload, crc}
  for (i=0; i<16; i++) payld_gpio_dir[bits_gpio_dir+i] = (crc_gpio_dir>>i)&1;
  bits_gpio_dir += 16;

  // Modify "on" payload; {payload, crc}
  for (i=0; i<16; i++) payld_gpio_on[bits_gpio_on+i] = (crc_gpio_on>>i)&1;
  bits_gpio_on += 16;

  // Modify "off" payload; {payload, crc}
  for (i=0; i<16; i++) payld_gpio_off[bits_gpio_off+i] = (crc_gpio_off>>i)&1;
  bits_gpio_off += 16;

  //========================================================================
  // Insert HDLC zeros.
  //========================================================================

  // Insert "direction" zeros.
  if (VERBOSE1) fprintf(stderr,"bits_gpio_dir=%d, before HDLC\n",bits_gpio_dir);
  if (VERBOSE2) print_bits(bits_gpio_dir, payld_gpio_dir);
  bits_gpio_dir =  insert_zeros(bits_gpio_dir,
				payld_gpio_dir,
				payld2_gpio_dir);
  if (VERBOSE1) fprintf(stderr,"bits_gpio_dir=%d, after HDLC\n",bits_gpio_dir);
  if (VERBOSE2) print_bits(bits_gpio_dir, payld2_gpio_dir);

  // Insert "on" zeros.
  if (VERBOSE1) fprintf(stderr,"bits_gpio_on=%d, before HDLC\n",bits_gpio_on);
  if (VERBOSE2) print_bits(bits_gpio_on, payld_gpio_on);
  bits_gpio_on =  insert_zeros(bits_gpio_on,
			       payld_gpio_on,
			       payld2_gpio_on);
  if (VERBOSE1) fprintf(stderr,"bits_gpio_on=%d, after HDLC\n",bits_gpio_on);
  if (VERBOSE2) print_bits(bits_gpio_on, payld2_gpio_on);

  // Insert "off" zeros.
  if (VERBOSE1) fprintf(stderr,"bits_gpio_off=%d, before HDLC\n",bits_gpio_off);
  if (VERBOSE2) print_bits(bits_gpio_off, payld_gpio_off);
  bits_gpio_off =  insert_zeros(bits_gpio_off,
				payld_gpio_off,
				payld2_gpio_off);
  if (VERBOSE1) fprintf(stderr,"bits_gpio_off=%d, after HDLC\n",bits_gpio_off);
  if (VERBOSE2) print_bits(bits_gpio_off, payld2_gpio_off);

  //========================================================================
  // Construct packets.
  //========================================================================

  // Construct "idle" packet: {0XFE, 0XFE}
  byte[0] = 0xFE;
  byte[1] = 0xFE;
  indx = 0;
  for (j=0; j<2; j++) {
    for (i=0; i<8; i++) pckt_idle[indx++] = (byte[j]>>i)&1;
  }
  bits_idle = indx;
  if (VERBOSE1) fprintf(stderr,"bits_idle=%d, full packet\n",bits_idle);
  if (VERBOSE2) print_bits(bits_idle, pckt_idle);

  // Construct "direction" packet: {0X7E, payload2, 0X7E}
  byte[0] = 0x7E;
  indx = 0;
  for (i=0; i<8; i++) pckt_gpio_dir[indx++] = (byte[0]>>i)&1;
  for (i=0; i<bits_gpio_dir; i++) pckt_gpio_dir[indx++] = payld2_gpio_dir[i];
  for (i=0; i<8; i++) pckt_gpio_dir[indx++] = (byte[0]>>i)&1;
  bits_gpio_dir = indx;
  printf("RESET PACKET\n");
  if (VERBOSE1) fprintf(stderr,"bits_gpio_dir=%d, full packet\n",bits_gpio_dir);
  if (VERBOSE2) print_bits(bits_gpio_dir, pckt_gpio_dir);









  // Construct "on" packet: {0X7E, payload2, 0X7E}
  byte[0] = 0x7E;
  indx = 0;
  for (i=0; i<8; i++) pckt_gpio_on[indx++] = (byte[0]>>i)&1;
  for (i=0; i<bits_gpio_on; i++) pckt_gpio_on[indx++] = payld2_gpio_on[i];
  for (i=0; i<8; i++) pckt_gpio_on[indx++] = (byte[0]>>i)&1;
  bits_gpio_on = indx;
  if (VERBOSE1) fprintf(stderr,"bits_gpio_on=%d, full packet\n",bits_gpio_on);
  if (VERBOSE2) print_bits(bits_gpio_on, pckt_gpio_on);

  // Construct "off" packet: {0X7E, payload2, 0X7E}
  byte[0] = 0x7E;
  indx = 0;
  for (i=0; i<8; i++) pckt_gpio_off[indx++] = (byte[0]>>i)&1;
  for (i=0; i<bits_gpio_off; i++) pckt_gpio_off[indx++] = payld2_gpio_off[i];
  for (i=0; i<8; i++) pckt_gpio_off[indx++] = (byte[0]>>i)&1;
  bits_gpio_off = indx;
  if (VERBOSE1) fprintf(stderr,"bits_gpio_off=%d, full_packet\n",bits_gpio_off);
  if (VERBOSE2) print_bits(bits_gpio_off, pckt_gpio_off);

  //========================================================================
  // Write packets into firmware regs.
  //========================================================================

  // Write "idle" to REG0 (with number of bits).
  word_count = 0;
  bit_count = 0;
  word = 0;
  for (i=0; i<bits_idle; i++) {
    word |= pckt_idle[i] << bit_count++;
    if (bit_count == 16) {
      spi_put_16bits(SCA_TX_PACKET0 + word_count, word);
      word_count++;
      bit_count = 0;
      word = 0;
    }
  }
  if (bit_count != 16) {
    spi_put_16bits(SCA_TX_PACKET0 + word_count, word);
  }


  // Write "direction" to REG1 (with number of bits).
  word_count = 0;
  bit_count = 0;
  word = 0;
  for (i=0; i<bits_gpio_dir; i++) {
    word |= pckt_gpio_dir[i] << bit_count++;
    if (bit_count == 16) {
      spi_put_16bits(SCA_TX_PACKET1 + word_count, word);
      word_count++;
      bit_count = 0;
      word = 0;
    }
  }
  if (bit_count != 16) {
    spi_put_16bits(SCA_TX_PACKET1 + word_count, word);
  }

  // Write "on" to REG2 (with number of bits).
  word_count = 0;
  bit_count = 0;
  word = 0;
  for (i=0; i<bits_gpio_on; i++) {
    word |= pckt_gpio_on[i] << bit_count++;
    if (bit_count == 16) {
      spi_put_16bits(SCA_TX_PACKET2 + word_count, word);
      word_count++;
      bit_count = 0;
      word = 0;
    }
  }
  if (bit_count != 16) {
    spi_put_16bits(SCA_TX_PACKET2 + word_count, word);
  }

  // Write "off" to REG3 (with number of bits).
  word_count = 0;
  bit_count = 0;
  word = 0;
  for (i=0; i<bits_gpio_off; i++) {
    word |= pckt_gpio_off[i] << bit_count++;
    if (bit_count == 16) {
      spi_put_16bits(SCA_TX_PACKET3 + word_count, word);
      word_count++;
      bit_count = 0;
      word = 0;
    }
  }
  if (bit_count != 16) {
    spi_put_16bits(SCA_TX_PACKET3 + word_count, word);
  }

  //========================================================================
  // Write bit counts into firmware registers.
  //========================================================================

  spi_put_16bits(SCA_BITS_PACKET0, bits_idle - 1);
  spi_put_16bits(SCA_BITS_PACKET1, bits_gpio_dir - 1);
  spi_put_16bits(SCA_BITS_PACKET2, bits_gpio_on - 1);
  spi_put_16bits(SCA_BITS_PACKET3, bits_gpio_off - 1);

  //========================================================================
  // Misc. commands for initilaization.
  //========================================================================

  spi_put_16bits(SCA_AUX_DISABLE, 1);
  spi_put_16bits(SCA_RESETB, 0);
  spi_put_16bits(SCA_RESETB, 1);
  spi_put_16bits(SCA_ELINK_ENABLE, 1);
  ReadBack(SCA_RX_PACKET0);

  //========================================================================
  // Start sending packets to GBT-SCA.
  //========================================================================

  // Send packet 1. (gpio direction)
  spi_put_16bits(SCA_SEND_PACKET1, 1);

  //========================================================================
  // Infinite loop.
  //========================================================================
  while (1) {
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    // Send packet 2. (led on)
    spi_put_16bits(SCA_SEND_PACKET1, 1);
    usleep(500000); // Sleep 500 milliseconds.
    ReadBack(SCA_STATUS);

    // spi_put_16bits(SCA_SEND_PACKET2, 1);
    usleep(500000); // Sleep 500 milliseconds.
    // ReadBack(SCA_STATUS);
    //
    //
    //
    ReadBack(SCA_RX_PACKET1);
    // ReadBack(SCA_RX_PACKET2);
    //
    // ReadBack(SCA_STATUS);
    //
    //
    //
    //
    // // Send packet 3. (led off)
    // spi_put_16bits(SCA_SEND_PACKET3, 1);
    // usleep(500000); // Sleep 500 milliseconds.
    // ReadBack(SCA_RX_PACKET1);
    // ReadBack(SCA_RX_PACKET3);
    //
    // ReadBack(SCA_STATUS);
    //
    // printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    // // break;

  }
}

//========================================================================
// Check the CRC implementation, for debug.
//========================================================================

void check_crc()
{
  /*
    https://www.itu.int/rec/dologin_pub.asp?lang=e&id=T-REC-X.25-199610-I!!PDF-E&type=items
  */

  char byte[64];
  char bits[64*8];
  int i, crc16;

  byte[0] = 0x03; byte[1] = 0x3F; // 0xEC5B, Example I1.1 on p.153
  // byte[0] = 0x01; byte[1] = 0x73; // 0x5783, Example I1.2 on p.153
  // byte[0] = 0x01; byte[1] = 0x3F; // 0xDFEB, Example I2.1 on p.153
  // byte[0] = 0x03; byte[1] = 0x73; // 0x6433, Example I2.1 on p.153

  for (i=0; i<8; i++) bits[0+i] = (byte[0]>>i) & 1;
  for (i=0; i<8; i++) bits[8+i] = (byte[1]>>i) & 1;

  crc16 = calculate_crc(16, bits);
  fprintf(stderr,"crc is %04x\n",(int)crc16);
}

//========================================================================
// Main program.
//========================================================================

void main()
{
  // check_crc();

  init_spi();

  blink_led();
  end_spi();


}
