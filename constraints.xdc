create_clock -period 6.250 -name CLK_REF_P -waveform {0.000 3.125} [get_ports CLK_REF_P]
#All connections are in Page 5 of the KRIA_TSTR_Schematics file created by Erich
#The pin mapping of the som_240 connector is avaialble in the file Kria_K26_SOM_Rev1.xdc
#LVDS is a 2.5V standard
#3.3V I/O standards LVTTL and LVCMOS
#2.5V I/O standards LVCMOS and LVDS(1)
#1.8V I/O standards LVCMOS, SSTL(2)(3), and HSTL(2)(3)
#Comment Convention First line is the name and function of the pin
#Next line is the corresponding pin mapping from the xdc file for the P pair
#Next line is the corresponding pin mapping from the xdc file for the N pair

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AE5   [get_ports "som240_2_c41"] ;# Bank  64 VCCO - som240_2_c44 - IO_L12P_T1U_N10_GC_64
#set_property PACKAGE_PIN AF5      [get_ports "som240_2_c42"] ;# Bank  64 VCCO - som240_2_c44 - IO_L12N_T1U_N11_GC_64
#Reference Clock on the schematics it is the PLL_OUT LVDS pair
set_property IOSTANDARD LVDS [get_ports CLK_REF_P]

set_property PACKAGE_PIN AE5 [get_ports CLK_REF_P]
set_property PACKAGE_PIN AF5 [get_ports CLK_REF_N]
set_property IOSTANDARD LVDS [get_ports CLK_REF_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AH8 [get_ports "som240_2_b36"] ;# Bank  64 VCCO - som240_2_c44 - IO_L9P_T1L_N4_AD12P_64
#set_property PACKAGE_PIN AH7      [get_ports "som240_2_b37"] ;# Bank  64 VCCO - som240_2_c44 - IO_L9N_T1L_N5_AD12N_64
#Channel 0
set_property IOSTANDARD LVDS [get_ports AQ0_P]

set_property PACKAGE_PIN AH8 [get_ports AQ0_P]
set_property PACKAGE_PIN AH7 [get_ports AQ0_N]
set_property IOSTANDARD LVDS [get_ports AQ0_N]

#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AE2      [get_ports "som240_2_b39"] ;# Bank  64 VCCO - som240_2_c44 - IO_L22P_T3U_N6_DBC_AD0P_64
#set_property PACKAGE_PIN AF2      [get_ports "som240_2_b40"] ;# Bank  64 VCCO - som240_2_c44 - IO_L22N_T3U_N7_DBC_AD0N_64
#Channel 2
set_property IOSTANDARD LVDS [get_ports AQ2_P]

set_property PACKAGE_PIN AE2 [get_ports AQ2_P]
set_property PACKAGE_PIN AF2 [get_ports AQ2_N]
set_property IOSTANDARD LVDS [get_ports AQ2_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AD7      [get_ports "som240_2_a41"] ;# Bank  64 VCCO - som240_2_c44 - IO_L4P_T0U_N6_DBC_AD7P_64
#set_property PACKAGE_PIN AE7      [get_ports "som240_2_a42"] ;# Bank  64 VCCO - som240_2_c44 - IO_L4N_T0U_N7_DBC_AD7N_64
#Channel 3
set_property IOSTANDARD LVDS [get_ports AQ3_P]

set_property PACKAGE_PIN AD7 [get_ports AQ3_P]
set_property PACKAGE_PIN AE7 [get_ports AQ3_N]
set_property IOSTANDARD LVDS [get_ports AQ3_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AD2      [get_ports "som240_2_b30"] ;# Bank  64 VCCO - som240_2_c44 - IO_L16P_T2U_N6_QBC_AD3P_64
#set_property PACKAGE_PIN AD1      [get_ports "som240_2_b31"] ;# Bank  64 VCCO - som240_2_c44 - IO_L16N_T2U_N7_QBC_AD3N_64
#Channel 4
set_property IOSTANDARD LVDS [get_ports BQ0_P]

set_property PACKAGE_PIN AD2 [get_ports BQ0_P]
set_property PACKAGE_PIN AD1 [get_ports BQ0_N]
set_property IOSTANDARD LVDS [get_ports BQ0_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AF8      [get_ports "som240_2_b27"] ;# Bank  64 VCCO - som240_2_c44 - IO_L8P_T1L_N2_AD5P_64
#set_property PACKAGE_PIN AG8      [get_ports "som240_2_b28"] ;# Bank  64 VCCO - som240_2_c44 - IO_L8N_T1L_N3_AD5N_64
#Channel 5
set_property IOSTANDARD LVDS [get_ports BQ1_P]

set_property PACKAGE_PIN AF8 [get_ports BQ1_P]
set_property PACKAGE_PIN AG8 [get_ports BQ1_N]
set_property IOSTANDARD LVDS [get_ports BQ1_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AG9      [get_ports "som240_2_c38"] ;# Bank  64 VCCO - som240_2_c44 - IO_L7P_T1L_N0_QBC_AD13P_64
#set_property PACKAGE_PIN AH9      [get_ports "som240_2_c39"] ;# Bank  64 VCCO - som240_2_c44 - IO_L7N_T1L_N1_QBC_AD13N_64
#Channel 6
set_property IOSTANDARD LVDS [get_ports BQ2_P]

set_property PACKAGE_PIN AG9 [get_ports BQ2_P]
set_property PACKAGE_PIN AH9 [get_ports BQ2_N]
set_property IOSTANDARD LVDS [get_ports BQ2_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AG4 [get_ports "som240_2_a38"] ;# Bank  64 VCCO - som240_2_c44 - IO_L19P_T3L_N0_DBC_AD9P_64
#set_property PACKAGE_PIN AH4      [get_ports "som240_2_a39"] ;# Bank  64 VCCO - som240_2_c44 - IO_L19N_T3L_N1_DBC_AD9N_64
#Channel 7
set_property IOSTANDARD LVDS [get_ports BQ3_P]

set_property PACKAGE_PIN AG4 [get_ports BQ3_P]
set_property PACKAGE_PIN AH4 [get_ports BQ3_N]
set_property IOSTANDARD LVDS [get_ports BQ3_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AB4 [get_ports "som240_2_c35"] ;# Bank  64 VCCO - som240_2_c44 - IO_L15P_T2L_N4_AD11P_64
#set_property PACKAGE_PIN AB3      [get_ports "som240_2_c36"] ;# Bank  64 VCCO - som240_2_c44 - IO_L15N_T2L_N5_AD11N_64
#Channel 8
set_property IOSTANDARD LVDS [get_ports CQ0_P]

set_property PACKAGE_PIN AB4 [get_ports CQ0_P]
set_property PACKAGE_PIN AB3 [get_ports CQ0_N]
set_property IOSTANDARD LVDS [get_ports CQ0_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AB2  [get_ports "som240_2_a35"] ;# Bank  64 VCCO - som240_2_c44 - IO_L17P_T2U_N8_AD10P_64
#set_property PACKAGE_PIN AC2      [get_ports "som240_2_a36"] ;# Bank  64 VCCO - som240_2_c44 - IO_L17N_T2U_N9_AD10N_64
#Channel 9
set_property IOSTANDARD LVDS [get_ports CQ1_P]

set_property PACKAGE_PIN AB2 [get_ports CQ1_P]
set_property PACKAGE_PIN AC2 [get_ports CQ1_N]
set_property IOSTANDARD LVDS [get_ports CQ1_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AC4      [get_ports "som240_2_c32"] ;# Bank  64 VCCO - som240_2_c44 - IO_L14P_T2L_N2_GC_64
#set_property PACKAGE_PIN AC3      [get_ports "som240_2_c33"] ;# Bank  64 VCCO - som240_2_c44 - IO_L14N_T2L_N3_GC_64
#Channel 10

set_property IOSTANDARD LVDS [get_ports CQ2_P]

set_property PACKAGE_PIN AC4 [get_ports CQ2_P]
set_property PACKAGE_PIN AC3 [get_ports CQ2_N]
set_property IOSTANDARD LVDS [get_ports CQ2_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AH2      [get_ports "som240_2_a32"] ;# Bank  64 VCCO - som240_2_c44 - IO_L23P_T3U_N8_64
#set_property PACKAGE_PIN AH1      [get_ports "som240_2_a33"] ;# Bank  64 VCCO - som240_2_c44 - IO_L23N_T3U_N9_64
#Channel 11
set_property IOSTANDARD LVDS [get_ports CQ3_P]

set_property PACKAGE_PIN AH2 [get_ports CQ3_P]
set_property PACKAGE_PIN AH1 [get_ports CQ3_N]
set_property IOSTANDARD LVDS [get_ports CQ3_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AE3      [get_ports "som240_2_c26"] ;# Bank  64 VCCO - som240_2_c44 - IO_L21P_T3L_N4_AD8P_64
#set_property PACKAGE_PIN AF3      [get_ports "som240_2_c27"] ;# Bank  64 VCCO - som240_2_c44 - IO_L21N_T3L_N5_AD8N_64
#Channel 12
set_property IOSTANDARD LVDS [get_ports DQ0_P]

set_property PACKAGE_PIN AE3 [get_ports DQ0_P]
set_property PACKAGE_PIN AF3 [get_ports DQ0_N]
set_property IOSTANDARD LVDS [get_ports DQ0_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AB7      [get_ports "som240_2_d39"] ;# Bank  64 VCCO - som240_2_c44 - IO_L5P_T0U_N8_AD14P_64
#set_property PACKAGE_PIN AC7      [get_ports "som240_2_d40"] ;# Bank  64 VCCO - som240_2_c44 - IO_L5N_T0U_N9_AD14N_64
#Channel 13
set_property IOSTANDARD LVDS [get_ports DQ1_P]

set_property PACKAGE_PIN AB7 [get_ports DQ1_P]
set_property PACKAGE_PIN AC7 [get_ports DQ1_N]
set_property IOSTANDARD LVDS [get_ports DQ1_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AB8      [get_ports "som240_2_d36"] ;# Bank  64 VCCO - som240_2_c44 - IO_L3P_T0L_N4_AD15P_64
#set_property PACKAGE_PIN AC8      [get_ports "som240_2_d37"] ;# Bank  64 VCCO - som240_2_c44 - IO_L3N_T0L_N5_AD15N_64
#Channel 14
set_property IOSTANDARD LVDS [get_ports DQ2_P]

set_property PACKAGE_PIN AB8 [get_ports DQ2_P]
set_property PACKAGE_PIN AC8 [get_ports DQ2_N]
set_property IOSTANDARD LVDS [get_ports DQ2_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AC9      [get_ports "som240_2_d33"] ;# Bank  64 VCCO - som240_2_c44 - IO_L1P_T0L_N0_DBC_64
#set_property PACKAGE_PIN AD9      [get_ports "som240_2_d34"] ;# Bank  64 VCCO - som240_2_c44 - IO_L1N_T0L_N1_DBC_64
#Channel 15
set_property IOSTANDARD LVDS [get_ports DQ3_P]

set_property PACKAGE_PIN AC9 [get_ports DQ3_P]
set_property PACKAGE_PIN AD9 [get_ports DQ3_N]
set_property IOSTANDARD LVDS [get_ports DQ3_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AE9      [get_ports "som240_2_d30"] ;# Bank  64 VCCO - som240_2_c44 - IO_L2P_T0L_N2_64
#set_property PACKAGE_PIN AE8      [get_ports "som240_2_d31"] ;# Bank  64 VCCO - som240_2_c44 - IO_L2N_T0L_N3_64
#Channel 16
set_property IOSTANDARD LVDS [get_ports EQ0_P]


set_property PACKAGE_PIN AE9 [get_ports EQ0_P]
set_property PACKAGE_PIN AE8 [get_ports EQ0_N]
set_property IOSTANDARD LVDS [get_ports EQ0_N]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN K7       [get_ports "som240_2_d25"] ;# Bank  65 VCCO - som240_2_a44 - IO_L22N_T3U_N7_DBC_AD0N_65
#set_property PACKAGE_PIN K8       [get_ports "som240_2_d24"] ;# Bank  65 VCCO - som240_2_a44 - IO_L22P_T3U_N6_DBC_AD0P_65
#Channel 17
set_property PACKAGE_PIN K7 [get_ports EQ1_P]
set_property IOSTANDARD LVDS [get_ports EQ1_P]
set_property is_loc_fixed true [get_ports [list  EQ1_P]]


set_property PACKAGE_PIN K8 [get_ports EQ1_N]
set_property IOSTANDARD LVDS [get_ports EQ1_N]
set_property is_loc_fixed true [get_ports [list  EQ1_N]]

#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AF7      [get_ports "som240_2_d27"] ;# Bank  64 VCCO - som240_2_c44 - IO_L11P_T1U_N8_GC_64
#set_property PACKAGE_PIN AF6      [get_ports "som240_2_d28"] ;# Bank  64 VCCO - som240_2_c44 - IO_L11N_T1U_N9_GC_64
#Channel 18
set_property IOSTANDARD LVDS [get_ports EQ2_P]
set_property is_loc_fixed true [get_ports [list  EQ2_P]]



set_property PACKAGE_PIN AF7 [get_ports EQ2_P]
set_property PACKAGE_PIN AF6 [get_ports EQ2_N]
set_property IOSTANDARD LVDS [get_ports EQ2_N]
set_property is_loc_fixed true [get_ports [list  EQ2_P]]

#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AD4      [get_ports "som240_2_c30"] ;# Bank  64 VCCO - som240_2_c44 - IO_L13N_T2L_N1_GC_QBC_64
#set_property PACKAGE_PIN AD5      [get_ports "som240_2_c29"] ;# Bank  64 VCCO - som240_2_c44 - IO_L13P_T2L_N0_GC_QBC_64
#PLLIN1
set_property IOSTANDARD LVDS [get_ports PLL_IN1_P]
set_property is_loc_fixed true [get_ports [list  PLL_IN1_P]]



set_property PACKAGE_PIN AD5 [get_ports PLL_IN1_P]
set_property PACKAGE_PIN AD4 [get_ports PLL_IN1_N]
set_property IOSTANDARD LVDS [get_ports PLL_IN1_N]
set_property is_loc_fixed true [get_ports [list  PLL_IN1_N]]

#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN AG6      [get_ports "som240_2_a29"] ;# Bank  64 VCCO - som240_2_c44 - IO_L10P_T1U_N6_QBC_AD4P_64
#set_property PACKAGE_PIN AG5      [get_ports "som240_2_a30"] ;# Bank  64 VCCO - som240_2_c44 - IO_L10N_T1U_N7_QBC_AD4N_64
#PLLIN2

set_property IOSTANDARD LVDS [get_ports PLL_IN2_P]
set_property is_loc_fixed true [get_ports [list  PLL_IN2_P]]


set_property PACKAGE_PIN AG6 [get_ports PLL_IN2_P]
set_property PACKAGE_PIN AG5 [get_ports PLL_IN2_N]
set_property IOSTANDARD LVDS [get_ports PLL_IN2_N]
set_property is_loc_fixed true [get_ports [list  PLL_IN2_N]]


#-----------------------------------------------------------------------


#-----------------------------------------------------------------------
#set_property PACKAGE_PIN H9       [get_ports "som240_2_a26"] ;# Bank  65 VCCO - som240_2_a44 - IO_L24P_T3U_N10_PERSTN1_I2C_SDA_65
#set_property PACKAGE_PIN H8       [get_ports "som240_2_a27"] ;# Bank  65 VCCO - som240_2_a44 - IO_L24N_T3U_N11_PERSTN0_65
#TX Channel 1

set_property IOSTANDARD LVDS [get_ports TX_1_P]
set_property is_loc_fixed true [get_ports [list  TX_1_P]]


set_property PACKAGE_PIN H9 [get_ports TX_1_P]
set_property PACKAGE_PIN H8 [get_ports TX_1_N]
set_property IOSTANDARD HSTL_I_18 [get_ports TX1_N]
set_property is_loc_fixed true [get_ports [list  TX_1_N]]
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#set_property PACKAGE_PIN K9       [get_ports "som240_2_c23"] ;# Bank  65 VCCO - som240_2_a44 - IO_L23P_T3U_N8_I2C_SCLK_65
#set_property PACKAGE_PIN J9       [get_ports "som240_2_c24"] ;# Bank  65 VCCO - som240_2_a44 - IO_L23N_T3U_N9_65
#TX Channel 2

set_property IOSTANDARD LVDS [get_ports TX_2_P]


set_property PACKAGE_PIN K9 [get_ports TX_2_P]
set_property PACKAGE_PIN J9 [get_ports TX_2_N]
set_property IOSTANDARD LVDS [get_ports TX_2_N]
set_property is_loc_fixed true [get_ports [list  TX_2_N]]

#-----------------------------------------------------------------------


#-----------------------------------------------------------------------
#set_property PACKAGE_PIN J7       [get_ports "som240_2_a23"] ;# Bank  65 VCCO - som240_2_a44 - IO_L21P_T3L_N4_AD8P_65
#set_property PACKAGE_PIN H7       [get_ports "som240_2_a24"] ;# Bank  65 VCCO - som240_2_a44 - IO_L21N_T3L_N5_AD8N_65
#TX Channel 3

set_property IOSTANDARD LVDS [get_ports TX_3_P]
set_property is_loc_fixed true [get_ports [list  TX_3_P]]


set_property PACKAGE_PIN J7 [get_ports TX_3_P]
set_property PACKAGE_PIN H7 [get_ports TX_3_N]
set_property IOSTANDARD LVDS [get_ports TX_3_N]
set_property is_loc_fixed true [get_ports [list  TX_3_N]]


#-----------------------------------------------------------------------
#set_property PACKAGE_PIN P7       [get_ports "som240_2_c20"] ;# Bank  65 VCCO - som240_2_a44 - IO_L16P_T2U_N6_QBC_AD3P_65
#set_property PACKAGE_PIN P6       [get_ports "som240_2_c21"] ;# Bank  65 VCCO - som240_2_a44 - IO_L16N_T2U_N7_QBC_AD3N_65
#TX Channel 4

set_property IOSTANDARD LVDS [get_ports TX_4_P]
set_property is_loc_fixed true [get_ports [list  TX_4_P]]


set_property PACKAGE_PIN P7 [get_ports TX_4_P]
set_property PACKAGE_PIN P6 [get_ports TX_4_N]
set_property IOSTANDARD HSTL_I_18 [get_ports TX4_N]
set_property is_loc_fixed true [get_ports [list  TX_4_N]]

#-----------------------------------------------------------------------





##-----------------------------------------------------------------------



