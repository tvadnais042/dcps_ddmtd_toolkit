


DST="./Flash_Firmware/HEX_Files"
SRC="Flash_Firmware/"
HOST=$2

#Extract the file name from dst
FileName=$(echo $1 | rev | cut -d '/' -f1 | rev)


scp $1 $HOST:$DST
ssh -T $HOST << EOF
  cd ~/$SRC;
  echo "We are in dir::\$PWD"
  # gcc -O program_fpga_Nex.c  -l bcm2835 -o NexFlash.exe
  sudo ./NexFlash.exe < HEX_Files/$FileName
  sleep 1;
EOF
