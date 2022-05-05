#!/bin/bash


PI=$5

# Running the dcps control code
rsync -ra $1dcps_control $PI:
ssh -T $PI << EOF
cd dcps_control
chmod +x compile.sh
./compile.sh
sudo ./rpi_dcps.exe $2 $3 $4
# echo "Done Executing RPI DCPS"
EOF


