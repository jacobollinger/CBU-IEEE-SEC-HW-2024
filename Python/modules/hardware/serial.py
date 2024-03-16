import serial
import threading

class SerialInterface:
    def __init__(self, port=None, baudrate=9600):
        self.port = port
        self.baudrate = baudrate
        self.serial = None
        self.running = False
        self.lines = []
        self.waiting = False

    def start(self):
        if self.port is None:
            print("Serial port is not specified.")
            return
        self.serial = serial.Serial(self.port, self.baudrate)
        self.running = True
        threading.Thread(target=self._read_data).start()

    def stop(self):
        self.running = False
        if self.serial:
            self.serial.close()
            
    def write_line(self, line):
        if not self.serial:
            print("Serial port is not initialized.")
            return

        if not self.serial.isOpen():
            print("Serial port is not open.")
            return

        try:
            self.serial.write(line.encode())
            self.waiting = False
        except serial.SerialException as e:
            print(f"Failed to write to serial port: {e}")

    def read_line(self):
        if self.lines:
            return self.lines.pop(0)
        return None
    
    def is_data_available(self):
        return len(self.lines) > 0
    
    def is_waiting(self):
        return self.waiting

    def _read_data(self):
        while self.running:
            data = self.serial.readline().decode('utf-8', 'ignore').strip()
            if data.startswith("LOG"):
                print(f"\t\t\t\t\t\t\t\t\t\t\t\tARDUINO {data}")
                pass
            elif data == "WAITING":
                self.waiting = True
                print("ARDUINO is waiting for a command.")
            else:
                self._store_data(data)

    def _store_data(self, data):
        self.lines.append(data)