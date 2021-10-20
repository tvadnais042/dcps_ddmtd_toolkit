#!/bin/bash
#This will configure both OCXO and PLL

HOST_NAME=$1
REL_PATH=$2
CONFIG_NAME_PLL=$4
CONFIG_NAME_OCXO=$3


#copy the correct configuration file for local pll
if [ $# == 4 ]
then
  echo "No board number selected; going with Si5344H configs"
  cp $2si5344_config/$4 $2/Flash_Firmware/Si5344H_REG_LOC.h
  PLL_EXE=./loc_pll_Si5344H.exe
elif [ $5 == '1' ]
then
  echo "Board Number "$5 "chosen"
  cp $2si5344_config/$4 $2/Flash_Firmware/Si5344_REG_LOC.h
  PLL_EXE=./loc_pll_Si5344.exe
else  
  echo "Board Number "$5 "chosen; make sure this is the correct board"
  cp $2si5344_config/$4 $2/Flash_Firmware/Si5344H_REG_LOC.h
  PLL_EXE=./loc_pll_Si5344H.exe
fi

#copy the correct configuration file for OCXO pll
cp $2si5344_config/$3 $2/Flash_Firmware/Si5344H_REG_MEZZ.h

rsync -ra $2Flash_Firmware $HOST_NAME:



#Compile and Run

ssh -T $HOST_NAME << EOF
  cd Flash_Firmware
  echo "We are in dir::\$PWD"
  ./compile.sh
  sudo $PLL_EXE
  sudo ./mezz_pll_Si5344H.exe
EOF