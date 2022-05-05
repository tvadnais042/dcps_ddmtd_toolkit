gcc -O rpi_dcps.c dcps1_lib.c dcps2_lib.c spi_common.c NexysDDMTD.c -lwiringPi -l bcm2835 -o rpi_dcps.exe
echo Done Compiling RPI DCPS 
