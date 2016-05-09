__author__ = 'zmiller'

import serial

ser = serial.Serial('COM', 9600)
while True:
    print ser.readline()
