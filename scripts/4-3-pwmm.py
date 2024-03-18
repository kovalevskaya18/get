import RPi.GPIO as gpio
from time import sleep
dac = [8, 11, 7, 1, 0, 5, 12, 6]
gpio.setmode(gpio.BCM)
gpio.setup(dac, gpio.OUT)
gpio.setup(27, gpio.OUT)
pwm = gpio.PWM(27, 1000)
pwm.start(0)
U_max = 3.3


try:
    while True:
        DutyCycle = int(input())
        pwm.ChangeDutyCycle(DutyCycle)
        print("{:.2f}".format(DutyCycle*U_max/100))
finally:
    gpio.output(27,0)
    gpio.output(dac,0)
    gpio.cleanup()