from serial import Serial

serial = Serial("/dev/ttyUSB0", 115200)

def send_data(data):
    serial.write(data.encode())

def read_data():
    return serial.readline().decode()

def close():
    serial.close()
