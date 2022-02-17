#!/usr/bin/env bash



HOST="Nex1"
SRC=Flash_Firmware


rsync -rv $SRC $HOST:
ssh -T $HOST << EOF
cd ~/$SRC;
pwd;
./compile.sh
sudo ./$1
EOF
