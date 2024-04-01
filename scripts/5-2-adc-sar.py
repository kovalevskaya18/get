import RPi.GPIO as gpio
import time
gpio.setmode(gpio.BCM)
dac = [8, 11, 7, 1, 0, 5, 12, 6]
comp = 14
troykamod = 13
N = 8
U_max = 3.3
gpio.setup(dac, gpio.OUT)
gpio.setup(troykamod, gpio.OUT, initial=gpio.HIGH)
gpio.setup(comp, gpio.IN)
def decimal_to_binary(N, value):
    return [int(elem) for elem in bin(value)[2:].zfill(N)]
def adc():
    k = 0
    for i in range(7, -1, -1):
        k += 2**i
        gpio.output(dac, decimal_to_binary(N, k))
        time.sleep(0.05)
        if gpio.input(comp) == 1:
            k -= 2**i
    return k
try:
    while True:
        k = adc()
        if k != 0:
            print(k, '{:.2f}v'.format(U_max*k/(2**N)))
finally:
    gpio.output(dac, 0)
    gpio.cleanup()