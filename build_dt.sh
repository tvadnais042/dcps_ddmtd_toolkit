# cp /home/nishant/tools/Xilinx/Vivado/2022.1/KR260_Port/KR260_Port.runs/impl_1/main.bin ./bram.bit.bin

# xsct get_dtbo.tcl

# cd bram_dts/
# dtc -@ -O dtb -o pl.dtbo pl.dtsi
# cd ../
# cp bram_dts/pl.dtbo bram.dtbo

# mkdir -p payload
# cp bram.bit.bin bram.dtbo shell.json payload/

scp -r payload kria:
ssh -T kria << EOF
pwd
sudo xmutil unloadapp
sudo cp -r  /home/ubuntu/payload/* /lib/firmware/xilinx/bram/
sudo xmutil unloadapp
sudo xmutil loadapp bram

EOF
