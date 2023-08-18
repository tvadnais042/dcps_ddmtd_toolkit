#!/usr/bin/python3
import board
import busio
import si5344_lib as siLib
import time

reg_filename ="Si5344-RevD-Registers.h"
i2cbus = busio.I2C(board.SCL, board.SDA)
i2caddress = 0x70
si5344 = siLib.si5344_i2c(i2cbus, i2caddress)
while not i2cbus.try_lock():
    pass
siLib.read_config(reg_filename, si5344)
i2cbus.unlock()
#for i, (addr, val) in enumerate(zip(addrs, vals)):
#    si5344.transfer(addr, val)
#    if i == 2:
#        time.sleep(1)
