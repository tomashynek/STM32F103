import serial

ser = serial.Serial('/dev/ttyUSB0')
print(ser.name)
while(1):
    data = ser.readline()
    print(data)
    reading = data[0]*256 + data[1]
    print("ADC reading =", reading)
    print("Voltage = ", reading/4096*3.3)
