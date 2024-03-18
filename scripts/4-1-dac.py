import RPi.GPIO as gpio
import sys
dac = [8, 11, 7, 1, 0, 5, 12, 6]
gpio.setmode(gpio.BCM)
gpio.setup(dac, gpio.OUT)
U_max = 3.3

def decimal2binary(value):
    return [int(elem) for elem in bin(value)[2:].zfill(8)]
try:
    while True:
        n = input("Enter 0-255, print 'q' to exit\n")
        if n == 'q':
            sys.exit()
        elif n.isdigit() and int(n)%1 == 0 and 0<=int(n)<=2**len(dac)-1:
            gpio.output(dac, decimal2binary(int(n)))
            print("{:.4f}".format(int(n)/(2**len(dac))*U_max))

        elif not n.isdigit() or int(n)%1 != 0 or int(n)<0 or int(n)>2**len(dac) - 1:
            print('enter a number 0-255')
except ValueError:
    print("input a number 0-255")
except KeyboardInterrupt:
    print('.....')
finally:
    gpio.output(dac, 0)
    gpio.cleanup()