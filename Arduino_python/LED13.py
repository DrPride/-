# -*- coding: UTF-8 -*-

import time
import serial

ser = serial.Serial( #下面这些参数根据情况修改
    port='COM4',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)
data = ''

#做模块化

while True:
    data = ser.readline()
    data = str(data)
    #还可以做规范化，发送到后端
    print(data)