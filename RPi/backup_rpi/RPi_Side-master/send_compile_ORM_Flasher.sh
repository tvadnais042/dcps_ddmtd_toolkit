#!/bin/bash


SRC="Flash_Firmware"

for num in $(seq 1 1 9)
do
  # Syncing to the RPi
  DST=ORM$num
  echo "sending files to $DST"
  rsync -rv $SRC $DST:

  # compiling the program
  echo "compiling $DST files"
  echo

  ssh -T $DST << EOF
  touch ~/.hushlogin
  cd ~/$SRC;
  pwd;
  ./compile
  sleep 1;
EOF

echo "done for $DST"
done
