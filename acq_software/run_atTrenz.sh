#!/bin/bash




# HOST="root@10.0.0.10"
HOST=$3
# FIRMWARE='2021_06_04_firmware.bit.bin'
# FIRMWARE='2021_07_26_firmware_v1.1.bit.bin'
FIRMWARE='2021_08_09_24channel_v2.bit.bin'
sshpass -p "root" scp $1/firmware_files/$FIRMWARE $HOST:
echo "loading firmware: "$FIRMWARE

# echo "Sending software to Trenz"
# sshpass -p "root" scp get_data.c $HOST:
sshpass -p "root" scp $1do_load.sh $HOST:


# sshpass -p "root" rsync -rva -r $1data_acq $HOST:
sshpass -p "root" scp -r -r $1data_acq $HOST:
sshpass -p "root" ssh -T $HOST << EOF
./do_load.sh $FIRMWARE
cd data_acq
# chmod +x compile.sh
# ./compile.sh
nice --20 ./get_data_bram $2
EOF



