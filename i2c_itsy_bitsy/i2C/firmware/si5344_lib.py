from adafruit_bus_device import i2c_device

def read_config(config_filename, si5344Instance):
    """
    reg_filename --> ouput of the Clock Builder C header file
    returns list of addresses and values including the preamble and the postamble
    """
    encd = "latin1"  # encoding
    TOTAL_REG_NUM = 0  # total number of registers actions
    addresses_read = 0

    with open(config_filename, encoding=encd) as f:
        for num, i in enumerate(f.readlines()):
            if ("NUM_REGS" in i) and ("#define" in i):
                TOTAL_REG_NUM = int(i.split("\t")[-1])
            if ("{" in i) & ("}" in i) & ("0x" in i):
                addr, val = i.split(" ")[1:3]
                # addresses.append(addr.split(",")[0])
                # values.append(val.split(",")[0])
                address = addr.split(",")[0]
                value = val.split(",")[0]
                addresses_read += 1
                if addresses_read==1:
                    si5344Instance.transfer(address, value)
                # if num == 2:
                # time.sleep(1)

    print("Total Registers Detected: ", TOTAL_REG_NUM)
    print("Total Registers Read    : ", addresses_read)


class si5344_i2c:
    def __init__(self, i2cbus, i2caddress):
        self.i2c_device = i2c_device.I2CDevice(
            i2cbus, i2caddress
        )  # DeviceAddress(i2caddress))
        # self.i2cbus = i2cbus
        # self.i2caddress = i2caddress
        self.PAGE_ADDR = 0x1  # Page Address

    def write_i2c(self, address, data):
        # The write_byte_data used in the original code is a SMbus
        # method used to write a byte of data to a specific address bus
        # For the circuitpython change we use the writeto method of the i2cdevice class
        self.i2c_device.write(bytes([address, data]))
        # print(bin(i2caddress))

    def read_i2c(self, address):
        result = bytearray(2)
        self.i2c_device.write_then_readinto(bytes([address]), result)
        return result

    def set_page(self, page):
        self.write_i2c(page, page)
        # Check if the page is correct...
        readPage = self.read_i2c(page)
        if readPage != page:
            print("Unsuccessful Page Settings!", readPage, " ", page)

    def transfer(self, addr, val):
        page_byte = (int(addr, 16) >> 8) & 0xFF
        addr_byte = (int(addr, 16)) & 0xFF
        val_byte = int(val, 16) & 0xFF

        #self.set_page(page_byte)
        self.write_i2c(addr_byte, val_byte)
        reading = self.read_i2c(addr_byte)
        print("lets check - Val: ", val_byte ," Read: ", reading)
        #if val_byte != reading:
           # print("Mismatch! ", hex(int.from_bytes(val_byte))," ", hex(int.from_bytes(reading)))
