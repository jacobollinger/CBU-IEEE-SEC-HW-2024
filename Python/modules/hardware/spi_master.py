import spidev

class SPIMaster:
    def __init__(self, bus=0, device=0, max_speed_hz=1000000):
        self.spi = spidev.SpiDev()
        self.bus = bus
        self.device = device
        self.max_speed_hz = max_speed_hz
        
    def open(self):
        self.spi.open(self.bus, self.device)
        self.spi.max_speed_hz = self.max_speed_hz
        
    def close(self):
        self.spi.close()

    def read(self, length):
        # TODO: Implement
        pass
    
    def write(self, data):
        for word in [data[i:i+2] for i in range(0, len(data), 2)]:
            self.spi.write(word)
    
    def readASCII(self, length):
        # TODO: Implement
        pass

    def writeASCII(self, data):
        self.write([ord(char) for char in list(data)] + [0x04])

    def transfer_data(self, data):
        received = []
        for word in [data[i:i+2] for i in range(0, len(data), 2)]:
            received += self.spi.xfer2(word)
        return received
    
    def transferASCII(self, data):
        return ''.join([chr(byte) for byte in self.transfer_data([ord(char) for char in list(data)] + [0x04])])

    def __enter__(self):
        return self.open()
    
    def __exit__(self, type, value, traceback):
        self.close()
