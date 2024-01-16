from time import sleep

from spi_master import SPIMaster

spi = SPIMaster(max_speed_hz=2000000)

spi.open()

try:
    while True:
        sent_bytes = input("Press enter data to send... ")
        
        received_bytes = spi.transferASCII(sent_bytes)

        print(f"Sent: {sent_bytes} at {spi.spi.max_speed_hz} Hz")
        print(f"Received: {received_bytes}")
finally:
    spi.close()