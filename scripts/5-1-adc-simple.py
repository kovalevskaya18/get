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
    a = 0
    for i in range(2**N):
        dacval = decimal_to_binary(N, i)
        gpio.output(dac, dacval)
        compvalue = gpio.input(comp)
        time.sleep(0.05)
        if compvalue == 1:
            a = i
            break
    return a
            

try:
    while True:
        a = adc()
        if a != 0:
            print(a, '{:.2f}v'.format(U_max*a/(2**N)))
finally:
    gpio.output(dac, 0)
    gpio.cleanup()
                
                  
        