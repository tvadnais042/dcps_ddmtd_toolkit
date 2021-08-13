#!/bin/bash

SRC="Flash_Firmware"

if [ "$1" = "" ]
then

  for num in $(seq 1 1 9)
  do
    # Syncing to the RPi
    DST=ORM$num
    ssh -T $DST << EOF
    cd ~/$SRC;
    pwd;
    ./power_Cycle.py
    sleep 1;
EOF
  done

else
  DST=$1
  ssh -T $DST << EOF
  cd ~/$SRC;
  pwd;
  ./power_Cycle.py
  sleep 1;
EOF
fi
