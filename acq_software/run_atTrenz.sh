#!/bin/bash




# HOST="root@10.0.0.10"
HOST=$3
# FIRMWARE='2021_06_04_firmware.bit.bin'
# FIRMWARE='2021_07_26_firmware_v1.1.bit.bin'
# FIRMWARE='2021_08_09_24channel_v2.bit.bin'
# FIRMWARE='2021_08_09_DCPS_v2.bit.bin'
# FIRMWARE='2021_10_08_firmware_v2.2.bit.bin'
FIRMWARE='2021_10_11_firmware_v2.4.bit.bin'




# echo "Copying firmware: "$FIRMWARE
# # sshpass -p "root" scp $1/firmware_files/$FIRMWARE $HOST:
# scp $1/firmware_files/$FIRMWARE $HOST:

# echo "Copying loading script: do_load.sh"
# # echo "Sending software to Trenz"
# # sshpass -p "root" scp $1do_load.sh $HOST:
# scp $1do_load.sh $HOST:




# sshpass -p "root" scp -r -r $1data_acq $HOST:
# sshpass -p "root" ssh -T $HOST << EOF
# ./do_load.sh $FIRMWARE
# cd data_acq
# chmod +x compile.sh
# ./compile.sh
# nice --20 ./get_data_bram $2
# EOF



# echo "Copying Data_acq Folder"
# scp -r -r $1data_acq $HOST:

echo "Running & Compiling Section"
ssh -T $HOST << EOF

echo "Loading Firmware: "$FIRMWARE
./do_load.sh $FIRMWARE
cd data_acq

# echo "Compiling get_data_bram"
# chmod +x compile.sh
# ./compile.sh

echo "Running get_data_bram"
nice --20 ./get_data_bram $2
EOF




