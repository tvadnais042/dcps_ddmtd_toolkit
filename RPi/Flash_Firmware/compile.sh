#gcc -O program_fpga.c  -l bcm2835 -o ORMFlash.exe
# gcc -O program_fpga_Nex.c  -l bcm2835 -o NexFlash.exe
# gcc -O GBT_SCA.c  spi_common.c -l bcm2835 -o GBT_SCA.exe
# gcc -O sca_blink.c spi_common.c  -l bcm2835 -o sca_blink.exe

#gcc -O ddmtd_mem.c spi_common.c NexysDDMTD.c -l bcm2835 -o ddmtd_mem.exe
#echo Done Compiling MEM
#cp /home/pi/Flash_Firmware/PLL_Conf/160MHzBand4k.h /home/pi/FlashFirmware/Si5344
gcc -O loc_pll_Si5344.c  spi_common.c NexysDDMTD.c -l bcm2835 -o loc_pll_Si5344.exe
gcc -O loc_pll_Si5344H.c spi_common.c NexysDDMTD.c -l bcm2835 -o loc_pll_Si5344H.exe

gcc -O mezz_pll_Si5344H.c spi_common.c NexysDDMTD.c -l bcm2835 -o mezz_pll_Si5344H.exe
echo Done Compiling PLLs
