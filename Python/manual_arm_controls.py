from modules.hardware.serial import SerialInterface

serial = SerialInterface("/dev/ttyACM0", 9600)

def main():
    serial.start()
    
    while True:
        if serial.is_data_available():
            print(serial.read_line())

        serial.write_line(input("Enter coordinates: "))


if __name__ == "__main__":
    main()
