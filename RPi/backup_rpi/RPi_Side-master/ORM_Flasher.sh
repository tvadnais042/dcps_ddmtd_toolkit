#!/bin/bash
DST="./Flash_Firmware/HEX_Files"
SRC="./Flash_Firmware/"
HOST=$2

#Extract the file name from dst
FileName=$(echo $1 | rev | cut -d '/' -f1 | rev)


echo -e "The file we are flashing is $FileName \n"


if [ "$2" = "" ]
then
echo "Flashing from ORM 2 to ORM 9 ..."

for num in $(seq 3 2 9) # change 1 to 2 to do alternate flashing...
do

  echo
  echo -e "Now flashing ORM $num"
  HOST=ORM$num
  scp $1 $HOST:$DST
  #-T for not assigning pseudo terminal
  ssh -T $HOST << EOF
    cd ~/$SRC;
    echo "We are in dir::\$PWD"
    rm status.txt
    sudo ./ORMFlash.exe < HEX_Files/$FileName
    sleep 1;
    result=\$(cat status.txt)
    if [ "\$result" = "SUCCESS" ]
    then
      echo "Success"
      ./power_Cycle.py
    else
      echo "Failed"
      while [ "\$result" = "FAILED" ]
      do
        echo -e "failed, flashing again..."
        sudo ./ORMFlash.exe < HEX_Files/$FileName
        result=\$(cat status.txt)
        echo \$result
        echo
      done
      ./power_Cycle.py
    fi
EOF
done

else
scp $1 $HOST:$DST
ssh -T $HOST << EOF
  cd ~/$SRC;
  echo "We are in dir::\$PWD"
  sudo ./ORMFlash.exe < HEX_Files/$FileName
  sleep 1;
EOF
fi
