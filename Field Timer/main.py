import time
from time import sleep
import tm1637
from machine import Pin


class LEDs:
    def __init__(self, pin1, pin2):
        self.pin1 = pin1
        self.pin2 = pin2
        self.pin1.value(0)
        self.pin2.value(0)

    def value(self, value):
        self.pin1.value(value)
        self.pin2.value(value)


tm = tm1637.TM1637(clk=Pin(27), dio=Pin(26))
led = LEDs(Pin(16, Pin.OUT), Pin("LED", Pin.OUT))  # Pin(16, Pin.OUT)

# dim
tm.brightness(1)

interrupt_flag = 0
debounce_time = 0
#? Finish button?
pin = Pin(15, Pin.IN, Pin.PULL_UP)


def callback(pin):
    global interrupt_flag, debounce_time
    if (time.ticks_ms() - debounce_time) > 500:
        interrupt_flag = 1
        debounce_time = time.ticks_ms()


pin.irq(trigger=Pin.IRQ_FALLING, handler=callback)

start = Pin(14, Pin.IN, Pin.PULL_UP)
min = 0
sec = 0
led.value(0)
is_counting = True

while True:
    tm.numbers(min, sec)
    if start.value() == 1:
        is_counting = True
        min = 0
        sec = 0
        tm.numbers(min, sec)
        led.value(1)
        
        for i in range(1, 4):
            for x in range(1, 60):
                sleep(1)
                if interrupt_flag is 1:
                    interrupt_flag = 0
                    print("Interrupt Detected")
                    is_counting = False
                    led.value(0)
                    break
                sec = x
                tm.numbers(min, sec)

            if not is_counting:
                break

            sec = 0
            min = i
            tm.numbers(min, sec)

        led.value(0)
