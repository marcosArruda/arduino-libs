import serial
import time
ser = serial.Serial('/dev/ttyUSB0', 9600)
ser.write('ola')
time.sleep(3)
ser.write('olaalallaa  a alalal') 
time.sleep(3)
