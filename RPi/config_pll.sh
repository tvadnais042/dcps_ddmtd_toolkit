#!/bin/bash
#This will configure both OCXO and PLL

HOST_NAME=$1
REL_PATH=$2
CONFIG_NAME_PLL=$4
CONFIG_NAME_OCXO=$3


cp $2si5344_config/$4 $2/Flash_Firmware/Si5344_REG_PLL.h
cp $2si5344_config/$3 $2/Flash_Firmware/Si5344_REG.h

# echo "rsync -ra "$1"Flash_Firmware" $3:
rsync -ra $2Flash_Firmware $HOST_NAME:


#Compile and Run

ssh -T $HOST_NAME << EOF
  cd Flash_Firmware
  echo "We are in dir::\$PWD"
  ./compile.sh
  sudo ./loc_pll.exe 
  sudo ./mezz_pll.exe
EOF