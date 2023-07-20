 scp -r payload kria:
  ssh -T kria << EOF
  pwd
  sudo xmutil unloadapp
  sudo cp -r  /home/ubuntu/payload/* /lib/firmware/xilinx/bram/
  sudo xmutil unloadapp
  sudo xmutil loadapp bram

