import serial
import threading

class SerialInterface:
    def __init__(self, port, baudrate):
        self.port = port
        self.baudrate = baudrate
        self.serial = None
        self.running = False
        self.lines = []

    def start(self):
        self.serial = serial.Serial(self.port, self.baudrate)
        self.running = True
        threading.Thread(target=self._read_data).start()

    def stop(self):
        self.running = False
        if self.serial:
            self.serial.close()
            
    def write_line(self, line):
        self.serial.write(f"{line}\n".encode())
    
    def read_line(self):
        if self.lines:
            return self.lines.pop(0)
        return None

    def _read_data(self):
        while self.running:
            data = self.serial.readline().decode().strip()
            if data.startswith("LOG"):
                print(f"ARDUINO {data}")
            else:
                self._store_data(data)

    def _store_data(self, data):
        self.lines.append(data)