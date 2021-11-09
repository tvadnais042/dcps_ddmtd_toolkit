#!/bin/bash
echo 'main.bit.bin will be written now' 
cp $1project_2_bram.runs/impl_1/main.bit $1.
bootgen -image main.bif -arch zynqmp -process_bitstream bin -w

#echo "We will send it to trenz_fpga now"
#sshpass -p "root" scp main.bit.bin root@trenz_fpga:

