import RPi.GPIO as gpio
import time
import matplotlib.pyplot as plt
gpio.setmode(gpio.BCM)
leds = [2, 3, 4, 17, 27, 22, 10, 9]
dac = [8, 11, 7, 1, 0, 5, 12, 6]
comp = 14
troyka = 13
N = 8
U_min = 2
U_max = 112
gpio.setup(leds, gpio.OUT)
gpio.setup(dac, gpio.OUT, initial = gpio.HIGH)
gpio.setup(comp, gpio.IN)
gpio.setup(troyka, gpio.OUT, initial = gpio.HIGH)
def decimal_to_binary(N, value):
    return [int(elem) for elem in bin(value)[2:].zfill(N)]

def adc():
    k = 0
    for i in range(7, -1, -1):
        k += 2**i
        gpio.output(dac, decimal_to_binary(N, k))
        time.sleep(0.003)
        if gpio.input(comp) == 1:
            k -= 2**i
    return k
try:
    U = 0
    measures = []
    start = time.time()
    count = 0
    print('charge has started')
    while U<U_max:
        U = adc()
        print(U)
        measures.append(U)
        time.sleep(0.0001)
        count += 1
        gpio.output(leds, decimal_to_binary(N, U))
    gpio.setup(troyka, gpio.OUT, initial = gpio.LOW)
    print('The start of discharge')
#    while U>U_min:
#        U = adc()
#       print(U/256*3.3)
#        measures.append(U)
#        time.sleep(0.002)
#        count += 1
#        gpio.output(leds, decimal_to_binary(N, U))
    measure_time = time.time()-start
    print('Coping data in the file')
    with open('data2.txt', 'w') as file:
        for i in measures:
            file.write(str(i) + '\n')
    with open('settings.txt', 'w') as file:
        file.write(str(1/(measure_time/count))+'\n')
        file.write('0.0129')
    print('time of measures: ', measure_time, 'a period of measurement: ', measure_time/count, 'sampling frequency: ', 1/measure_time/count, 'quantization step: 0.013' )
    y = [i/256*3.3 for i in measures]
    x = [i for i in range(len(measures))]
    plt.plot(x, y)
    plt.show()
finally:
    gpio.output(leds, 0)
    gpio.output(dac, 0)
    gpio.cleanup()
                
    
        
    
    

