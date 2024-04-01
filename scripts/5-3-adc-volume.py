import RPi.GPIO as gpio
import time
gpio.setmode(gpio.BCM)
dac = [8, 11, 7, 1, 0, 5, 12, 6]
leds = [2, 3, 4, 17, 27, 22, 10, 9]
comp = 14
troykamod = 13
N = 8
U_max = 3.3
gpio.setup(dac, gpio.OUT)
gpio.setup(troykamod, gpio.OUT, initial=gpio.HIGH)
gpio.setup(comp, gpio.IN)
gpio.setup(leds, gpio.OUT)
def decimal_to_binary(N, value):
    return [int(elem) for elem in bin(value)[2:].zfill(N)]
def adc():
    k = 0
    for i in range(7, -1, -1):
        k += 2**i
        gpio.output(dac, decimal_to_binary(N, k))
        time.sleep(0.005)
        if gpio.input(comp) == 1:
            k -= 2**i
    return k
def volume(n):
    n = int(n*10/(2**N))
    mas = [0] * N
    for i in range(n-1):
        mas[i] = 1
    return mas
try:
    while True:
        k = adc()
        if k != 0:
            gpio.output(leds, volume(k))
            print(k*3.3/256)
            print(int(k*10/(2**N)) - 1)
finally:
    gpio.output(dac, 0)
    gpio.output(leds, 0)
    gpio.cleanup()