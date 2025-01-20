from machine import Pin
import utime

led = Pin(27, Pin.OUT)

while True:
    led.toggle()
    utime.sleep(1)
