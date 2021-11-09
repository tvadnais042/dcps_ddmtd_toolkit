`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/12/2020 08:37:30 PM
// Design Name: 
// Module Name: main
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module main(
    input wire CLK_REF_P,
    input wire CLK_REF_N,
    
    
    // DDMTD Reference beak clocks 
    input wire BEAT_REF1_N,
    input wire BEAT_REF1_P,
    input wire BEAT_REF2_N,
    input wire BEAT_REF2_P,    
    
    // input wire BEAT0_Q1_P,
    // input wire BEAT0_Q1_N,
    // input wire BEAT0_Q2_P,
    // input wire BEAT0_Q2_N,
    // input wire BEAT1_Q1_P,
    // input wire BEAT1_Q1_N,
    // input wire BEAT1_Q2_P,
    // input wire BEAT1_Q2_N

    input wire AQ0_P,
    input wire AQ0_N,
    input wire AQ1_P,
    input wire AQ1_N,
    input wire AQ2_P,
    input wire AQ2_N,
    input wire AQ3_P,
    input wire AQ3_N,
    
    input wire BQ0_P,
    input wire BQ0_N,
    input wire BQ1_P,
    input wire BQ1_N,
    input wire BQ2_P,
    input wire BQ2_N,
    input wire BQ3_P,
    input wire BQ3_N,

    input wire CQ0_P,
    input wire CQ0_N,
    input wire CQ1_P,
    input wire CQ1_N,
    input wire CQ2_P,
    input wire CQ2_N,
    input wire CQ3_P,
    input wire CQ3_N,

    // input wire DQ0_P,
    // input wire DQ0_N,
    // input wire DQ1_P,
    // input wire DQ1_N,
    // input wire DQ2_P,
    // input wire DQ2_N,
    // input wire DQ3_P,
    // input wire DQ3_N,

    // input wire EQ0_P,
    // input wire EQ0_N,
    // input wire EQ1_P,
    // input wire EQ1_N,
    // input wire EQ2_P,
    // input wire EQ2_N,
    // input wire EQ3_P,
    // input wire EQ3_N,

    // input wire FQ0_P,
    // input wire FQ0_N,
    // input wire FQ1_P,
    // input wire FQ1_N,
    // input wire FQ2_P,
    // input wire FQ2_N,
    // input wire FQ3_P,
    // input wire FQ3_N,



    //Input Wire SPI from RPI

    input wire SPI_KOSI,
    input wire SPI_SCK,
    input wire SPI_SSB1,

    input wire DAT0,
    input wire DAT1,
    input wire DAT2,
    input wire DAT3,

    //output to ASIC

    output wire SCK_P,
    output wire SCK_N,
    
    output wire SDIN_P,
    output wire SDIN_N,
    
    output wire CS1B_P,
    output wire CS1B_N,

    output wire CS2B_P,
    output wire CS2B_N,


    
    output wire MEZZ_PAGE3_P,
    output wire MEZZ_PAGE3_N,
    
    output wire MEZZ_PAGE2_P,
    output wire MEZZ_PAGE2_N,
    
    output wire MEZZ_PAGE1_P,
    output wire MEZZ_PAGE1_N,
    
    output wire MEZZ_PAGE0_P,
    output wire MEZZ_PAGE0_N


    );
    

    reg [7:0] FIRMWARE_VER = 8'd24 ;// divide by 10 to get the firmware version
    // Bypassing SPI to DCPS
    OBUFDS OBUFDS_MEZZ_PAGE0(.I(DAT0),.O(MEZZ_PAGE0_P),.OB(MEZZ_PAGE0_N));
    OBUFDS OBUFDS_MEZZ_PAGE1(.I(DAT1),.O(MEZZ_PAGE1_P),.OB(MEZZ_PAGE1_N));
    OBUFDS OBUFDS_MEZZ_PAGE2(.I(DAT2),.O(MEZZ_PAGE2_P),.OB(MEZZ_PAGE2_N));
    OBUFDS OBUFDS_MEZZ_PAGE3(.I(DAT3),.O(MEZZ_PAGE3_P),.OB(MEZZ_PAGE3_N));

    OBUFDS OBUFDS_SDIN(.I(SPI_KOSI),.O(SDIN_P),.OB(SDIN_N));
    OBUFDS OBUFDS_SCK (.I(SPI_SCK),.O(SCK_P),.OB(SCK_N));

    //Swapped
    // OBUFDS OBUFDS_SDIN(.I(SPI_SCK),.O(SDIN_P),.OB(SDIN_N));
    // OBUFDS OBUFDS_SCK (.I(SPI_KOSI),.O(SCK_P),.OB(SCK_N));

    OBUFDS OBUFDS_CS1B(.I(SPI_SSB1),.O(CS1B_P),.OB(CS1B_N));
    OBUFDS OBUFDS_CS2B(.I(SPI_SSB1),.O(CS2B_P),.OB(CS2B_N));



    wire CLK;
    wire clk_ref;

   IBUFGDS IBUFGDS_CLK_REF (.O(clk_ref), .I(CLK_REF_P), .IB(CLK_REF_N)); //good
 
 
 
 
    //DDMTD Reference clocks
   wire BEAT_REF1,BEAT_REF1_out;
   IBUFDS IBUFDS_BEAT_REF1 (.O(BEAT_REF1_out), .I(BEAT_REF1_P), .IB(BEAT_REF1_N)); //good
   sync_ddr sync_BEAT_REF1(.clk(clk_ref),.D(BEAT_REF1_out),.Q(BEAT_REF1));

  wire BEAT_REF2,BEAT_REF2_out;
   IBUFDS IBUFDS_BEAT_REF2 (.O(BEAT_REF2_out), .I(BEAT_REF2_P), .IB(BEAT_REF2_N)); //good
   sync_ddr sync_BEAT_REF2(.clk(clk_ref),.D(BEAT_REF2_out),.Q(BEAT_REF2));
   
    

   // A pins
   wire AQ0,AQ1,AQ2,AQ3;
   wire AQ0_out,AQ1_out,AQ2_out,AQ3_out;
   
   
   IBUFDS IBUFDS_AQ0 (.O(AQ0_out), .I(AQ0_P), .IB(AQ0_N)); //good
   sync_ddr sync_AQ0(.clk(clk_ref),.D(AQ0_out),.Q(AQ0));
   
   IBUFDS IBUFDS_AQ1 (.O(AQ1_out), .I(AQ1_P), .IB(AQ1_N)); //good
   sync_ddr sync_AQ1(.clk(clk_ref),.D(AQ1_out),.Q(AQ1));

   IBUFDS IBUFDS_AQ2 (.O(AQ2_out), .I(AQ2_P), .IB(AQ2_N)); //good
   sync_ddr sync_AQ2(.clk(clk_ref),.D(AQ2_out),.Q(AQ2));

   IBUFDS IBUFDS_AQ3 (.O(AQ3_out), .I(AQ3_P), .IB(AQ3_N)); //good
   sync_ddr sync_AQ3(.clk(clk_ref),.D(AQ3_out),.Q(AQ3));



   // B pins

   wire BQ0,BQ1,BQ2,BQ3;
   wire BQ0_out,BQ1_out,BQ2_out,BQ3_out;
   
   
   IBUFDS IBUFDS_BQ0 (.O(BQ0_out), .I(BQ0_P), .IB(BQ0_N)); //good
   sync_ddr sync_BQ0(.clk(clk_ref),.D(BQ0_out),.Q(BQ0));
   
   IBUFDS IBUFDS_BQ1 (.O(BQ1_out), .I(BQ1_P), .IB(BQ1_N)); //good
   sync_ddr sync_BQ1(.clk(clk_ref),.D(BQ1_out),.Q(BQ1));

   IBUFDS IBUFDS_BQ2 (.O(BQ2_out), .I(BQ2_P), .IB(BQ2_N)); //good
   sync_ddr sync_BQ2(.clk(clk_ref),.D(BQ2_out),.Q(BQ2));

   IBUFDS IBUFDS_BQ3 (.O(BQ3_out), .I(BQ3_P), .IB(BQ3_N)); //good
   sync_ddr sync_BQ3(.clk(clk_ref),.D(BQ3_out),.Q(BQ3));



   // C pins

   wire CQ0,CQ1,CQ2,CQ3;
   wire CQ0_out,CQ1_out,CQ2_out,CQ3_out;
   
   
   IBUFDS IBUFDS_CQ0 (.O(CQ0_out), .I(CQ0_P), .IB(CQ0_N)); //good
   sync_ddr sync_CQ0(.clk(clk_ref),.D(CQ0_out),.Q(CQ0));
   
   IBUFDS IBUFDS_CQ1 (.O(CQ1_out), .I(CQ1_P), .IB(CQ1_N)); //good
   sync_ddr sync_CQ1(.clk(clk_ref),.D(CQ1_out),.Q(CQ1));

   IBUFDS IBUFDS_CQ2 (.O(CQ2_out), .I(CQ2_P), .IB(CQ2_N)); //good
   sync_ddr sync_CQ2(.clk(clk_ref),.D(CQ2_out),.Q(CQ2));

   IBUFDS IBUFDS_CQ3 (.O(CQ3_out), .I(CQ3_P), .IB(CQ3_N)); //good
   sync_ddr sync_CQ3(.clk(clk_ref),.D(CQ3_out),.Q(CQ3));



   


  
  //Simple counter to generate data
    reg beat_0_q1=0;
    reg beat_1_q1=0;
    integer counter_clkbeat=0;
    reg odd=0;
    always @(posedge clk_ref)
    begin
     // 100k subs
    counter_clkbeat<=counter_clkbeat+1;
    if(counter_clkbeat == 50000 ) begin
    beat_0_q1<=~beat_0_q1;
    beat_1_q1<=~beat_1_q1;
    counter_clkbeat <=0;
    end
    end





    

  wire [31:0]GPIO;
  wire user_reset;
  assign user_reset = GPIO[0];
  reg enable_sampling_logic=0;



  //Internal reset
  //Since clk_ref is the slower clock, we will run this as the reset counter...
  parameter RESET_COUNT = 1000000;
  parameter RESET_RUN   =  950000;
  reg internal_reset=1; //Active High
  integer reset_counter=0;
  always @(posedge clk_ref) 
  begin 
      if(user_reset)
      begin
      internal_reset<=1;
      reset_counter <=0;
      enable_sampling_logic <=0;
      end

      if( reset_counter < RESET_COUNT)
      reset_counter<=reset_counter+1;


      if(reset_counter == RESET_RUN) internal_reset <=0;
      else if (reset_counter == RESET_COUNT)  enable_sampling_logic<=1;

  end




  reg [31:0] external_counter;
  // reg  [24:0] ddmtd_counter;
  // assign external_counter = ddmtd_counter;
  always @(negedge clk_ref)
  begin
    if(~enable_sampling_logic) 
    begin
      external_counter=0;
    end
    else external_counter <= external_counter+1;
  end




  parameter NUM_DDMTD = 24;
  parameter DATA_WIDTH = 32; 
  parameter START_COUNT	=32;
  parameter NUM_BYTES = DATA_WIDTH*8/8; // PER BRAM CONTROLLER
  integer WORDS_TO_SEND = 1024;








  wire [DATA_WIDTH*NUM_DDMTD-1 : 0] TDATA;
  wire [(DATA_WIDTH*NUM_DDMTD/8)-1 : 0] TSTRB;
  wire TLAST;
  wire TVALID;
  reg  TREADY;
  wire TCLK;
  wire [NUM_DDMTD-1:0] PROG_FULL;
  
  wire RESETN;
  
  // Each bit of this wire will be the clock
  wire [NUM_DDMTD-1:0]  clk_beat;
//  Edit this 
//   assign clk_beat =  { 
//                       beat_0_q1,FQ2,FQ1,FQ0,EQ3,EQ2,EQ1,EQ0,
//                       DQ3,DQ2,DQ1,DQ0,CQ3,CQ2,CQ1,CQ0,
//                       BQ3,BQ2,BQ1,BQ0,AQ3,AQ2,AQ1,AQ0 
//                      };

  // assign clk_beat =  { 
  //                     beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,
  //                     beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,CQ3      ,CQ2      ,CQ1      ,CQ0      ,
  //                     BQ3      ,BQ2      ,BQ1      ,BQ0      ,AQ3      ,AQ2      ,AQ1      ,AQ0 
  //                    };


  assign clk_beat =  { 
                      beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,
                      beat_0_q1,beat_0_q1,beat_0_q1,CQ3      ,CQ2      ,CQ1      ,CQ0      ,BQ3      ,
                      BQ2      ,BQ1      ,BQ0      ,AQ3      ,AQ2      ,AQ1      ,AQ0      ,BEAT_REF1 
                     };
  // assign clk_beat =  { 
  //                     beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,
  //                     beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,
  //                     beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,beat_0_q1,AQ0
  //                    };

                    


 DDMTD_Array
#(
    .NUM_DDMTD(NUM_DDMTD),
    .DATA_WIDTH(DATA_WIDTH),
    .C_M_START_COUNT(START_COUNT)
 )
  DDMTD_Array_inst
 (
    // Inputs for the sampling logic
    .enable_sampling_logic(enable_sampling_logic), //Active High
    .clk_ref(clk_ref),
    .clk_beat(clk_beat),
    .external_counter(external_counter),
    .reset(internal_reset),
      

    // Fifo chain to AXIS
     .M_AXIS_ACLK(CLK),
     .M_AXIS_ARESETN(1'b1), //RESET when low.
     .M_AXIS_TVALID(TVALID), //output
     .M_AXIS_TDATA(TDATA),  
     .M_AXIS_TSTRB(TSTRB),
     .M_AXIS_TLAST(TLAST),
     .M_AXIS_TREADY(TREADY),
     .WORDS_TO_SEND(WORDS_TO_SEND),
     .PROG_FULL(PROG_FULL)
 );


  wire [31:0]BRAM_PORTB_0_addr;
  wire BRAM_PORTB_0_clk;
  wire [DATA_WIDTH*NUM_DDMTD-1:0]BRAM_PORTB_0_din;
  wire [DATA_WIDTH*NUM_DDMTD-1:0]BRAM_PORTB_0_dout;
  wire BRAM_PORTB_0_en;
  wire BRAM_PORTB_0_rst;
  wire [DATA_WIDTH*NUM_DDMTD/8-1:0]BRAM_PORTB_0_we;

  wire rsta_busy_0;
  wire rstb_busy_0;


  integer addr_pointer=0;
  integer word_counter;
  reg [DATA_WIDTH*NUM_DDMTD-1:0] data=0;
  reg [NUM_BYTES-1:0] we_byte=0;
  reg enable=1;

  



  reg enable_bram1 = 0; //used to write information to SOC


  always @(negedge CLK)
  begin

  if(internal_reset | ~GPIO[1])
  begin
    addr_pointer <=0;
    word_counter <=0;
    we_byte <=0;
    WORDS_TO_SEND <=BRAM_PORTB_0_dout;
    TREADY<=0;
    enable_bram1 <= 1;
  end
  
  else if(GPIO[1] & (word_counter<WORDS_TO_SEND))
    begin
      enable_bram1 <= 0;
      TREADY<=1; //TREADY
      // data <= {word_counter,32'd5,32'd4,32'd3,32'd2,32'd1,WORDS_TO_SEND,TDATA[31:0]};
      data <= TDATA;
      addr_pointer <= addr_pointer + NUM_BYTES;
      word_counter <=word_counter +1;
      we_byte<={(NUM_BYTES){1'b1}};
    end
  else 
  begin
    TREADY<=0; 
    we_byte <=0;
  end


  end


  assign BRAM_PORTB_0_clk = CLK;



  //Test Counter...
  reg [31:0] clk_counter = 0;
  always @(posedge CLK) begin
    clk_counter <= clk_counter +1;
  end

  //Syncing data before going into the bram
  reg addr_pointer_sync;
  reg [DATA_WIDTH*NUM_DDMTD-1:0] BRAM_PORTB_0_data;
  reg [DATA_WIDTH*NUM_DDMTD-1:0] BRAM_PORTB_1_data;
  reg [DATA_WIDTH*NUM_DDMTD-1:0] BRAM_PORTB_2_data;
  reg [NUM_BYTES-1:0] we_byte_sync;
  reg [NUM_BYTES-1:0] we_byte_bram1_sync;


  always @(negedge CLK)
  begin

    if (enable_bram1)
    begin
      BRAM_PORTB_1_data <= {internal_reset,clk_counter,FIRMWARE_VER,PROG_FULL} ;
      we_byte_bram1_sync <= {(NUM_BYTES){1'b1}};
      addr_pointer_sync <= 0;

    end
    else
    begin
      addr_pointer_sync <= addr_pointer;
      we_byte_sync <= we_byte;
      we_byte_bram1_sync <= we_byte;
      BRAM_PORTB_0_data <= data[255:0];
      BRAM_PORTB_1_data <= data[511:256];
      BRAM_PORTB_2_data <= data[767:512];
    end

  end


design_1_wrapper desing_ins   
   (
       
    .BRAM_PORTB_0_addr(addr_pointer),
    .BRAM_PORTB_0_clk(CLK),
    .BRAM_PORTB_0_din(BRAM_PORTB_0_data),
    .BRAM_PORTB_0_dout(BRAM_PORTB_0_dout),
    .BRAM_PORTB_0_en(1),
    .BRAM_PORTB_0_we(we_byte_sync),




    .BRAM_PORTB_1_addr(addr_pointer),
    .BRAM_PORTB_1_clk(CLK),
    .BRAM_PORTB_1_din(BRAM_PORTB_1_data),
    // .BRAM_PORTB_1_dout(BRAM_PORTB_0_dout),
    .BRAM_PORTB_1_en(1),
    .BRAM_PORTB_1_we(we_byte_bram1_sync),



    .BRAM_PORTB_2_addr(addr_pointer),
    .BRAM_PORTB_2_clk(CLK),
    .BRAM_PORTB_2_din(BRAM_PORTB_2_data),
    // .BRAM_PORTB_2_dout,
    .BRAM_PORTB_2_en(1),
    .BRAM_PORTB_2_we(we_byte_sync),




    .CLK_OUT(CLK),
    .CLK_IN(clk_ref),
    // .CLK_REF(clk_ref),
    .gpio_rtl_tri_o(GPIO)

    
   );
    

    
    
endmodule
