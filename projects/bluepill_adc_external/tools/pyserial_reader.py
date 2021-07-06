import serial
from matplotlib import pyplot as plt
import numpy
import time

ser = serial.Serial('/dev/ttyUSB0')
print(ser.name)
L = 5000
results = numpy.ndarray((L,),int)
i = 0
while i < L:
    data = ser.readline()
    print(data)
    if(len(data)) != 3:
            continue
    reading = data[0]*256 + data[1]
    print("ADC reading =", reading)
    print("Voltage = {:.3f}".format(reading/4096*3.3))
    results[i] = reading
    i += 1
    
plt.plot(results)
plt.show()
