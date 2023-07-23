import adafruit_bus_device.i2c_device as i2c_device

def read_config(config_filename):
    '''
    reg_file_name --> ouput of the Clock Builder C header file
    returns list of addresses and values including the preamble and the postamble
    '''
    encd = "latin1" #encoding
    TOTAL_REG_NUM = 0 #total number of registers actions
    addresses = []
    values = []
    with open(config_filename, encoding=encd) as f:
        for i in f.readlines():
            if ("NUM_REGS" in i) and ("#define" in i):
                TOTAL_REG_NUM = int(i.split("\t")[-1])
            if ("{" in i) & ("}" in i) & ("0x" in i):
                addr,val = i.split(" ")[1:3]
                addresses.append(addr.split(",")[0])
                values.append(val.split(",")[0])
                    # print(addr,val)
                # break
            # else:
            #     print(i)

    print("Total Registers Detected: ",TOTAL_REG_NUM)
    print("Total Registers Read    : ", len(addresses))
    return addresses,values



class si5344_i2c():
    def __init__(self,i2cbus,i2caddress):
        self.i2c_device = I2CDevice(i2c_bus,DeviceAddress(i2c_address)) 
        self.PAGE_ADDR = 0x1; #Page Address
        
    def write_i2c (self,address,data):
     #The write_byte_data used in the original code is a SMbus method used to write a byte of data to a specific address bus
     #For the circuitpython change we use the writeto method of the i2cdevice class
        self.i2c_device.writeto(bytes([address,data])
        # print(bin(i2caddress))

    def read_i2c(self,address):
        result=bytearray(1)
        self.i2c_device.write_then_readinto(address,result)
        return result
    
    def set_page(self,page):
        self.write_i2c(self.PAGE_ADDR,page)
        #Check if the page is correct...
        if self.read_i2c(self.PAGE_ADDR) != page:
            print("Unsuccessful Page Settings!")

    def transfer(self,addr,val):
        page_byte = (int(addr,base=16)>>8)&0xFF
        addr_byte = (int(addr,base=16))&0xFF
        val_byte  = int(val,base=16)&0xFF

        self.set_page(page_byte)
        self.write_i2c(addr_byte,val_byte)
        reading  = self.read_i2c(addr_byte)
        if val_byte != reading:
            print(hex(val_byte), hex(reading))
