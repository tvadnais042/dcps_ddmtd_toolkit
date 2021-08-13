#!/bin/bash




TRENZ="root@10.0.0.10"
# PI="pi@10.0.0.9"
PI=$4




# Flashing Firmware
# sshpass -p 'root' scp ./do_load.sh $TRENZ:
# sshpass -p 'root' ssh -T $TRENZ << EOF
# ./do_load.sh main.bit.bin
# EOF



# Running the dcps control code
rsync -ra $1dcps_control $PI:
ssh -T $PI << EOF
cd dcps_control
# chmod +x compile.sh
# ./compile.sh
sudo ./rpi_dcps.exe $2 $3
# echo "Done Executing RPI DCPS"
EOF


